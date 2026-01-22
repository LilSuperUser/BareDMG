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

// ADC instruction helpers
bool check_half_carry_adc(u8 a, u8 b, u8 carry) {
    return ((a & 0x0F) + (b & 0x0F) + carry) > 0x0F;
}

bool check_carry_adc(u8 a, u8 b, u8 carry) {
    return (u16)a + (u16)b + carry > 0xFF;
}

// SBC instruction helpers
bool check_half_carry_sbc(u8 a, u8 b, u8 carry) {
    return (a & 0x0F) < ((b & 0x0F) + carry);
}

bool check_carry_sbc(u8 a, u8 b, u8 carry) {
    return (u16)a < (u16)b + carry;
}

// DAA instruction helper
u8 adjust_bcd(u8 value, bool subtract, bool carry, bool half_carry) {
    u8 correction = 0;

    if (!subtract) {
        // After ADD / ADC
        if (half_carry || (value & 0x0F) > 0x09)
            correction |= 0x06;

        if (carry || value > 0x99)
            correction |= 0x60;

        value += correction;
    } else {
        // After SUB / SBC
        if (half_carry)
            correction |= 0x06;

        if (carry)
            correction |= 0x60;

        value -= correction;
    }

    return value;
}

// Extend 8-bit signed to 16-bit
i16 sign_extend_i8(u8 val) {
    return (val & 0x80) ? (i16)(val | 0xFF00) : (i16)val;
}
