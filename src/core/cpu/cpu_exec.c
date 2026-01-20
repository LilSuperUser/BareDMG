// src/core/cpu/cpu_exec.c
#include <core/cpu/cpu.h>
#include <core/cpu/cpu_exec.h>
#include <core/bus.h>
#include <gbemu.h>
#include <core/utils.h>

u8 instr_nop(CPU *cpu) {
    (void)cpu;
    return 0;
}

// ============================================================================
// 8-bit Load Instructions
// ============================================================================

// Immediate loads
u8 instr_ld_b_n(CPU *cpu) {
    cpu->regs.b = mmu_read(cpu->gb, cpu->pc++);
    return 0;
}

u8 instr_ld_c_n(CPU *cpu) {
    cpu->regs.c = mmu_read(cpu->gb, cpu->pc++);
    return 0;
}

u8 instr_ld_d_n(CPU *cpu) {
    cpu->regs.d = mmu_read(cpu->gb, cpu->pc++);
    return 0;
}

u8 instr_ld_e_n(CPU *cpu) {
    cpu->regs.e = mmu_read(cpu->gb, cpu->pc++);
    return 0;
}

u8 instr_ld_h_n(CPU *cpu) {
    cpu->regs.h = mmu_read(cpu->gb, cpu->pc++);
    return 0;
}

u8 instr_ld_l_n(CPU *cpu) {
    cpu->regs.l = mmu_read(cpu->gb, cpu->pc++);
    return 0;
}

u8 instr_ld_a_n(CPU *cpu) {
    cpu->regs.a = mmu_read(cpu->gb, cpu->pc++);
    return 0;
}

// Register <-> Register
u8 instr_ld_b_b(CPU *cpu) {
    cpu->regs.b = cpu->regs.b;
    return 0;
}

u8 instr_ld_b_c(CPU *cpu) {
    cpu->regs.b = cpu->regs.c;
    return 0;
}

u8 instr_ld_b_d(CPU *cpu) {
    cpu->regs.b = cpu->regs.d;
    return 0;
}

u8 instr_ld_b_e(CPU *cpu) {
    cpu->regs.b = cpu->regs.e;
    return 0;
}

u8 instr_ld_b_h(CPU *cpu) {
    cpu->regs.b = cpu->regs.h;
    return 0;
}

u8 instr_ld_b_l(CPU *cpu) {
    cpu->regs.b = cpu->regs.l;
    return 0;
}

u8 instr_ld_b_a(CPU *cpu) {
    cpu->regs.b = cpu->regs.a;
    return 0;
}

u8 instr_ld_c_b(CPU *cpu) {
    cpu->regs.c = cpu->regs.b;
    return 0;
}

u8 instr_ld_c_c(CPU *cpu) {
    cpu->regs.c = cpu->regs.c;
    return 0;
}

u8 instr_ld_c_d(CPU *cpu) {
    cpu->regs.c = cpu->regs.d;
    return 0;
}

u8 instr_ld_c_e(CPU *cpu) {
    cpu->regs.c = cpu->regs.e;
    return 0;
}

u8 instr_ld_c_h(CPU *cpu) {
    cpu->regs.c = cpu->regs.h;
    return 0;
}

u8 instr_ld_c_l(CPU *cpu) {
    cpu->regs.c = cpu->regs.l;
    return 0;
}

u8 instr_ld_c_a(CPU *cpu) {
    cpu->regs.c = cpu->regs.a;
    return 0;
}

u8 instr_ld_d_b(CPU *cpu) {
    cpu->regs.d = cpu->regs.b;
    return 0;
}

u8 instr_ld_d_c(CPU *cpu) {
    cpu->regs.d = cpu->regs.c;
    return 0;
}

u8 instr_ld_d_d(CPU *cpu) {
    cpu->regs.d = cpu->regs.d;
    return 0;
}

u8 instr_ld_d_e(CPU *cpu) {
    cpu->regs.d = cpu->regs.e;
    return 0;
}

u8 instr_ld_d_h(CPU *cpu) {
    cpu->regs.d = cpu->regs.h;
    return 0;
}

u8 instr_ld_d_l(CPU *cpu) {
    cpu->regs.d = cpu->regs.l;
    return 0;
}

u8 instr_ld_d_a(CPU *cpu) {
    cpu->regs.d = cpu->regs.a;
    return 0;
}

u8 instr_ld_e_b(CPU *cpu) {
    cpu->regs.e = cpu->regs.b;
    return 0;
}

u8 instr_ld_e_c(CPU *cpu) {
    cpu->regs.e = cpu->regs.c;
    return 0;
}

u8 instr_ld_e_d(CPU *cpu) {
    cpu->regs.e = cpu->regs.d;
    return 0;
}

u8 instr_ld_e_e(CPU *cpu) {
    cpu->regs.e = cpu->regs.e;
    return 0;
}

u8 instr_ld_e_h(CPU *cpu) {
    cpu->regs.e = cpu->regs.h;
    return 0;
}

u8 instr_ld_e_l(CPU *cpu) {
    cpu->regs.e = cpu->regs.l;
    return 0;
}

u8 instr_ld_e_a(CPU *cpu) {
    cpu->regs.e = cpu->regs.a;
    return 0;
}

