// src/core/cartridge.c
#include <stdio.h>
#include <core/cartridge.h>
#include <stdlib.h>
#include <string.h>

/*
EXIT CODES
return 1; -->  failed to open
return 2; -->  too small
return 3; -->  malloc ROM failed
return 4; -->  malloc RAM failed
return 5; -->  fread failed
*/

// Load ROM from disk & parse header
int cart_load(Cartridge *cart, const char *path) {
    // Open the ROM file
    FILE *rom_f = fopen(path, "rb");
    if (!rom_f) {
        fprintf(stderr, "Failed to open ROM: %s\n", path);
        return 1;
    }

    // Get the file size
    fseek(rom_f, 0, SEEK_END);
    cart->rom_size = ftell(rom_f);
    rewind(rom_f);

    // Actual ROM file size should be greater than 0x0150
    if (cart->rom_size < 0x0150) {
        fclose(rom_f);
        fprintf(stderr, "ROM file too small\n");
        return 2;
    }

    // Allocate memory for ROM from heap
    cart->rom = malloc(cart->rom_size);
    if (!cart->rom) {
        fclose(rom_f);
        fprintf(stderr, "Failed to allocate ROM memory\n");
        return 3;
    }

    // Read the ROM data from file into ROM buffer
    size_t read = fread(cart->rom, 1, cart->rom_size, rom_f);
    fclose(rom_f);

    if (read != cart->rom_size) {
        fprintf(stderr, "Failed to read ROM\n");
        return 5;
    }

    // Copy raw header (located at 0x100 - 0x14F)
    memcpy(&cart->raw_header, cart->rom + 0x0100, sizeof(RawRomHeader));

    // Parse the header into usable format
    parse_header(&cart->raw_header, &cart->header);

    // Allocate RAM if needed (based on ram_size_code)
    cart->ram_size = get_ram_size(cart->header.ram_size_code);
    if (cart->ram_size > 0) {
        cart->ram = calloc(1, cart->ram_size);
        if (!cart->ram) {
            fprintf(stderr, "Failed to allocate cartridge RAM\n");
            free(cart->rom);
            cart->rom      = NULL;
            cart->rom_size = 0;
            return 4;
        }
    } else {
        cart->ram = NULL;
    }

    return 0;
}

// Unload the cart: Free the allocated memory for RAM & ROM
void cart_unload(Cartridge *cart) {
    if (cart->rom) {
        free(cart->rom);
        cart->rom = NULL;
    }

    if (cart->ram) {
        free(cart->ram);
        cart->ram = NULL;
    }

    cart->rom_size = 0;
    cart->ram_size = 0;
}

// Parse raw header into usable format
void parse_header(const RawRomHeader *raw, CartHeader *out) {
    // Make title null terminated
    memcpy(out->title, raw->title, 16);
    out->title[16]     = '\0';

    // Parse CGB flag (embedded in title area at byte 15)
    // DMG only 0x00, CGB only (0xC0), both compatible (0x80)
    u8 cgb_flag        = raw->title[15];
    out->cgb_supported = (cgb_flag == 0x80 || cgb_flag == 0xC0);

    // If CGB flag is present, actual title is only 15 chars
    if (out->cgb_supported)
        out->title[15] = '\0';

    // Parse SGB flag
    out->sgb_supported = (raw->sgb_flag == 0x03);

    // Cartridge type (determine MBC)
    out->cart_type     = raw->type;

    // ROM/RAM sizes (encoded values not actual Bytes)
    out->rom_size_code = raw->rom_size;
    out->ram_size_code = raw->ram_size;

    // License code (use new if old is 0x33)
    if (raw->old_lic_code == 0x33)
        out->lic_code = raw->new_lic;
    else
        out->lic_code = raw->old_lic_code;

    // Version
    out->version = raw->version;
}

// TODO: cart_print_header()
// Print cartridge information to stdout
void   cart_print_header(const CartHeader *hdr);

// Get RAM size in bytes from RAM size code
// https://gbdev.io/pandocs/The_Cartridge_Header.html#0149--ram-size
size_t get_ram_size(u8 ram_size_code) {
    switch (ram_size_code) {
        case 0x00:
            return 0; // No RAM
        case 0x01:
            return 2 * 1024; // 2 KB (rare)
        case 0x02:
            return 8 * 1024; // 8 KB (1 bank)
        case 0x03:
            return 32 * 1024; // 32 KB (4 banks of 8 KB)
        case 0x04:
            return 128 * 1024; // 128 KB (16 banks of 8 KB)
        case 0x05:
            return 64 * 1024; // 64 KB (8 banks of 8KB)
        default:
            fprintf(stderr, "Unknown RAM size code: 0x%02X\n", ram_size_code);
            return 0;
    }
}

// Get ROM size in bytes from ROM size code
// https://gbdev.io/pandocs/The_Cartridge_Header.html#0148--rom-size
size_t get_rom_size(u8 rom_size_code) {
    /*
     * Formula: 32 KB << rom_size_code
     * 0x00 ==> 32 KB (2 banks)
     * 0x01 ==> 64 KB (4 banks)
     * 0x02 ==> 128 KB (8 banks)
     * ... up to 0x08 ==> 8 MB
     */
    if (rom_size_code <= 0x08) {
        return (32 * 1024) << rom_size_code;
    }

    // Special cases for certain rare carts
    switch (rom_size_code) {
        case 0x52:
            return 72 * 16 * 1024; // 1.1 MB
        case 0x53:
            return 80 * 16 * 1024; // 1.2 MB
        case 0x54:
            return 96 * 16 * 1024; // 1.5 MB
        default:
            fprintf(stderr, "Unknown ROM size code: 0x%02X\n", rom_size_code);
            return 0;
    }
}

// Get human-readable cartridge type name
// https://gbdev.io/pandocs/The_Cartridge_Header.html#0147--cartridge-type
const char *get_cart_type_name(u8 type) {
    switch (type) {
        case 0x00:
            return "ROM ONLY";
        case 0x01:
            return "MBC1";
        case 0x02:
            return "MBC1+RAM";
        case 0x03:
            return "MBC1+RAM+BATTERY";
        case 0x05:
            return "MBC2";
        case 0x06:
            return "MBC2+BATTERY";
        case 0x08:
            return "ROM+RAM";
        case 0x09:
            return "ROM+RAM+BATTERY";
        case 0x0B:
            return "MMM01";
        case 0x0C:
            return "MMM01+RAM";
        case 0x0D:
            return "MMM01+RAM+BATTERY";
        case 0x0F:
            return "MBC3+TIMER+BATTERY";
        case 0x10:
            return "MBC3+TIMER+RAM+BATTERY";
        case 0x11:
            return "MBC3";
        case 0x12:
            return "MBC3+RAM";
        case 0x13:
            return "MBC3+RAM+BATTERY";
        case 0x19:
            return "MBC5";
        case 0x1A:
            return "MBC5+RAM";
        case 0x1B:
            return "MBC5+RAM+BATTERY";
        case 0x1C:
            return "MBC5+RUMBLE";
        case 0x1D:
            return "MBC5+RUMBLE+RAM";
        case 0x1E:
            return "MBC5+RUMBLE+RAM+BATTERY";
        case 0x20:
            return "MBC6";
        case 0x22:
            return "MBC7+SENSOR+RUMBLE+RAM+BATTERY";
        case 0xFC:
            return "POCKET CAMERA";
        case 0xFD:
            return "BANDAI TAMA5";
        case 0xFE:
            return "HuC3";
        case 0xFF:
            return "HuC1+RAM+BATTERY";
        default:
            return "UNKNOWN";
    }
}
