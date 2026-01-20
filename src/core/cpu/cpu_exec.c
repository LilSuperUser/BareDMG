// src/core/cpu/cpu_exec.c
#include <core/cpu/cpu.h>
#include <core/cpu/cpu_exec.h>
#include <core/bus.h>
#include <gbemu.h>
#include <core/utils.h>

// ============================================================================
// NOTE: CPU Control
// ============================================================================
u8 instr_nop(CPU *cpu) {
    (void)cpu;
    return 0;
}

// NOTE: Full STOP implementation requires joypad
// therefore, for now we treat it as HALT
u8 instr_stop(CPU *cpu) {
    // Read and discard the next byte (always 0x00)
    mmu_read(cpu->gb, cpu->pc++);

    // Set CPU to stopped state
    cpu->halted = true; // Use halted flag for now

    // TODO: When implementing joypad:
    // - Stop CPU clock
    // - Stop LCD display
    // - Wake on button press

    return 0;
}

u8 instr_halt(CPU *cpu) {
    cpu->halted = true;

    // TODO: When implementing interrupts:
    // - CPU enters low-power mode
    // - Wakes up when interrupt occurs (even if IME is disabled)
    // - If IME is enabled, interrupt handler runs
    // - If IME is disabled, execution continues after HALT
    return 0;
}

// Disable interrupts
u8 instr_di(CPU *cpu) {
    cpu->ime = false;
    return 0;
}

// Enable interrupts
u8 instr_ei(CPU *cpu) {
    cpu->ime_scheduled = true; // Set after NEXT instruction
    return 0;
}

// TODO: When implementing extended instruction set
/* u8 instr_prefix_cb(CPU *cpu); */

// ============================================================================
// NOTE: 8-bit Load Instructions
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
// NOTE: Memory via HL
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

// ld hl, sp+e8
u8 instr_ld_hl_sp_e8(CPU *cpu) {
    i8  e8      = (i8)mmu_read(cpu->gb, cpu->pc++);
    u16 sp      = cpu->sp;
    u16 result  = sp + e8;

    u8  sp_low  = sp & 0xFF;
    u8  val     = (u8)e8;

    cpu->regs.f = 0; // Z=0, N=0

    if (check_half_carry_add(sp_low, val))
        cpu->regs.f |= FLAG_HF_CARRY;

    if (check_carry_add(sp_low, val))
        cpu->regs.f |= FLAG_CARRY;

    cpu_write_hl(cpu, result);
    return 0;
}

// ld sp, hl
u8 instr_ld_sp_hl(CPU *cpu) {
    cpu->sp = cpu_read_hl(cpu);
    return 0;
}

// =================================
// NOTE: Special Memory Loads
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

// [a16] <- SP
u8 instr_ld_mem_a16_sp(CPU *cpu) {
    u8  lo   = mmu_read(cpu->gb, cpu->pc++);
    u8  hi   = mmu_read(cpu->gb, cpu->pc++);
    u16 addr = MAKE_U16(hi, lo);

    u16 sp   = cpu->sp;

    mmu_write(cpu->gb, addr, GET_LOW_BYTE(sp));
    mmu_write(cpu->gb, addr + 1, GET_HIGH_BYTE(sp));

    return 0;
}

// ============================================================================
// NOTE: 16-bit Load Instructions
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
// NOTE: 8-bit Arithmetic
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

u8 instr_inc_mem_hl(CPU *cpu) {
    u16  addr      = cpu_read_hl(cpu);
    u8   value     = mmu_read(cpu->gb, addr);
    u8   result    = value + 1;

    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = 0;

    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if ((value & 0x0F) == 0x0F)
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY;

    mmu_write(cpu->gb, addr, result);
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

u8 instr_dec_mem_hl(CPU *cpu) {
    u16  addr      = cpu_read_hl(cpu);
    u8   value     = mmu_read(cpu->gb, addr);
    u8   result    = value - 1;

    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if ((value & 0x0F) == 0)
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY;

    mmu_write(cpu->gb, addr, result);
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
// NOTE: Bitwise Logic Instructions
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

u8 instr_and_a_mem_hl(CPU *cpu) {
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

u8 instr_or_a_mem_hl(CPU *cpu) {
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

u8 instr_xor_a_mem_hl(CPU *cpu) {
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

u8 instr_cp_a_mem_hl(CPU *cpu) {
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
// NOTE: 16 - bit Aarithmetic Instructions
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
// NOTE: Stack Manipulation Instructions
// https://rgbds.gbdev.io/docs/v1.0.1/gbz80.7#Stack_manipulation_instructions
// ============================================================================

// PUSH r16
// push regisrter r16 onto stack
// Flags:
// None affected
// ----------------------------------------------
u8 instr_push_bc(CPU *cpu) {
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, cpu->regs.b);
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, cpu->regs.c);
    return 0;
}

u8 instr_push_de(CPU *cpu) {
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, cpu->regs.d);
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, cpu->regs.e);
    return 0;
}

u8 instr_push_hl(CPU *cpu) {
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, cpu->regs.h);
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, cpu->regs.l);
    return 0;
}