u8 instr_ld_h_b(CPU *cpu) {
    cpu->regs.h = cpu->regs.b;
    return 0;
}

u8 instr_ld_h_c(CPU *cpu) {
    cpu->regs.h = cpu->regs.c;
    return 0;
}

u8 instr_ld_h_d(CPU *cpu) {
    cpu->regs.h = cpu->regs.d;
    return 0;
}

u8 instr_ld_h_e(CPU *cpu) {
    cpu->regs.h = cpu->regs.e;
    return 0;
}

u8 instr_ld_h_h(CPU *cpu) {
    cpu->regs.h = cpu->regs.h;
    return 0;
}

u8 instr_ld_h_l(CPU *cpu) {
    cpu->regs.h = cpu->regs.l;
    return 0;
}

u8 instr_ld_h_a(CPU *cpu) {
    cpu->regs.h = cpu->regs.a;
    return 0;
}

u8 instr_ld_l_b(CPU *cpu) {
    cpu->regs.l = cpu->regs.b;
    return 0;
}

u8 instr_ld_l_c(CPU *cpu) {
    cpu->regs.l = cpu->regs.c;
    return 0;
}

u8 instr_ld_l_d(CPU *cpu) {
    cpu->regs.l = cpu->regs.d;
    return 0;
}

u8 instr_ld_l_e(CPU *cpu) {
    cpu->regs.l = cpu->regs.e;
    return 0;
}

u8 instr_ld_l_h(CPU *cpu) {
    cpu->regs.l = cpu->regs.h;
    return 0;
}

u8 instr_ld_l_l(CPU *cpu) {
    cpu->regs.l = cpu->regs.l;
    return 0;
}

u8 instr_ld_l_a(CPU *cpu) {
    cpu->regs.l = cpu->regs.a;
    return 0;
}

u8 instr_ld_a_b(CPU *cpu) {
    cpu->regs.a = cpu->regs.b;
    return 0;
}

u8 instr_ld_a_c(CPU *cpu) {
    cpu->regs.a = cpu->regs.c;
    return 0;
}

u8 instr_ld_a_d(CPU *cpu) {
    cpu->regs.a = cpu->regs.d;
    return 0;
}

u8 instr_ld_a_e(CPU *cpu) {
    cpu->regs.a = cpu->regs.e;
    return 0;
}

u8 instr_ld_a_h(CPU *cpu) {
    cpu->regs.a = cpu->regs.h;
    return 0;
}

u8 instr_ld_a_l(CPU *cpu) {
    cpu->regs.a = cpu->regs.l;
    return 0;
}

u8 instr_ld_a_a(CPU *cpu) {
    cpu->regs.a = cpu->regs.a;
    return 0;
}

// =================================
// Memory via HL
// =================================

// register <- [hl]
u8 instr_ld_b_mem_hl(CPU *cpu) {
    u16 addr    = cpu_read_hl(cpu);
    cpu->regs.b = mmu_read(cpu->gb, addr);
    return 0;
}

u8 instr_ld_c_mem_hl(CPU *cpu) {
    u16 addr    = cpu_read_hl(cpu);
    cpu->regs.c = mmu_read(cpu->gb, addr);
    return 0;
}

u8 instr_ld_d_mem_hl(CPU *cpu) {
    u16 addr    = cpu_read_hl(cpu);
    cpu->regs.d = mmu_read(cpu->gb, addr);
    return 0;
}

u8 instr_ld_e_mem_hl(CPU *cpu) {
    u16 addr    = cpu_read_hl(cpu);
    cpu->regs.e = mmu_read(cpu->gb, addr);
    return 0;
}

u8 instr_ld_h_mem_hl(CPU *cpu) {
    u16 addr    = cpu_read_hl(cpu);
    cpu->regs.h = mmu_read(cpu->gb, addr);
    return 0;
}

u8 instr_ld_l_mem_hl(CPU *cpu) {
    u16 addr    = cpu_read_hl(cpu);
    cpu->regs.l = mmu_read(cpu->gb, addr);
    return 0;
}

u8 instr_ld_a_mem_hl(CPU *cpu) {
    u16 addr    = cpu_read_hl(cpu);
    cpu->regs.a = mmu_read(cpu->gb, addr);
    return 0;
}

// [hl] <- register
u8 instr_ld_mem_hl_b(CPU *cpu) {
    u16 addr = cpu_read_hl(cpu);
    mmu_write(cpu->gb, addr, cpu->regs.b);
    return 0;
}

u8 instr_ld_mem_hl_c(CPU *cpu) {
    u16 addr = cpu_read_hl(cpu);
    mmu_write(cpu->gb, addr, cpu->regs.c);
    return 0;
}

u8 instr_ld_mem_hl_d(CPU *cpu) {
    u16 addr = cpu_read_hl(cpu);
    mmu_write(cpu->gb, addr, cpu->regs.d);
    return 0;
}

u8 instr_ld_mem_hl_e(CPU *cpu) {
    u16 addr = cpu_read_hl(cpu);
    mmu_write(cpu->gb, addr, cpu->regs.e);
    return 0;
}

