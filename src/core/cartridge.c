// src/core/cartridge.c
#include <stdio.h>
#include <core/cartridge.h>
#include <stdlib.h>
#include <string.h>

// TODO: cart_load()
// Load ROM from disk & parse header
int    cart_load(Cartridge *cart, const char *path);

// TODO: cart_unload()
// Unlod the cart: Free the allocated memory for RAM & ROM
void   cart_unload(Cartridge *cart);

// TODO: parse_header()
// Parse raw header into usable format
void   parse_header(const RawRomHeader *raw, CartHeader *out);

// TODO: cart_print_header
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
