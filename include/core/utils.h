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

// ---------------------------------------------
// 16-bit Register Operations (simple macros)
// ---------------------------------------------

// Combine two 8-bit values into 16 bit (high B, low B)
#define MAKE_U16(hi, lo) (((u16)(hi) << 8) | (u16)lo)

// Extract high/low 8 bits from a 16-bit value
#define GET_HIGH_BYTE(val) ((u8)((val) >> 8))
#define GET_LOW_BYTE(val) ((u8)((val) & 0xFF))

#endif