u8 instr_ld_mem_hl_h(CPU *cpu) {
    u16 addr = cpu_read_hl(cpu);
    mmu_write(cpu->gb, addr, cpu->regs.h);
    return 0;
}

u8 instr_ld_mem_hl_l(CPU *cpu) {
    u16 addr = cpu_read_hl(cpu);
    mmu_write(cpu->gb, addr, cpu->regs.l);
    return 0;
}

u8 instr_ld_mem_hl_a(CPU *cpu) {
    u16 addr = cpu_read_hl(cpu);
    mmu_write(cpu->gb, addr, cpu->regs.a);
    return 0;
}

// [hl] <- immediate (n)
u8 instr_ld_mem_hl_n(CPU *cpu) {
    u16 addr  = cpu_read_hl(cpu);
    u8  value = mmu_read(cpu->gb, cpu->pc++); // Read immediate value
    mmu_write(cpu->gb, addr, value);
    return 0;
}

// =================================
// Special Memory Loads
// =================================
u8 instr_ld_mem_bc_a(CPU *cpu) {
    u16 addr = cpu_read_bc(cpu);
    mmu_write(cpu->gb, addr, cpu->regs.a);
    return 0;
}

u8 instr_ld_mem_de_a(CPU *cpu) {
    u16 addr = cpu_read_de(cpu);
    mmu_write(cpu->gb, addr, cpu->regs.a);
    return 0;
}

u8 instr_ld_a_mem_bc(CPU *cpu) {
    u16 addr    = cpu_read_bc(cpu);
    cpu->regs.a = mmu_read(cpu->gb, addr);
    return 0;
}

u8 instr_ld_a_mem_de(CPU *cpu) {
    u16 addr    = cpu_read_de(cpu);
    cpu->regs.a = mmu_read(cpu->gb, addr);
    return 0;
}

// https://rgbds.gbdev.io/docs/v1.0.1/gbz80.7#LD__HLI_,A
// [hl] <- a and then increment hl
u8 instr_ld_mem_hli_a(CPU *cpu) {
    u16 addr = cpu_read_hl(cpu);
    mmu_write(cpu->gb, addr, cpu->regs.a);
    cpu_write_hl(cpu, addr + 1); // Increment hl
    return 0;
}

// [hl] <- a and then decrement hl
u8 instr_ld_mem_hld_a(CPU *cpu) {
    u16 addr = cpu_read_hl(cpu);
    mmu_write(cpu->gb, addr, cpu->regs.a);
    cpu_write_hl(cpu, addr - 1); // Decrement hl
    return 0;
}

// a <- [hl] and then decrement hl
u8 instr_ld_a_mem_hld(CPU *cpu) {
    u8 value    = cpu_read_hl(cpu);
    cpu->regs.a = value;
    cpu_write_hl(cpu, value - 1); // Decrement hl
    return 0;
}

// a <- [hl] and then increment hl
u8 instr_ld_a_mem_hli(CPU *cpu) {
    u8 value    = cpu_read_hl(cpu);
    cpu->regs.a = value;
    cpu_write_hl(cpu, value + 1); // Increment hl
    return 0;
}

// [0xFF00 + a8] <- a
u8 instr_ldh_mem_a8_a(CPU *cpu) {
    u8  offset = mmu_read(cpu->gb, cpu->pc++);
    u16 addr   = 0xFF00 + offset;
    mmu_write(cpu->gb, addr, cpu->regs.a);
    return 0;
}

// [0xFF00 + c] <- a
u8 instr_ldh_mem_c_a(CPU *cpu) {
    u8  offset = cpu->regs.c;
    u16 addr   = 0xFF00 + offset;
    mmu_write(cpu->gb, addr, cpu->regs.a);
    return 0;
}

// a <- [0xFF00 + a8]
u8 instr_ldh_a_mem_a8(CPU *cpu) {
    u8  offset  = mmu_read(cpu->gb, cpu->pc++);
    u16 addr    = 0xFF00 + offset;
    cpu->regs.a = mmu_read(cpu->gb, addr);
    return 0;
}

// a <- [0xFF00 + c]
u8 instr_ldh_a_mem_c(CPU *cpu) {
    u8  offset  = cpu->regs.c;
    u16 addr    = 0xFF00 + offset;
    cpu->regs.a = mmu_read(cpu->gb, addr);
    return 0;
}

// [a16] <- a
u8 instr_ld_mem_a16_a(CPU *cpu) {
    u8  lo   = mmu_read(cpu->gb, cpu->pc++);
    u8  hi   = mmu_read(cpu->gb, cpu->pc++);
    u16 addr = MAKE_U16(hi, lo);
    mmu_write(cpu->gb, addr, cpu->regs.a);
    return 0;
}

// a <- [a16]
u8 instr_ld_a_mem_a16(CPU *cpu) {
    u8  lo      = mmu_read(cpu->gb, cpu->pc++);
    u8  hi      = mmu_read(cpu->gb, cpu->pc++);
    u16 addr    = MAKE_U16(hi, lo);
    cpu->regs.a = mmu_read(cpu->gb, addr);
    return 0;
}

// ============================================================================
// 16-bit Load Instructions
// ============================================================================

