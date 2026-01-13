// src/core/utils.c
#include <core/utils.h>

// Swap endianness
u16 swap_bytes(u16 val) {
    return (val << 8) | (val >> 8);
}

// Check if half-carry occurred (bit 3->4)
bool check_half_carry_add(u8 a, u8 b) {
    return ((a & 0x0F) + (b & 0x0F)) > 0x0F;
}

// Check if carry occurred (bit 7->8)
bool check_carry_add(u8 a, u8 b) {
    return (u16)a + (u16)b > 0xFF;
}

// Check if half-carry for subtraction occurred
bool check_half_carry_sub(u8 a, u8 b) {
    return (a & 0x0F) < (b & 0x0F);
}

// Check if carry for subtraction occurred
bool check_carry_sub(u8 a, u8 b) {
    return a < b;
}

// 16-bit versions to check if half-carry occurred (bit 11->12)
bool check_half_carry_add_u16(u16 a, u16 b) {
    return ((a & 0x0FFF) + (b & 0x0FFF)) > 0x0FFF;
}

// 16-bit version to check if carry occurred
bool check_carry_add_u16(u16 a, u16 b) {
    return ((u32)a + (u32)b) > 0xFFFF;
}

// Extend 8-bit signed to 16-bit
i16 sign_extend_i8(u8 val) {
    return (val & 0x80) ? (i16)(val | 0xFF00) : (i16)val;
}
