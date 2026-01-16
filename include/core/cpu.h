// include/core/cpu.h
#ifndef CPU_H
#define CPU_H

#include <core/utils.h>
#include <stdbool.h>

// ---------------------------------------------
// CPU Registers (CPU State)
// https://gbdev.io/pandocs/CPU_Registers_and_Flags.html
// ---------------------------------------------

struct GameBoy;

typedef struct {
    // 8 bit registers
    struct {
        u8 a; // Accumulator
        u8 f; // Flags
        u8 b;
        u8 c;
        u8 d;
        u8 e;
        u8 h;
        u8 l;
    } regs;

    // 16 bit registers
    u16      sp; // Stack pointer
    u16      pc; // Program Counter

    // Interrupt state
    bool     ime;    // Interrupt Master Enable
    bool     halted; // CPU is haled?

    // Pointer to the emulator context (for memory access)
    struct GameBoy *gb;
} CPU;

// ---------------------------------------------
// CPU Flags (Lower 8 bits of AF register)
// ---------------------------------------------
#define FLAG_ZERO 0x80     // bit 7 (z)
#define FLAG_SUBT 0x40     // bit 6 (n)
#define FLAG_HF_CARRY 0x20 // bit 5 (h)
#define FLAG_CARRY 0x10    // bit 4 (c)

// ---------------------------------------------
// CPU Functions
// ---------------------------------------------
void cpu_init(CPU *cpu, struct GameBoy *gb);
void cpu_reset(CPU *cpu);
u8   cpu_step(CPU *cpu); // Execute 1 instruction, return cycles

// ---------------------------------------------
// Register pair accessors
// ---------------------------------------------
u16  cpu_read_af(const CPU *cpu);
u16  cpu_read_bc(const CPU *cpu);
u16  cpu_read_de(const CPU *cpu);
u16  cpu_read_hl(const CPU *cpu);

void cpu_write_af(CPU *cpu, u16 value);
void cpu_write_bc(CPU *cpu, u16 value);
void cpu_write_de(CPU *cpu, u16 value);
void cpu_write_hl(CPU *cpu, u16 value);

// ---------------------------------------------
// Flag Helpers
// ---------------------------------------------
bool cpu_get_flag(CPU *cpu, u8 flag);
void cpu_set_flag(CPU *cpu, u8 flag);
void cpu_clear_flag(CPU *cpu, u8 flag);

// ---------------------------------------------
// Internal CPU Functions (used by tables/exec)
// Declared here so cpu_exec.c and cpu_tables.c can use them
// ---------------------------------------------
u8   cpu_execute(CPU *cpu, u8 opcode);

#endif // !CPU_H