u8 instr_ld_bc_nn(CPU *cpu) {
    u8 lo = mmu_read(cpu->gb, cpu->pc++);
    u8 hi = mmu_read(cpu->gb, cpu->pc++);
    cpu_write_bc(cpu, MAKE_U16(hi, lo));
    return 0;
}

u8 instr_ld_de_nn(CPU *cpu) {
    u8 lo = mmu_read(cpu->gb, cpu->pc++);
    u8 hi = mmu_read(cpu->gb, cpu->pc++);
    cpu_write_de(cpu, MAKE_U16(hi, lo));
    return 0;
}

u8 instr_ld_hl_nn(CPU *cpu) {
    u8 lo = mmu_read(cpu->gb, cpu->pc++);
    u8 hi = mmu_read(cpu->gb, cpu->pc++);
    cpu_write_hl(cpu, MAKE_U16(hi, lo));
    return 0;
}

u8 instr_ld_sp_nn(CPU *cpu) {
    u8 lo   = mmu_read(cpu->gb, cpu->pc++);
    u8 hi   = mmu_read(cpu->gb, cpu->pc++);
    cpu->sp = MAKE_U16(hi, lo);
    return 0;
}

// ============================================================================
// 8-bit Arithmetic
// https://rgbds.gbdev.io/docs/v1.0.1/gbz80.7#8-bit_arithmetic_instructions
// ============================================================================

// INC r8
// Increment the value in register r8 by 1.
// Flags:
// Z - Set if reselt is zero
// N - 0
// H - Set if overflow from 3rd bit
// ----------------------------------------------
u8 instr_inc_b(CPU *cpu) {
    u8   result    = cpu->regs.b + 1;

    // Preserve carry flag
    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = 0;

    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;     // Set Z if result = 0
    if ((cpu->regs.b & 0x0F) == 0x0F) // Set H if lower nibble overlfows
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY; // Restore C (if it was set)

    cpu->regs.b = result;
    return 0;
}

u8 instr_inc_c(CPU *cpu) {
    u8   result    = cpu->regs.c + 1;

    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if ((cpu->regs.c & 0x0F) == 0x0F)
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.c = result;
    return 0;
}

u8 instr_inc_d(CPU *cpu) {
    u8   result    = cpu->regs.d + 1;

    // Preserve carry flag
    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = 0;

    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if ((cpu->regs.d & 0x0F) == 0x0F)
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.d = result;
    return 0;
}

u8 instr_inc_e(CPU *cpu) {
    u8   result    = cpu->regs.e + 1;

    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = 0;

    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if ((cpu->regs.e & 0x0F) == 0x0F)
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.e = result;
    return 0;
}

u8 instr_inc_h(CPU *cpu) {
    u8   result    = cpu->regs.h + 1;

    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = 0;

    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if ((cpu->regs.h & 0x0F) == 0x0F)
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.h = result;
    return 0;
}

u8 instr_inc_l(CPU *cpu) {
    u8   result    = cpu->regs.l + 1;

    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = 0;

    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if ((cpu->regs.l & 0x0F) == 0x0F)
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.l = result;
    return 0;
}

u8 instr_inc_a(CPU *cpu) {
    u8   result    = cpu->regs.a + 1;

    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = 0;

    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if ((cpu->regs.a & 0x0F) == 0x0F)
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

// DEC r8
// Decrement the value in register r8 by 1.
// Flags:
// Z - Set if reselt is zero
// N - 1
// H - Set if borrow from 4th bit
// ----------------------------------------------
u8 instr_dec_b(CPU *cpu) {
    u8   result    = cpu->regs.b - 1;

    // Preserve carry flag
    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;  // Set Z if result is zero
    if ((cpu->regs.b & 0x0F) == 0) // Set H if lower nibble underflows
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY; // Restore the carry flag

    cpu->regs.b = result;
    return 0;
}

u8 instr_dec_c(CPU *cpu) {
    u8   result    = cpu->regs.c - 1;

    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if ((cpu->regs.c & 0x0F) == 0)
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.c = result;
    return 0;
}

u8 instr_dec_d(CPU *cpu) {
    u8   result    = cpu->regs.d - 1;

    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if ((cpu->regs.d & 0x0F) == 0)
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.d = result;
    return 0;
}

u8 instr_dec_e(CPU *cpu) {
    u8   result    = cpu->regs.e - 1;

    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if ((cpu->regs.e & 0x0F) == 0)
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.e = result;
    return 0;
}

u8 instr_dec_h(CPU *cpu) {
    u8   result    = cpu->regs.h - 1;

    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if ((cpu->regs.h & 0x0F) == 0)
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.h = result;
    return 0;
}

u8 instr_dec_l(CPU *cpu) {
    u8   result    = cpu->regs.l - 1;

    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if ((cpu->regs.l & 0x0F) == 0)
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.l = result;
    return 0;
}

u8 instr_dec_a(CPU *cpu) {
    u8   result    = cpu->regs.a - 1;

    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if ((cpu->regs.a & 0x0F) == 0)
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

// ADD A, r8
// a <- a + r8
// Flags:
// Z - Set if reselt is zero
// N - 0
// H - Set if overflow from bit 3
// C - Set if overflow from bit 7
// ----------------------------------------------
u8 instr_add_a_b(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 b        = cpu->regs.b;
    u8 result   = a + b;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_add(a, b))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_add(a, b))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_add_a_c(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 c        = cpu->regs.c;
    u8 result   = a + c;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_add(a, c))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_add(a, c))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_add_a_d(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 d        = cpu->regs.d;
    u8 result   = a + d;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_add(a, d))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_add(a, d))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_add_a_e(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 e        = cpu->regs.e;
    u8 result   = a + e;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_add(a, e))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_add(a, e))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_add_a_h(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 h        = cpu->regs.h;
    u8 result   = a + h;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_add(a, h))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_add(a, h))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_add_a_l(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 l        = cpu->regs.l;
    u8 result   = a + l;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_add(a, l))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_add(a, l))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_add_a_a(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 result   = a + a;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_add(a, a))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_add(a, a))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_add_a_mem_hl(CPU *cpu) {
    u8  a       = cpu->regs.a;
    u16 address = cpu_read_hl(cpu);
    u8  value   = mmu_read(cpu->gb, address);
    u8  result  = a + value;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_add(a, a))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_add(a, a))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_add_a_n(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 n        = mmu_read(cpu->gb, cpu->pc++);
    u8 result   = a + n;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_add(a, n))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_add(a, n))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

