// include/core/cpu/cpu_decode.h
#ifndef CPU_DECODE_H
#define CPU_DECODE_H
#include <core/cpu/cpu.h>

// ---------------------------------------------
// CB-Prefixed Opcode Decoding
// Top two bits of the CB opcode
// ---------------------------------------------
typedef enum {
    CB_GROUP_ROTATE_SHIFT = 0,
    CB_GROUP_BIT          = 1,
    CB_GROUP_RES          = 2,
    CB_GROUP_SET          = 3,
} CBGroup;

// ---------------------------------------------
// Decoded fields of a CB-prefixed opcode
// https://gbdev.io/pandocs/CPU_Instruction_Set.html#cb-prefix-instructions
// CB opcode byte layout: [ GG BBB RRR ]
//   GG  (bits 6-7) - group: rotate/shift, BIT, RES, or SET
//   BBB (bits 3-5) - bit index (BIT/RES/SET) or rotate/shift sub-op (group 0)
//   RRR (bits 0-2) - r8 operand
// ---------------------------------------------
typedef struct {
    CBGroup group;     // Which operation family
    u8      bit_or_op; // Bit index (BIT/RES/SET) or rotate/shift sub-op (group 0)
    u8      r;         // r8 operand index: 0=B 1=C 2=D 3=E 4=H 5=L 6=(HL) 7=A
} CBOpcode;

// Fetch the CB sub-opcode byte at cpu->pc
// (consuming it, i.e. pc++) and decode it
CBOpcode cpu_decode_cb(CPU *cpu);

// ---------------------------------------------
// Shared r8 operand access
// ---------------------------------------------
// r8 index convention shared across the CPU's opcode encoding:
// 0=B 1=C 2=D 3=E 4=H 5=L 6=(HL) 7=A
u8       read_r8(CPU *cpu, u8 r);
void     write_r8(CPU *cpu, u8 r, u8 value);

#endif // !CPU_DECODE_H
