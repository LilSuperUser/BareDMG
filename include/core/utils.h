// include/core/utils.h
#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdbool.h>

// ---------------------------------------------
// Type Definitions
// ---------------------------------------------
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

// ---------------------------------------------
// ANSI Colors
// ---------------------------------------------
#define RED "\033[91m"          // Errors
#define YELLOW "\033[93m"       // Warnings
#define GREEN "\033[92m"        // Success
#define CYAN "\033[96m"         // Information
#define BLUE "\033[94m"         // Debug
#define MAGENTA "\033[95m"      // Emulator-specific
#define BOLD_WHITE "\033[1;97m" // Bold white
#define ORANGE "\033[38;5;208m" // Serial
#define RESET "\033[0m"

// ---------------------------------------------
// Logger functions
// ---------------------------------------------
void put_error(const char *format, ...);
void put_warning(const char *format, ...);
void put_success(const char *format, ...);
void put_info(const char *format, ...);
void put_debug(const char *format, ...);
void put_emulator(const char *format, ...);
void put_serial(const char *format, ...);
void put_bold(const char *msg);

// ---------------------------------------------
// Bit Manipulation Macros (simple, inline)
// ---------------------------------------------

// Create a number with only bit x set
#define BIT(x) (1 << (x))

// Check if a single bit is set in val
#define CHECK_BIT(val, bit) ((val) >> (bit) & 1)

// Set/Clear/Toggle a single bit
#define SET_BIT(val, bit) ((val) | BIT(bit))
#define CLEAR_BIT(val, bit) ((val) & ~BIT(bit))
#define TOGGLE_BIT(val, bit) ((val) ^ BIT(bit))

// Get bit range (for multi-bit values)
// Extract len bits, starting at position start, from val and return as right-aligned number.
#define GET_BITS(val, start, len) (((val) >> (start)) & ((1 << (len)) - 1))

// Set bit range (for multi-bit values)
// Replace len bits starting from start in val with given bits
#define SET_BITS(val, start, len, bits)                                                            \
    (((val) & ~(((1U << (len)) - 1) << (start))) | (((bits) & ((1U << (len)) - 1)) << (start)))

// Extract specific bits
#define MASK_BITS(val, mask) ((val) & (mask))

// Keep some bits, replace others
#define REPLACE_BITS(old, new, mask) (((old) & ~(mask)) | ((new) & (mask)))

// ---------------------------------------------
// 16-bit Register Operations (simple macros)
// ---------------------------------------------

// Combine two 8-bit values into 16 bit (high B, low B)
#define MAKE_U16(hi, lo) (((u16)(hi) << 8) | (u16)lo)

// Extract high/low 8 bits from a 16-bit value
#define GET_HIGH_BYTE(val) ((u8)((val) >> 8))
#define GET_LOW_BYTE(val) ((u8)((val) & 0xFF))

// ---------------------------------------------
// Complex Utility Functions
// ---------------------------------------------
u16  swap_bytes(u16 val);              // Swap endianness
bool check_half_carry_add(u8 a, u8 b); // Check if half-carry occurred (bit 3->4)
bool check_carry_add(u8 a, u8 b);      // Check if carry occurred (bit 7->8)
bool check_half_carry_sub(u8 a, u8 b); // Half-carry for subtraction
bool check_carry_sub(u8 a, u8 b);      // Carry for subtraction

// 16-bit carry checks (for 16-bit arithmetic)
bool check_half_carry_add_u16(u16 a, u16 b); // Half-carry bit 11->12
bool check_carry_add_u16(u16 a, u16 b);      // Carry bit 15->16

// ADC instruction helpers
bool check_half_carry_adc(u8 a, u8 b, u8 carry);
bool check_carry_adc(u8 a, u8 b, u8 carry);

// SBC instruction helpers
bool check_half_carry_sbc(u8 a, u8 b, u8 carry);
bool check_carry_sbc(u8 a, u8 b, u8 carry);

// Binary Coded Decimal (BCD) adjustment for DAA instruction
u8   adjust_bcd(u8 value, bool subtract, bool carry, bool half_carry);

// Sign extension (for relative jumps)
i16  sign_extend_i8(u8 val); // Extend 8 bit signed to 16-bit

#endif