// ADC A, r8
// a <- a + r8 + Carry flag
// Flags:
// Z - Set if reselt is zero
// N - 0
// H - Set if overflow from bit 3
// C - Set if overflow from bit 7
// ----------------------------------------------
u8 instr_adc_a_b(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 b        = cpu->regs.b;
    u8 carry    = cpu_get_flag(cpu, FLAG_CARRY) ? 1 : 0;
    u8 result   = a + b + carry;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_adc(a, b, carry))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_adc(a, b, carry))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_adc_a_c(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 c        = cpu->regs.c;
    u8 carry    = cpu_get_flag(cpu, FLAG_CARRY) ? 1 : 0;
    u8 result   = a + c + carry;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_adc(a, c, carry))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_adc(a, c, carry))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_adc_a_d(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 d        = cpu->regs.d;
    u8 carry    = cpu_get_flag(cpu, FLAG_CARRY) ? 1 : 0;
    u8 result   = a + d + carry;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_adc(a, d, carry))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_adc(a, d, carry))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_adc_a_e(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 e        = cpu->regs.e;
    u8 carry    = cpu_get_flag(cpu, FLAG_CARRY) ? 1 : 0;
    u8 result   = a + e + carry;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_adc(a, e, carry))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_adc(a, e, carry))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_adc_a_h(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 h        = cpu->regs.h;
    u8 carry    = cpu_get_flag(cpu, FLAG_CARRY) ? 1 : 0;
    u8 result   = a + h + carry;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_adc(a, h, carry))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_adc(a, h, carry))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_adc_a_l(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 l        = cpu->regs.l;
    u8 carry    = cpu_get_flag(cpu, FLAG_CARRY) ? 1 : 0;
    u8 result   = a + l + carry;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_adc(a, l, carry))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_adc(a, l, carry))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_adc_a_a(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 carry    = cpu_get_flag(cpu, FLAG_CARRY) ? 1 : 0;
    u8 result   = a + a + carry;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_adc(a, a, carry))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_adc(a, a, carry))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_adc_a_mem_hl(CPU *cpu) {
    u8  a       = cpu->regs.a;
    u8  carry   = cpu_get_flag(cpu, FLAG_CARRY) ? 1 : 0;
    u16 addr    = cpu_read_hl(cpu);
    u8  value   = mmu_read(cpu->gb, addr);
    u8  result  = a + value + carry;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_adc(a, value, carry))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_adc(a, value, carry))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_adc_a_n(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 carry    = cpu_get_flag(cpu, FLAG_CARRY) ? 1 : 0;
    u8 value    = mmu_read(cpu->gb, cpu->pc++);
    u8 result   = a + value + carry;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_adc(a, value, carry))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_adc(a, value, carry))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

// SUB A, r8
// a <- a - r8
// Flags:
// Z - Set if reselt is zero
// N - 1
// H - Set if borrow from bit 4
// C - Set if borrow (r8 > A)
// ----------------------------------------------
u8 instr_sub_a_b(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 b        = cpu->regs.b;
    u8 result   = a - b;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sub(a, b))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sub(a, b))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_sub_a_c(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 c        = cpu->regs.c;
    u8 result   = a - c;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sub(a, c))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sub(a, c))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_sub_a_d(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 d        = cpu->regs.d;
    u8 result   = a - d;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sub(a, d))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sub(a, d))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_sub_a_e(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 e        = cpu->regs.e;
    u8 result   = a - e;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sub(a, e))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sub(a, e))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_sub_a_h(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 h        = cpu->regs.h;
    u8 result   = a - h;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sub(a, h))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sub(a, h))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_sub_a_l(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 l        = cpu->regs.l;
    u8 result   = a - l;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sub(a, l))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sub(a, l))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_sub_a_a(CPU *cpu) {
    cpu->regs.a = 0;
    cpu->regs.f = FLAG_ZERO | FLAG_SUBT; // Z=1, N=1, H=0, C=0
    return 0;
}

