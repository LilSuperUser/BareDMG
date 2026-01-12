// include/core/cartridge.h
#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <core/utils.h>

// ---------------------------------------------
// Raw Header Layout
// https://gbdev.io/pandocs/The_Cartridge_Header.html
// ---------------------------------------------
typedef struct {
    u8   entry[4];   // Entry point (0x100 - 0x103)
    u8   logo[0x30]; // Nintendo logo (0x0104 - 0x0133)

    char title[16]; // Title in uppercase ASCII (0x0134 - 0x0143)
    u16  new_lic;   // New license code (0x0144 - 0x0145)

    u8   sgb_flag; // SGB flag (0x0146)
    u8   type;     // Cartridge type (0x0147)

    u8   rom_size; // ROM size (0x0148)
    u8   ram_size; // RAM size (0x0149)

    u8   dest_code;    // Destination code (0x014A)
    u8   old_lic_code; // Old license code (0x14B) if $33 use new lic code

    u8   version; // Mask ROM version number (0x014C)

    u8   header_checksum; // 8 bit checksum for the header (0x014D)
    u16  global_checksum; // 16-bit global checksum (0x014E - 0x014F)
} RawRomHeader;

// ---------------------------------------------
// Parsed Header Layout
// ---------------------------------------------
typedef struct {
    char title[17]; // Null-terminated title

    u8   cart_type;     // MBC type
    u8   rom_size_code; // Encoded size (not bytes)
    u8   ram_size_code; // Encoded size (not bytes)

    u16  lic_code; // if old lic code = $33 use new lic code
    u8   version;

    bool sgb_supported; // (if sgb_flag == 0x03)
    bool cgb_supported; // Derived from title area ($80 = supports CGB and $C0 only CGB)
} CartHeader;

#endif