u8 instr_push_af(CPU *cpu) {
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, cpu->regs.a);
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, cpu->regs.f);
    return 0;
}

// POP r16
// pop regisrter r16 from stack
// Flags:
// None affected
// ----------------------------------------------
u8 instr_pop_bc(CPU *cpu) {
    cpu->regs.c = mmu_read(cpu->gb, cpu->sp++);
    cpu->regs.b = mmu_read(cpu->gb, cpu->sp++);
    return 0;
}

u8 instr_pop_de(CPU *cpu) {
    cpu->regs.e = mmu_read(cpu->gb, cpu->sp++);
    cpu->regs.d = mmu_read(cpu->gb, cpu->sp++);
    return 0;
}

u8 instr_pop_hl(CPU *cpu) {
    cpu->regs.l = mmu_read(cpu->gb, cpu->sp++);
    cpu->regs.h = mmu_read(cpu->gb, cpu->sp++);
    return 0;
}

u8 instr_pop_af(CPU *cpu) {
    cpu->regs.f = mmu_read(cpu->gb, cpu->sp++);
    cpu->regs.a = mmu_read(cpu->gb, cpu->sp++);
    return 0;
}

// Restart Vectors
u8 instr_rst_00(CPU *cpu) {
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, GET_HIGH_BYTE(cpu->pc));
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, GET_LOW_BYTE(cpu->pc));
    cpu->pc = 0x00;
    return 0;
}

u8 instr_rst_08(CPU *cpu) {
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, GET_HIGH_BYTE(cpu->pc));
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, GET_LOW_BYTE(cpu->pc));
    cpu->pc = 0x08;
    return 0;
}

u8 instr_rst_10(CPU *cpu) {
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, GET_HIGH_BYTE(cpu->pc));
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, GET_LOW_BYTE(cpu->pc));
    cpu->pc = 0x10;
    return 0;
}

u8 instr_rst_18(CPU *cpu) {
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, GET_HIGH_BYTE(cpu->pc));
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, GET_LOW_BYTE(cpu->pc));
    cpu->pc = 0x18;
    return 0;
}

u8 instr_rst_20(CPU *cpu) {
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, GET_HIGH_BYTE(cpu->pc));
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, GET_LOW_BYTE(cpu->pc));
    cpu->pc = 0x20;
    return 0;
}

u8 instr_rst_28(CPU *cpu) {
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, GET_HIGH_BYTE(cpu->pc));
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, GET_LOW_BYTE(cpu->pc));
    cpu->pc = 0x28;
    return 0;
}

u8 instr_rst_30(CPU *cpu) {
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, GET_HIGH_BYTE(cpu->pc));
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, GET_LOW_BYTE(cpu->pc));
    cpu->pc = 0x30;
    return 0;
}

u8 instr_rst_38(CPU *cpu) {
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, GET_HIGH_BYTE(cpu->pc));
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, GET_LOW_BYTE(cpu->pc));
    cpu->pc = 0x38;
    return 0;
}

// ============================================================================
// NOTE: Jumps & Sub-routine instructions
// https://rgbds.gbdev.io/docs/v1.0.1/gbz80.7#Jumps_and_subroutine_instructions
// ============================================================================

// JP a16
// Jump to 16-bit address (a16)
// Flags:
// None affected
// ----------------------------------------------
u8 instr_jp_a16(CPU *cpu) {
    u8 lo   = mmu_read(cpu->gb, cpu->pc++);
    u8 hi   = mmu_read(cpu->gb, cpu->pc++);
    cpu->pc = MAKE_U16(hi, lo);
    return 0;
}