u8 instr_sub_a_mem_hl(CPU *cpu) {
    u8  a       = cpu->regs.a;
    u16 address = cpu_read_hl(cpu);
    u8  value   = mmu_read(cpu->gb, address);
    u8  result  = a - value;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sub(a, value))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sub(a, value))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_sub_a_n(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 n        = mmu_read(cpu->gb, cpu->pc++);
    u8 result   = a - n;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sub(a, n))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sub(a, n))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

// SBC A, r8
// a <- a - r8 - carry
// Flags:
// Z - Set if reselt is zero
// N - 1
// H - Set if borrow from bit 4
// C - Set if borrow (r8 + carry > A)
// ----------------------------------------------
u8 instr_sbc_a_b(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 b        = cpu->regs.b;
    u8 carry    = cpu_get_flag(cpu, FLAG_CARRY);
    u8 result   = a - b - carry;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sbc(a, b, carry))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sbc(a, b, carry))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_sbc_a_c(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 c        = cpu->regs.c;
    u8 carry    = cpu_get_flag(cpu, FLAG_CARRY);
    u8 result   = a - c - carry;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sbc(a, c, carry))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sbc(a, c, carry))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_sbc_a_d(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 d        = cpu->regs.d;
    u8 carry    = cpu_get_flag(cpu, FLAG_CARRY);
    u8 result   = a - d - carry;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sbc(a, d, carry))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sbc(a, d, carry))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_sbc_a_e(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 e        = cpu->regs.e;
    u8 carry    = cpu_get_flag(cpu, FLAG_CARRY);
    u8 result   = a - e - carry;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sbc(a, e, carry))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sbc(a, e, carry))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_sbc_a_h(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 h        = cpu->regs.h;
    u8 carry    = cpu_get_flag(cpu, FLAG_CARRY);
    u8 result   = a - h - carry;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sbc(a, h, carry))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sbc(a, h, carry))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_sbc_a_l(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 l        = cpu->regs.l;
    u8 carry    = cpu_get_flag(cpu, FLAG_CARRY);
    u8 result   = a - l - carry;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sbc(a, l, carry))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sbc(a, l, carry))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_sbc_a_a(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 carry    = cpu_get_flag(cpu, FLAG_CARRY);
    u8 result   = a - a - carry;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (carry) {
        cpu->regs.f |= FLAG_HF_CARRY;
        cpu->regs.f |= FLAG_CARRY;
    }

    cpu->regs.a = result;
    return 0;
}

u8 instr_sbc_a_mem_hl(CPU *cpu) {
    u8  a       = cpu->regs.a;
    u8  carry   = cpu_get_flag(cpu, FLAG_CARRY);
    u16 addr    = cpu_read_hl(cpu);
    u8  value   = mmu_read(cpu->gb, addr);
    u8  result  = a - value - carry;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sbc(a, value, carry))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sbc(a, value, carry))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_sbc_a_n(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 carry    = cpu_get_flag(cpu, FLAG_CARRY);
    u8 n        = mmu_read(cpu->gb, cpu->pc++);
    u8 result   = a - n - carry;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sbc(a, n, carry))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sbc(a, n, carry))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

// ============================================================================
// Bitwise Logic Instructions
// https://rgbds.gbdev.io/docs/v1.0.1/gbz80.7#Bitwise_logic_instructions
// ============================================================================

