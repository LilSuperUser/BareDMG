// src/core/cpu/cpu.c
#include <core/cpu/cpu.h>
#include <core/bus.h>
#include <gbemu.h>
#include <string.h>
#include <utils.h>

void cpu_init(CPU *cpu, GameBoy *gb) {
    memset(cpu, 0, sizeof(CPU));
    cpu->gb = gb;
    cpu_reset(cpu);
}

void cpu_reset(CPU *cpu) {
    // Game Boy boot sequence sets these initial values
    // https://gbdev.io/pandocs/Power_Up_Sequence.html
    cpu->regs.a = 0x01; // GB/SGB identifier
    cpu->regs.f = 0xB0; // Flags: Z = 1, N = 0, H = 1, C = 1
    cpu->regs.b = 0x00;
    cpu->regs.c = 0x13;
    cpu->regs.d = 0x00;
    cpu->regs.e = 0xD8;
    cpu->regs.h = 0x01;
    cpu->regs.l = 0x4D;

    cpu->sp     = 0xFFFE;
    cpu->pc     = 0x0100; // Start after boot ROM

    cpu->ime    = false;
    cpu->halted = false;
}

// Register Pair Read Functions
u16 cpu_read_af(const CPU *cpu) {
    return MAKE_U16(cpu->regs.a, cpu->regs.f);
}

u16 cpu_read_bc(const CPU *cpu) {
    return MAKE_U16(cpu->regs.b, cpu->regs.c);
}

u16 cpu_read_de(const CPU *cpu) {
    return MAKE_U16(cpu->regs.d, cpu->regs.e);
}

u16 cpu_read_hl(const CPU *cpu) {
    return MAKE_U16(cpu->regs.h, cpu->regs.l);
}

// Register Pair Write Functions
void cpu_write_af(CPU *cpu, u16 value) {
    cpu->regs.a = GET_HIGH_BYTE(value);
    cpu->regs.f = GET_LOW_BYTE(value) & 0xF0; // Lower 4 bits always zero
}

void cpu_write_bc(CPU *cpu, u16 value) {
    cpu->regs.b = GET_HIGH_BYTE(value);
    cpu->regs.c = GET_LOW_BYTE(value);
}

void cpu_write_de(CPU *cpu, u16 value) {
    cpu->regs.d = GET_HIGH_BYTE(value);
    cpu->regs.e = GET_LOW_BYTE(value);
}

void cpu_write_hl(CPU *cpu, u16 value) {
    cpu->regs.h = GET_HIGH_BYTE(value);
    cpu->regs.l = GET_LOW_BYTE(value);
}

// Flag Helpers
bool cpu_get_flag(CPU *cpu, u8 flag) {
    return (cpu->regs.f & flag) != 0;
}

void cpu_set_flag(CPU *cpu, u8 flag) {
    cpu->regs.f |= flag;
}

void cpu_clear_flag(CPU *cpu, u8 flag) {
    cpu->regs.f &= ~flag;
}

// Main execute function
u8 cpu_step(CPU *cpu) {
    if (cpu->halted) {
        // Just burn cycles
        return 4;
    }

    // FETCH: Read OpCode at PC, increment PC
    u8 opcode = mmu_read(cpu->gb, cpu->pc++);

    // Decode & Execute
    u8 cycles = cpu_execute(cpu, opcode);

    return cycles;
}