// JP HL
// Jump to 16-bit address (a16)
// Flags:
// None affected
// ----------------------------------------------
u8 instr_jp_hl(CPU *cpu) {
    cpu->pc = cpu_read_hl(cpu);
    return 0;
}

// JP cc a16
// Jump to 16-bit address if cc condition is met
// cc:
// nz, z, nc, c
// Flags:
// None affected
// ----------------------------------------------
u8 instr_jp_nz_a16(CPU *cpu) {
    u8 lo = mmu_read(cpu->gb, cpu->pc++);
    u8 hi = mmu_read(cpu->gb, cpu->pc++);

    if (!cpu_get_flag(cpu, FLAG_ZERO))
        cpu->pc = MAKE_U16(hi, lo);

    return 0;
}

u8 instr_jp_z_a16(CPU *cpu) {
    u8 lo = mmu_read(cpu->gb, cpu->pc++);
    u8 hi = mmu_read(cpu->gb, cpu->pc++);

    if (cpu_get_flag(cpu, FLAG_ZERO))
        cpu->pc = MAKE_U16(hi, lo);

    return 0;
}

u8 instr_jp_nc_a16(CPU *cpu) {
    u8 lo = mmu_read(cpu->gb, cpu->pc++);
    u8 hi = mmu_read(cpu->gb, cpu->pc++);

    if (!cpu_get_flag(cpu, FLAG_CARRY))
        cpu->pc = MAKE_U16(hi, lo);

    return 0;
}

u8 instr_jp_c_a16(CPU *cpu) {
    u8 lo = mmu_read(cpu->gb, cpu->pc++);
    u8 hi = mmu_read(cpu->gb, cpu->pc++);

    if (cpu_get_flag(cpu, FLAG_CARRY))
        cpu->pc = MAKE_U16(hi, lo);

    return 0;
}

// JR e8
// Relative jump to 16-bit address (a16)
// Flags:
// None affected
// ----------------------------------------------
u8 instr_jr_e8(CPU *cpu) {
    i8 offset = (i8)mmu_read(cpu->gb, cpu->pc++);
    cpu->pc += offset;
    return 0;
}

// JR cc e8
// Relative jump to 16-bit address if cc condition is met
// cc:
// nz, z, nc, c
// Flags:
// None affected
// ----------------------------------------------
u8 instr_jr_nz_e8(CPU *cpu) {
    i8 offset = (i8)mmu_read(cpu->gb, cpu->pc++);

    if (!cpu_get_flag(cpu, FLAG_ZERO))
        cpu->pc += offset;

    return 0;
}

u8 instr_jr_z_e8(CPU *cpu) {
    i8 offset = (i8)mmu_read(cpu->gb, cpu->pc++);

    if (cpu_get_flag(cpu, FLAG_ZERO))
        cpu->pc += offset;

    return 0;
}

u8 instr_jr_nc_e8(CPU *cpu) {
    i8 offset = (i8)mmu_read(cpu->gb, cpu->pc++);

    if (!cpu_get_flag(cpu, FLAG_CARRY))
        cpu->pc += offset;

    return 0;
}

u8 instr_jr_c_e8(CPU *cpu) {
    i8 offset = (i8)mmu_read(cpu->gb, cpu->pc++);

    if (cpu_get_flag(cpu, FLAG_CARRY))
        cpu->pc += offset;

    return 0;
}

// JP a16
// pushes the return address onto the stack, then jumps
// Flags:
// None affected
// ----------------------------------------------
u8 instr_call_a16(CPU *cpu) {
    u8  lo   = mmu_read(cpu->gb, cpu->pc++);
    u8  hi   = mmu_read(cpu->gb, cpu->pc++);
    u16 addr = MAKE_U16(hi, lo);

    // Push return address onto stack
    cpu->sp--;
    mmu_write(cpu->gb, cpu->sp, GET_HIGH_BYTE(cpu->pc));
    mmu_write(cpu->gb, cpu->sp, GET_LOW_BYTE(cpu->pc));

    // Update the pc
    cpu->pc = addr;
    return 0;
}