// AND A, r8
// [A] <- A AND r8
// Fags:
// Z - Set if reselt is zero
// N - 0
// H - 1
// C - 0
// ----------------------------------------------
u8 instr_and_a_b(CPU *cpu) {
    u8 result   = cpu->regs.a & cpu->regs.b;

    cpu->regs.f = FLAG_HF_CARRY;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_and_a_c(CPU *cpu) {
    u8 result   = cpu->regs.a & cpu->regs.c;

    cpu->regs.f = FLAG_HF_CARRY;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_and_a_d(CPU *cpu) {
    u8 result   = cpu->regs.a & cpu->regs.d;

    cpu->regs.f = FLAG_HF_CARRY;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_and_a_e(CPU *cpu) {
    u8 result   = cpu->regs.a & cpu->regs.e;

    cpu->regs.f = FLAG_HF_CARRY;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_and_a_h(CPU *cpu) {
    u8 result   = cpu->regs.a & cpu->regs.h;

    cpu->regs.f = FLAG_HF_CARRY;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_and_a_l(CPU *cpu) {
    u8 result   = cpu->regs.a & cpu->regs.l;

    cpu->regs.f = FLAG_HF_CARRY;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_and_a_a(CPU *cpu) {
    cpu->regs.f = FLAG_HF_CARRY;
    if (cpu->regs.a == 0)
        cpu->regs.f |= FLAG_ZERO;

    return 0;
}

u8 instr_and_a_hl(CPU *cpu) {
    u16 addr    = cpu_read_hl(cpu);
    u8  value   = mmu_read(cpu->gb, addr);
    u8  result  = cpu->regs.a & value;

    cpu->regs.f = FLAG_HF_CARRY;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_and_a_n(CPU *cpu) {
    u8 n        = mmu_read(cpu->gb, cpu->pc++);
    u8 result   = cpu->regs.a & n;

    cpu->regs.f = FLAG_HF_CARRY;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

// OR A, r8
// [A] <- A OR r8
// Fags:
// Z - Set if reselt is zero
// N - 0
// H - 0
// C - 0
// ----------------------------------------------
u8 instr_or_a_b(CPU *cpu) {
    u8 result   = cpu->regs.a | cpu->regs.b;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_or_a_c(CPU *cpu) {
    u8 result   = cpu->regs.a | cpu->regs.c;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_or_a_d(CPU *cpu) {
    u8 result   = cpu->regs.a | cpu->regs.d;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_or_a_e(CPU *cpu) {
    u8 result   = cpu->regs.a | cpu->regs.e;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_or_a_h(CPU *cpu) {
    u8 result   = cpu->regs.a | cpu->regs.h;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_or_a_l(CPU *cpu) {
    u8 result   = cpu->regs.a | cpu->regs.l;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_or_a_a(CPU *cpu) {
    cpu->regs.f = 0;
    if (cpu->regs.a == 0)
        cpu->regs.f |= FLAG_ZERO;

    return 0;
}

u8 instr_or_a_hl(CPU *cpu) {
    u16 addr    = cpu_read_hl(cpu);
    u8  value   = mmu_read(cpu->gb, addr);
    u8  result  = cpu->regs.a | value;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_or_a_n(CPU *cpu) {
    u8 value    = mmu_read(cpu->gb, cpu->pc++);
    u8 result   = cpu->regs.a | value;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

// XOR A, r8
// [A] <- A XOR r8
// Fags:
// Z - Set if reselt is zero
// N - 0
// H - 0
// C - 0
// ----------------------------------------------
u8 instr_xor_a_b(CPU *cpu) {
    u8 result   = cpu->regs.a ^ cpu->regs.b;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_xor_a_c(CPU *cpu) {
    u8 result   = cpu->regs.a ^ cpu->regs.c;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_xor_a_d(CPU *cpu) {
    u8 result   = cpu->regs.a ^ cpu->regs.d;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_xor_a_e(CPU *cpu) {
    u8 result   = cpu->regs.a ^ cpu->regs.e;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_xor_a_h(CPU *cpu) {
    u8 result   = cpu->regs.a ^ cpu->regs.h;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_xor_a_l(CPU *cpu) {
    u8 result   = cpu->regs.a ^ cpu->regs.l;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_xor_a_a(CPU *cpu) {
    cpu->regs.f = FLAG_ZERO;
    cpu->regs.a = 0;
    return 0;
}

u8 instr_xor_a_hl(CPU *cpu) {
    u16 addr    = cpu_read_hl(cpu);
    u8  value   = mmu_read(cpu->gb, addr);
    u8  result  = cpu->regs.a ^ value;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

u8 instr_xor_a_n(CPU *cpu) {
    u8 value    = mmu_read(cpu->gb, cpu->pc++);
    u8 result   = cpu->regs.a ^ value;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;

    cpu->regs.a = result;
    return 0;
}

// CP A, r8
// Compare the value in A with the value in r8
// A - r8 and set the flags accordingly && discard result
// Flags:
// Z - Set if reselt is zero
// N - 1
// H - Set if borrow from bit 4
// C - Set if borrow (r8 > A)
// ----------------------------------------------
u8 instr_cp_a_b(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 b        = cpu->regs.b;
    u8 result   = a - b;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sub(a, b))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sub(a, b))
        cpu->regs.f |= FLAG_CARRY;

    return 0;
}

u8 instr_cp_a_c(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 c        = cpu->regs.c;
    u8 result   = a - c;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sub(a, c))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sub(a, c))
        cpu->regs.f |= FLAG_CARRY;

    return 0;
}

u8 instr_cp_a_d(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 d        = cpu->regs.d;
    u8 result   = a - d;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sub(a, d))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sub(a, d))
        cpu->regs.f |= FLAG_CARRY;

    return 0;
}

u8 instr_cp_a_e(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 e        = cpu->regs.e;
    u8 result   = a - e;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sub(a, e))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sub(a, e))
        cpu->regs.f |= FLAG_CARRY;

    return 0;
}

u8 instr_cp_a_h(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 h        = cpu->regs.h;
    u8 result   = a - h;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sub(a, h))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sub(a, h))
        cpu->regs.f |= FLAG_CARRY;

    return 0;
}

u8 instr_cp_a_l(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 l        = cpu->regs.l;
    u8 result   = a - l;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sub(a, l))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sub(a, l))
        cpu->regs.f |= FLAG_CARRY;

    return 0;
}

u8 instr_cp_a_a(CPU *cpu) {
    cpu->regs.f = FLAG_SUBT | FLAG_ZERO;
    return 0;
}

u8 instr_cp_a_hl(CPU *cpu) {
    u8  a       = cpu->regs.a;
    u16 addr    = cpu_read_hl(cpu);
    u8  value   = mmu_read(cpu->gb, addr);
    u8  result  = a - value;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sub(a, value))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sub(a, value))
        cpu->regs.f |= FLAG_CARRY;

    return 0;
}

u8 instr_cp_a_n(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 n        = mmu_read(cpu->gb, cpu->pc++);
    u8 result   = a - n;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sub(a, n))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sub(a, n))
        cpu->regs.f |= FLAG_CARRY;

    return 0;
}

// ============================================================================
// 16 - bit Aarithmetic Instructions
// https://rgbds.gbdev.io/docs/v1.0.1/gbz80.7#16-bit_arithmetic_instructions
// ============================================================================

// ADD HL, r16
// HL <- r16
// Flags:
// N - 0
// H - Set if overflow from bit 11
// C - Set if overflow from bit 15
// ----------------------------------------------
u8 instr_add_hl_bc(CPU *cpu) {
    u16 hl       = cpu_read_hl(cpu);
    u16 bc       = cpu_read_bc(cpu);
    u16 result   = hl + bc;

    // Preserve Z flag
    u8  old_flag = cpu_get_flag(cpu, FLAG_ZERO);

    cpu->regs.f  = 0;
    if (check_half_carry_add_u16(hl, bc))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_add_u16(hl, bc))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.f |= old_flag; // Restore Z flag
    cpu_write_hl(cpu, result);
    return 0;
}

u8 instr_add_hl_de(CPU *cpu) {
    u16 hl       = cpu_read_hl(cpu);
    u16 de       = cpu_read_de(cpu);
    u16 result   = hl + de;

    // Preserve Z flag
    u8  old_flag = cpu_get_flag(cpu, FLAG_ZERO);

    cpu->regs.f  = 0;
    if (check_half_carry_add_u16(hl, de))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_add_u16(hl, de))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.f |= old_flag; // Restore Z flag
    cpu_write_hl(cpu, result);
    return 0;
}

u8 instr_add_hl_hl(CPU *cpu) {
    u16 hl       = cpu_read_hl(cpu);
    u16 result   = hl + hl;

    // Preserve Z flag
    u8  old_flag = cpu_get_flag(cpu, FLAG_ZERO);

    cpu->regs.f  = 0;
    if (check_half_carry_add_u16(hl, hl))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_add_u16(hl, hl))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.f |= old_flag; // Restore Z flag
    cpu_write_hl(cpu, result);
    return 0;
}

u8 instr_add_hl_sp(CPU *cpu) {
    u16 hl       = cpu_read_hl(cpu);
    u16 sp       = cpu->sp;
    u16 result   = hl + sp;

    // Preserve Z flag
    u8  old_flag = cpu_get_flag(cpu, FLAG_ZERO);

    cpu->regs.f  = 0;
    if (check_half_carry_add_u16(hl, sp))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_add_u16(hl, sp))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.f |= old_flag; // Restore Z flag
    cpu_write_hl(cpu, result);
    return 0;
}

// add sp, e8
// Flags:
// Z - 0
// N - 0
// H - Set if overflow from bit 3
// C - Set if overflow from bit 7
// ----------------------------------------------
u8 instr_add_sp_e8(CPU *cpu) {
    i8  e8      = (i8)mmu_read(cpu->gb, cpu->pc++);
    u16 sp      = cpu->sp;
    u16 result  = sp + e8;

    u8  sp_low  = sp & 0xFF;
    u8  val     = (u8)e8;

    cpu->regs.f = 0;

    if (check_half_carry_add(sp_low, val))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_add(sp_low, val))
        cpu->regs.f |= FLAG_CARRY;

    cpu->sp = result;
    return 0;
}

// INC r16
// Flags:
// None Affected
// ----------------------------------------------
u8 instr_inc_bc(CPU *cpu) {
    u16 bc = cpu_read_bc(cpu);
    cpu_write_bc(cpu, ++bc);
    return 0;
}

u8 instr_inc_de(CPU *cpu) {
    u16 de = cpu_read_de(cpu);
    cpu_write_bc(cpu, ++de);
    return 0;
}

u8 instr_inc_hl(CPU *cpu) {
    u16 hl = cpu_read_hl(cpu);
    cpu_write_bc(cpu, ++hl);
    return 0;
}

u8 instr_inc_sp(CPU *cpu) {
    cpu->sp++;
    return 0;
}

// DEC r16
// Flags:
// None Affected
// ----------------------------------------------
u8 instr_dec_bc(CPU *cpu) {
    u16 bc = cpu_read_bc(cpu);
    cpu_write_bc(cpu, --bc);
    return 0;
}

u8 instr_dec_de(CPU *cpu) {
    u16 de = cpu_read_de(cpu);
    cpu_write_bc(cpu, --de);
    return 0;
}

u8 instr_dec_hl(CPU *cpu) {
    u16 hl = cpu_read_hl(cpu);
    cpu_write_bc(cpu, --hl);
    return 0;
}

u8 instr_dec_sp(CPU *cpu) {
    cpu->sp--;
    return 0;
}

// ============================================================================
// Control Flow
// ============================================================================

u8 instr_jp_nn(CPU *cpu) {
    u8 lo   = mmu_read(cpu->gb, cpu->pc++);
    u8 hi   = mmu_read(cpu->gb, cpu->pc++);
    cpu->pc = MAKE_U16(hi, lo);
    return 0;
}

u8 instr_jr_n(CPU *cpu) {
    i8 offset = (i8)mmu_read(cpu->gb, cpu->pc++);
    cpu->pc += offset;
    return 0;
}
