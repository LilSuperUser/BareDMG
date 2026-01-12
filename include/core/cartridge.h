// include/core/cartridge.h
#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <core/utils.h>
#include <stddef.h>

// ---------------------------------------------
// Raw Header Layout
// https://gbdev.io/pandocs/The_Cartridge_Header.html
// ---------------------------------------------
typedef struct {
    u8   entry[4];        // Entry point (0x100 - 0x103)
    u8   logo[0x30];      // Nintendo logo (0x0104 - 0x0133)
    char title[16];       // Title in uppercase ASCII (0x0134 - 0x0143)
    u16  new_lic;         // New license code (0x0144 - 0x0145)
    u8   sgb_flag;        // SGB flag (0x0146)
    u8   type;            // Cartridge type (0x0147)
    u8   rom_size;        // ROM size (0x0148)
    u8   ram_size;        // RAM size (0x0149)
    u8   dest_code;       // Destination code (0x014A)
    u8   old_lic_code;    // Old license code (0x14B) - if $33, use new_lic
    u8   version;         // Mask ROM version number (0x014C)
    u8   header_checksum; // 8-bit checksum for the header (0x014D)
    u16  global_checksum; // 16-bit global checksum (0x014E - 0x014F)
} RawRomHeader;

// ---------------------------------------------
// Parsed Header
// ---------------------------------------------
typedef struct {
    char title[17];     // Null-terminated title
    u8   cart_type;     // Cartridge type (determines MBC, battery, RTC, etc.)
    u8   rom_size_code; // Encoded ROM size (not actual bytes)
    u8   ram_size_code; // Encoded RAM size (not actual bytes)
    u16  lic_code;      // License code (uses new_lic if old_lic_code == $33)
    u8   version;       // ROM version number
    bool sgb_supported; // Super Game Boy support (sgb_flag == 0x03)
    bool cgb_supported; // Game Boy Color support (0x80 = enhanced, 0xC0 = only)
} CartHeader;

// ---------------------------------------------
// Cartridge
// ---------------------------------------------
typedef struct {
    u8          *rom;        // ROM data
    size_t       rom_size;   // ROM size in bytes
    u8          *ram;        // External RAM (for save data)
    size_t       ram_size;   // RAM size in bytes
    RawRomHeader raw_header; // Raw header as read from ROM
    CartHeader   header;     // Parsed header with usable values
    // MBC-specific state (later)
    // Battery flag (later)
} Cartridge;

// ---------------------------------------------
// Cartridge Functions
// ---------------------------------------------

// Load ROM from disk & parse header
int         cart_load(Cartridge *cart, const char *path);

// Unlod the cart: Free the allocated memory for RAM & ROM
void        cart_unload(Cartridge *cart);

// Parse raw header into usable format
void        parse_header(const RawRomHeader *raw, CartHeader *out);

// Print cartridge information to stdout
void        cart_print_header(const CartHeader *hdr);

// Decode RAM size code to actual bytes
size_t      get_ram_size(u8 ram_size_code);

// Decode ROM size code to actual bytes
size_t      get_rom_size(u8 rom_size_code);

// Get human-readable cartridge type name
const char *get_cart_type_name(u8 type);

// Get header checksum
bool        cart_verify_header_checksum(const Cartridge *cart);

#endif // CARTRIDGE_H
