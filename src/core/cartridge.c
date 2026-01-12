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
return -1; --> cart header checksum failed
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

    // Verify the header checksum
    if (!cart_verify_header_checksum(cart)) {
        fprintf(stderr, "Error: Invalid cartridge header checksum\n");
        cart_unload(cart);
        return -1;
    }
    printf("Cartridge header checksum: OK\n\n");

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
    if (raw->old_lic_code == 0x33) {
        /* out->lic_code = (raw->new_lic_hi << 8) | raw->new_lic_lo; */
        out->lic_code = MAKE_U16(raw->new_lic_hi, raw->new_lic_lo);
    } else {
        out->lic_code = raw->old_lic_code;
    }

    // Version
    out->version = raw->version;
}

// Print cartridge information to stdout
void cart_print_header(const CartHeader *hdr) {
    // Get publisher name using license code
    // If the (lower 8 bits != 0x33) ==> use old code
    bool        is_old_code = (hdr->lic_code <= 0xFF);
    const char *publisher   = get_publisher_name(hdr->lic_code, is_old_code);

    printf("================================\n");
    printf("    Cartridge Information\n");
    printf("================================\n");

    printf("Title:         %s\n", hdr->title);
    printf("Publisher:     %s (0x%04X)\n", publisher, hdr->lic_code);
    printf("Type:          0x%02X (%s)\n", hdr->cart_type, get_cart_type_name(hdr->cart_type));
    printf("Version:       0x%02X\n", hdr->version);

    size_t rom_kb = get_rom_size(hdr->rom_size_code) / 1024;
    printf("ROM Size:      0x%02X (%zu KB)\n", hdr->rom_size_code, rom_kb);

    size_t ram_kb = get_ram_size(hdr->ram_size_code) / 1024;
    if (ram_kb > 0)
        printf("RAM Size:      0x%02X (%zu KB)\n", hdr->ram_size_code, ram_kb);
    else
        printf("RAM Size:      0x%02X (No RAM)\n", hdr->ram_size_code);

    printf("SGB Support:   %s\n", hdr->sgb_supported ? "Yes" : "No");
    printf("CGB Support:   %s\n", hdr->cgb_supported ? "Yes" : "No");
    printf("================================\n");
}

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

// Get header checksum
// https://gbdev.io/pandocs/The_Cartridge_Header.html#014d--header-checksum
bool cart_verify_header_checksum(const Cartridge *cart) {
    const u8 *rom      = cart->rom;

    u8        checksum = 0;
    for (u16 addr = 0x0134; addr <= 0x014C; addr++) {
        checksum = checksum - rom[addr] - 1;
    }

    return checksum == rom[0x014D];
}