// JP cc a16
// Jump to 16-bit address if cc condition is met
// cc:
// nz, z, nc, c
// Flags:
// None affected
// ----------------------------------------------
u8 instr_call_nz_a16(CPU *cpu) {
    u8  lo   = mmu_read(cpu->gb, cpu->pc++);
    u8  hi   = mmu_read(cpu->gb, cpu->pc++);
    u16 addr = MAKE_U16(hi, lo);

    if (!cpu_get_flag(cpu, FLAG_ZERO)) {
        cpu->sp--;
        mmu_write(cpu->gb, cpu->sp, GET_HIGH_BYTE(cpu->pc));
        mmu_write(cpu->gb, cpu->sp, GET_LOW_BYTE(cpu->pc));

        cpu->pc = addr;
    }
    return 0;
}

u8 instr_call_z_a16(CPU *cpu) {
    u8  lo   = mmu_read(cpu->gb, cpu->pc++);
    u8  hi   = mmu_read(cpu->gb, cpu->pc++);
    u16 addr = MAKE_U16(hi, lo);

    if (cpu_get_flag(cpu, FLAG_ZERO)) {
        cpu->sp--;
        mmu_write(cpu->gb, cpu->sp, GET_HIGH_BYTE(cpu->pc));
        mmu_write(cpu->gb, cpu->sp, GET_LOW_BYTE(cpu->pc));

        cpu->pc = addr;
    }
    return 0;
}

u8 instr_call_nc_a16(CPU *cpu) {
    u8  lo   = mmu_read(cpu->gb, cpu->pc++);
    u8  hi   = mmu_read(cpu->gb, cpu->pc++);
    u16 addr = MAKE_U16(hi, lo);

    if (!cpu_get_flag(cpu, FLAG_CARRY)) {
        cpu->sp--;
        mmu_write(cpu->gb, cpu->sp, GET_HIGH_BYTE(cpu->pc));
        mmu_write(cpu->gb, cpu->sp, GET_LOW_BYTE(cpu->pc));

        cpu->pc = addr;
    }
    return 0;
}

u8 instr_call_c_a16(CPU *cpu) {
    u8  lo   = mmu_read(cpu->gb, cpu->pc++);
    u8  hi   = mmu_read(cpu->gb, cpu->pc++);
    u16 addr = MAKE_U16(hi, lo);

    if (cpu_get_flag(cpu, FLAG_CARRY)) {
        cpu->sp--;
        mmu_write(cpu->gb, cpu->sp, GET_HIGH_BYTE(cpu->pc));
        mmu_write(cpu->gb, cpu->sp, GET_LOW_BYTE(cpu->pc));

        cpu->pc = addr;
    }
    return 0;
}

// RET
// Return from subroutine (POP PC after a call)
// Flags:
// None affected
// ----------------------------------------------
u8 instr_ret(CPU *cpu) {
    u8 lo   = mmu_read(cpu->gb, cpu->pc++);
    u8 hi   = mmu_read(cpu->gb, cpu->pc++);

    cpu->pc = MAKE_U16(hi, lo);
    return 0;
}

// RET cc
// Retrun from subroutine if cc condition is met
// cc:
// nz, z, nc, c
// Flags:
// None affected
// ----------------------------------------------
u8 instr_ret_nz(CPU *cpu) {
    if (!cpu_get_flag(cpu, FLAG_ZERO)) {
        u8 lo   = mmu_read(cpu->gb, cpu->sp++);
        u8 hi   = mmu_read(cpu->gb, cpu->sp++);
        cpu->pc = MAKE_U16(hi, lo);
    }
    return 0;
}

u8 instr_ret_z(CPU *cpu) {
    if (cpu_get_flag(cpu, FLAG_ZERO)) {
        u8 lo   = mmu_read(cpu->gb, cpu->sp++);
        u8 hi   = mmu_read(cpu->gb, cpu->sp++);
        cpu->pc = MAKE_U16(hi, lo);
    }
    return 0;
}

u8 instr_ret_nc(CPU *cpu) {
    if (!cpu_get_flag(cpu, FLAG_CARRY)) {
        u8 lo   = mmu_read(cpu->gb, cpu->sp++);
        u8 hi   = mmu_read(cpu->gb, cpu->sp++);
        cpu->pc = MAKE_U16(hi, lo);
    }
    return 0;
}

u8 instr_ret_c(CPU *cpu) {
    if (cpu_get_flag(cpu, FLAG_CARRY)) {
        u8 lo   = mmu_read(cpu->gb, cpu->sp++);
        u8 hi   = mmu_read(cpu->gb, cpu->sp++);
        cpu->pc = MAKE_U16(hi, lo);
    }
    return 0;
}

