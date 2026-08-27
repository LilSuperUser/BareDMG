// include/core/cpu/cpu_exec.h
#ifndef CPU_EXEC_H
#define CPU_EXEC_H

#define ILLEGAL 4

#include <core/cpu/cpu.h>

typedef u8 (*InstrFunc)(CPU *cpu);

// =====================================================
// 8-bit Load Instructions
// =====================================================

// Special memory loads
u8 instr_ld_mem_bc_a(CPU *cpu);
u8 instr_ld_mem_de_a(CPU *cpu);
u8 instr_ld_a_mem_bc(CPU *cpu);
u8 instr_ld_a_mem_de(CPU *cpu);

u8 instr_ld_mem_hli_a(CPU *cpu);
u8 instr_ld_a_mem_hli(CPU *cpu);
u8 instr_ld_mem_hld_a(CPU *cpu);
u8 instr_ld_a_mem_hld(CPU *cpu);

u8 instr_ldh_mem_a8_a(CPU *cpu);
u8 instr_ldh_a_mem_a8(CPU *cpu);
u8 instr_ldh_mem_c_a(CPU *cpu);
u8 instr_ldh_a_mem_c(CPU *cpu);

u8 instr_ld_mem_a16_a(CPU *cpu);
u8 instr_ld_a_mem_a16(CPU *cpu);

// =====================================================
// 16-bit Load Instructions
// =====================================================

u8 instr_ld_bc_nn(CPU *cpu);
u8 instr_ld_de_nn(CPU *cpu);
u8 instr_ld_hl_nn(CPU *cpu);
u8 instr_ld_sp_nn(CPU *cpu);

u8 instr_ld_mem_a16_sp(CPU *cpu);
u8 instr_ld_sp_hl(CPU *cpu);
u8 instr_ld_hl_sp_e8(CPU *cpu);

// =====================================================
// 16-bit Arithmetic
// =====================================================

u8 instr_add_hl_bc(CPU *cpu);
u8 instr_add_hl_de(CPU *cpu);
u8 instr_add_hl_hl(CPU *cpu);
u8 instr_add_hl_sp(CPU *cpu);
u8 instr_add_sp_e8(CPU *cpu);

u8 instr_inc_bc(CPU *cpu);
u8 instr_inc_de(CPU *cpu);
u8 instr_inc_hl(CPU *cpu);
u8 instr_inc_sp(CPU *cpu);

u8 instr_dec_bc(CPU *cpu);
u8 instr_dec_de(CPU *cpu);
u8 instr_dec_hl(CPU *cpu);
u8 instr_dec_sp(CPU *cpu);

// =====================================================
// Control Flow
// =====================================================

// Jumps
u8 instr_jp_a16(CPU *cpu);
u8 instr_jp_hl(CPU *cpu);
u8 instr_jp_nz_a16(CPU *cpu);
u8 instr_jp_z_a16(CPU *cpu);
u8 instr_jp_nc_a16(CPU *cpu);
u8 instr_jp_c_a16(CPU *cpu);

// Relative jumps (JR)
u8 instr_jr_e8(CPU *cpu);
u8 instr_jr_nz_e8(CPU *cpu);
u8 instr_jr_z_e8(CPU *cpu);
u8 instr_jr_nc_e8(CPU *cpu);
u8 instr_jr_c_e8(CPU *cpu);

// Calls & Returns
u8 instr_call_a16(CPU *cpu);
u8 instr_call_nz_a16(CPU *cpu);
u8 instr_call_z_a16(CPU *cpu);
u8 instr_call_nc_a16(CPU *cpu);
u8 instr_call_c_a16(CPU *cpu);

u8 instr_ret(CPU *cpu);
u8 instr_ret_nz(CPU *cpu);
u8 instr_ret_z(CPU *cpu);
u8 instr_ret_nc(CPU *cpu);
u8 instr_ret_c(CPU *cpu);
u8 instr_reti(CPU *cpu);

// Stack
u8 instr_push_bc(CPU *cpu);
u8 instr_push_de(CPU *cpu);
u8 instr_push_hl(CPU *cpu);
u8 instr_push_af(CPU *cpu);

u8 instr_pop_bc(CPU *cpu);
u8 instr_pop_de(CPU *cpu);
u8 instr_pop_hl(CPU *cpu);
u8 instr_pop_af(CPU *cpu);

// Restart vectors
u8 instr_rst_00(CPU *cpu);
u8 instr_rst_08(CPU *cpu);
u8 instr_rst_10(CPU *cpu);
u8 instr_rst_18(CPU *cpu);
u8 instr_rst_20(CPU *cpu);
u8 instr_rst_28(CPU *cpu);
u8 instr_rst_30(CPU *cpu);
u8 instr_rst_38(CPU *cpu);

// =====================================================
// CPU Control
// =====================================================
u8 instr_nop(CPU *cpu);
u8 instr_stop(CPU *cpu);
u8 instr_halt(CPU *cpu);
u8 instr_di(CPU *cpu);
u8 instr_ei(CPU *cpu);

// =====================================================
// Rotates / Flags
// =====================================================
u8 instr_rlca(CPU *cpu);
u8 instr_rrca(CPU *cpu);
u8 instr_rla(CPU *cpu);
u8 instr_rra(CPU *cpu);

u8 instr_cpl(CPU *cpu);
u8 instr_scf(CPU *cpu);
u8 instr_ccf(CPU *cpu);
u8 instr_daa(CPU *cpu);

// Dispatcher to CB prefixed instructions
u8 instr_prefix_cb(CPU *cpu);

// NOTE: read_r8() and write_r8() ( formerly cb_read_r8() and cb_write_r8() )
// already handle (HL) as just another r8 slot.

// Dispatcher to LD r8, n instructions (8 opcodes)
u8 instr_ld_r8_or_mem_hl_n(CPU *cpu, u8 opcode);

// Dispatcher to LD r8, r8' instructions (63 opcodes)
// 0x76 opcode is HALT
u8 instr_ld_r8_r8_or_mem_hl(CPU *cpu, u8 opcode);

// Dispatcher to INC r8 instructions (8 opcodes)
u8 instr_inc_r8_or_mem_hl(CPU *cpu, u8 opcode);

// Dispatcher to DEC r8 instructions (8 opcodes)
u8 instr_dec_r8_or_mem_hl(CPU *cpu, u8 opcode);

// Dispatcher to ALU A, n instructions (8 opcodes)
u8 instr_alu_a_n(CPU *cpu, u8 opcode);

// Dispatcher to ALU A, r8 instructions (64 opcodes)
u8 instr_alu_a_r8_or_mem_hl(CPU *cpu, u8 opcode);

#endif // !CPU_EXEC_H