// Get publisher name from license code
const char *get_publisher_name(u16 lic_code, bool is_old_code) {

    /* printf("is_old_code: %d\n", is_old_code); */
    /* printf("license code: %d\n", lic_code); */
    if (is_old_code) {
        // Old license code (single byte at 0x014B)
        switch (lic_code) {
            case 0x00:
                return "None";
            case 0x01:
                return "Nintendo";
            case 0x08:
                return "Capcom";
            case 0x13:
                return "EA (Electronic Arts)";
            case 0x18:
                return "Hudson Soft";
            case 0x19:
                return "B-AI";
            case 0x1F:
                return "Virgin Games";
            case 0x24:
                return "PCM Complete";
            case 0x28:
                return "Kemco";
            case 0x29:
                return "SETA Corporation";
            case 0x30:
                return "Viacom";
            case 0x31:
                return "Nintendo";
            case 0x32:
                return "Bandai";
            case 0x33:
                return "INVALID (new code indicator)";
            case 0x34:
                return "Konami";
            case 0x38:
                return "Capcom";
            case 0x39:
                return "Banpresto";
            case 0x41:
                return "Ubi Soft";
            case 0x42:
                return "Atlus";
            case 0x50:
                return "Absolute";
            case 0x51:
                return "Acclaim";
            case 0x52:
                return "Activision";
            case 0x53:
                return "American Sammy";
            case 0x54:
                return "Konami";
            case 0x56:
                return "LJN";
            case 0x60:
                return "Titus";
            case 0x67:
                return "Ocean";
            case 0x69:
                return "EA (Electronic Arts)";
            case 0x70:
                return "Infogrames";
            case 0x71:
                return "Interplay";
            case 0x72:
                return "Broderbund";
            case 0x78:
                return "THQ";
            case 0x79:
                return "Accolade";
            case 0x7F:
                return "Kemco";
            case 0x80:
                return "Misawa";
            case 0x83:
                return "LOZC";
            case 0x86:
                return "Tokuma Shoten";
            case 0x8B:
                return "Bullet-Proof Software";
            case 0x8C:
                return "Vic Tokai";
            case 0x8F:
                return "I'Max";
            case 0x91:
                return "Chunsoft";
            case 0x92:
                return "Video System";
            case 0x95:
                return "Varie";
            case 0x97:
                return "Kaneko";
            case 0x99:
                return "Arc";
            case 0x9B:
                return "Tecmo";
            case 0x9C:
                return "Imagineer";
            case 0x9D:
                return "Banpresto";
            case 0x9F:
                return "Nova";
            case 0xA1:
                return "Hori Electric";
            case 0xA2:
                return "Bandai";
            case 0xA4:
                return "Konami";
            case 0xA7:
                return "Takara";
            case 0xA9:
                return "Technos Japan";
            case 0xAF:
                return "Namco";
            case 0xB0:
                return "Acclaim";
            case 0xB1:
                return "ASCII/Nexoft";
            case 0xB2:
                return "Bandai";
            case 0xB4:
                return "Enix";
            case 0xB6:
                return "HAL Laboratory";
            case 0xB7:
                return "SNK";
            case 0xB9:
                return "Pony Canyon";
            case 0xBA:
                return "Culture Brain";
            case 0xBB:
                return "Sunsoft";
            case 0xBF:
                return "Sammy";
            case 0xC0:
                return "Taito";
            case 0xC2:
                return "Kemco";
            case 0xC3:
                return "Square";
            case 0xC4:
                return "Tokuma Shoten";
            case 0xC5:
                return "Data East";
            case 0xC6:
                return "Tonkin House";
            case 0xC8:
                return "Koei";
            case 0xCE:
                return "Pony Canyon";
            case 0xD1:
                return "Sofel";
            case 0xD2:
                return "Quest";
            case 0xD4:
                return "Ask Kodansha";
            case 0xD6:
                return "Naxat Soft";
            case 0xD9:
                return "Banpresto";
            case 0xDA:
                return "Tomy";
            case 0xDB:
                return "LJN";
            case 0xDE:
                return "Human";
            case 0xDF:
                return "Altron";
            case 0xE0:
                return "Jaleco";
            case 0xE2:
                return "Uutaka";
            case 0xE5:
                return "Epoch";
            case 0xE7:
                return "Athena";
            case 0xE8:
                return "Asmik";
            case 0xE9:
                return "Natsume";
            case 0xEB:
                return "Atlus";
            case 0xEE:
                return "IGS";
            case 0xFF:
                return "LJN";
            default:
                return "Unknown";
        }
    } else {
        // New license code (two ASCII bytes)
        // Stored as: (hi_byte << 8) | lo_byte
        // "01" = 0x30 ('0') and 0x31 ('1') = 0x3031
        switch (lic_code) {
            case 0x3030:
                return "None"; // "00"
            case 0x3031:
                return "Nintendo"; // "01"
            case 0x3038:
                return "Capcom"; // "08"
            case 0x3133:
                return "EA (Electronic Arts)"; // "13"
            case 0x3138:
                return "Hudson Soft"; // "18"
            case 0x3139:
                return "B-AI"; // "19"
            case 0x3230:
                return "KSS"; // "20"
            case 0x3232:
                return "Planning Office WADA"; // "22"
            case 0x3234:
                return "PCM Complete"; // "24"
            case 0x3235:
                return "San-X"; // "25"
            case 0x3238:
                return "Kemco"; // "28"
            case 0x3239:
                return "SETA Corporation"; // "29"
            case 0x3330:
                return "Viacom"; // "30"
            case 0x3331:
                return "Nintendo"; // "31"
            case 0x3332:
                return "Bandai"; // "32"
            case 0x3333:
                return "Ocean/Acclaim"; // "33"
            case 0x3334:
                return "Konami"; // "34"
            case 0x3335:
                return "HectorSoft"; // "35"
            case 0x3337:
                return "Taito"; // "37"
            case 0x3338:
                return "Hudson Soft"; // "38"
            case 0x3339:
                return "Banpresto"; // "39"
            case 0x3431:
                return "Ubi Soft"; // "41"
            case 0x3432:
                return "Atlus"; // "42"
            case 0x3434:
                return "Malibu Interactive"; // "44"
            case 0x3436:
                return "Angel"; // "46"
            case 0x3437:
                return "Bullet-Proof Software"; // "47"
            case 0x3439:
                return "Irem"; // "49"
            case 0x3530:
                return "Absolute"; // "50"
            case 0x3531:
                return "Acclaim Entertainment"; // "51"
            case 0x3532:
                return "Activision"; // "52"
            case 0x3533:
                return "Sammy USA Corporation"; // "53"
            case 0x3534:
                return "Konami"; // "54"
            case 0x3535:
                return "Hi Tech Expressions"; // "55"
            case 0x3536:
                return "LJN"; // "56"
            case 0x3537:
                return "Matchbox"; // "57"
            case 0x3538:
                return "Mattel"; // "58"
            case 0x3539:
                return "Milton Bradley"; // "59"
            case 0x3630:
                return "Titus Interactive"; // "60"
            case 0x3631:
                return "Virgin Games"; // "61"
            case 0x3634:
                return "Lucasfilm Games"; // "64"
            case 0x3637:
                return "Ocean Software"; // "67"
            case 0x3639:
                return "EA (Electronic Arts)"; // "69"
            case 0x3730:
                return "Infogrames"; // "70"
            case 0x3731:
                return "Interplay"; // "71"
            case 0x3732:
                return "Broderbund"; // "72"
            case 0x3733:
                return "Sculptured Software"; // "73"
            case 0x3735:
                return "The Sales Curve"; // "75"
            case 0x3738:
                return "THQ"; // "78"
            case 0x3739:
                return "Accolade"; // "79"
            case 0x3741:
                return "Triffix Entertainment"; // "7A"
            case 0x3743:
                return "Microprose"; // "7C"
            case 0x3746:
                return "Kemco"; // "7F"
            case 0x3830:
                return "Misawa Entertainment"; // "80"
            case 0x3833:
                return "LOZC G."; // "83"
            case 0x3836:
                return "Tokuma Shoten"; // "86"
            case 0x3837:
                return "Tsukuda Original"; // "87"
            case 0x3931:
                return "Chunsoft"; // "91"
            case 0x3932:
                return "Video System"; // "92"
            case 0x3933:
                return "Ocean/Acclaim"; // "93"
            case 0x3935:
                return "Varie"; // "95"
            case 0x3936:
                return "Yonezawa/S'Pal"; // "96"
            case 0x3937:
                return "Kaneko"; // "97"
            case 0x3939:
                return "Pack-In-Video"; // "99"
            case 0x4131:
                return "Nintendo"; // "A1"
            case 0x4134:
                return "Konami"; // "A4"
            default:
                return "Unknown";
        }
    }
}