// Return from subroutine & enable interrupts
u8 instr_reti(CPU *cpu) {
    u8 lo    = mmu_read(cpu->gb, cpu->sp++);
    u8 hi    = mmu_read(cpu->gb, cpu->sp++);
    cpu->pc  = MAKE_U16(hi, lo);
    cpu->ime = true;
    return 0;
}

// ============================================================================
// NOTE: Rotates / Flags
// https://rgbds.gbdev.io/docs/v1.0.1/gbz80.7#Bit_shift_instructions
// ============================================================================

// RLCA
// Rotate register A left
// Flags:
// Z = N = H = 0
// C = according to the result
// ----------------------------------------------
u8 instr_rlca(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 carry    = CHECK_BIT(a, 7);

    cpu->regs.a = (a << 1) | carry;

    cpu->regs.f = 0;
    if (carry)
        cpu->regs.f |= FLAG_CARRY;

    return 0;
}

// RRCA
// Rotate register A right
// Flags:
// Z = N = H = 0
// C = according to the result
// ----------------------------------------------
u8 instr_rrca(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 carry    = CHECK_BIT(a, 7);

    cpu->regs.a = (a >> 1) | (carry << 7);

    cpu->regs.f = 0;
    if (carry)
        cpu->regs.f |= FLAG_CARRY;

    return 0;
}

// RLA
// Rotate register A left, through the carry flag
// Flags:
// Z = N = H = 0
// C = according to the result
// ----------------------------------------------
u8 instr_rla(CPU *cpu) {
    u8 a         = cpu->regs.a;
    u8 old_carry = cpu_get_flag(cpu, FLAG_CARRY);
    u8 new_carry = CHECK_BIT(a, 7);

    cpu->regs.a  = (a << 1) | old_carry;

    cpu->regs.f  = 0;
    if (new_carry)
        cpu->regs.f |= FLAG_CARRY;

    return 0;
}

// RRA
// Rotate register A right, through the carry flag
// Flags:
// Z = N = H = 0
// C = according to the result
// ----------------------------------------------
u8 instr_rra(CPU *cpu) {
    u8 a         = cpu->regs.a;
    u8 old_carry = cpu_get_flag(cpu, FLAG_CARRY);
    u8 new_carry = CHECK_BIT(a, 7);

    cpu->regs.a  = (a >> 1) | (old_carry << 7);

    cpu->regs.f  = 0;
    if (new_carry)
        cpu->regs.f |= FLAG_CARRY;

    return 0;
}

// CPL
// Complement Accumulator register
// Flags:
// N = H = 1
u8 instr_cpl(CPU *cpu) {
    cpu->regs.a ^= 0xFF;
    cpu->regs.f |= FLAG_SUBT | FLAG_HF_CARRY;
    return 0;
}

// SCF
// Set carry flag
// N = H = 0
// C = 1
u8 instr_scf(CPU *cpu) {
    cpu->regs.f &= FLAG_ZERO;  // Preserve Z
    cpu->regs.f |= FLAG_CARRY; // Set C
    return 0;
}

// CCF
// Complement carry flag
// Flags:
// N = H = 0
// C = inverted
u8 instr_ccf(CPU *cpu) {
    bool carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f &= FLAG_ZERO;
    if (!carry)
        cpu->regs.f |= FLAG_CARRY; // Set C

    return 0;
}

// DAA
// Decimal Adjust Accumulator
// If inputs of ADD, ADC, SUB, SBC in BCD
// adjust result to bel in BCD as well
// Exact behavior of this instruction depends on N flag
// https://rgbds.gbdev.io/docs/v1.0.1/gbz80.7#DAA
u8 instr_daa(CPU *cpu) {
    u8   a      = cpu->regs.a;

    bool sub    = cpu_get_flag(cpu, FLAG_SUBT);
    bool half   = cpu_get_flag(cpu, FLAG_HF_CARRY);
    bool carry  = cpu_get_flag(cpu, FLAG_CARRY);

    u8   result = adjust_bcd(a, sub, carry, half);

    // Update flags
    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (sub)
        cpu->regs.f |= FLAG_SUBT;

    // Carry is set if we corrected with 0x60
    if (!sub && (carry || a > 0x99))
        cpu->regs.f |= FLAG_CARRY;
    if (sub && carry)
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}
