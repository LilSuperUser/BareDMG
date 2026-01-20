// include/core/cpu/cpu_exec.h
#ifndef CPU_EXEC_H
#define CPU_EXEC_H

#define ILLEGAL 4

#include <core/cpu/cpu.h>

typedef u8 (*InstrFunc)(CPU *cpu);

// =====================================================
// 8-bit Load Instructions
// =====================================================

// Immediate loads
u8 instr_ld_b_n(CPU *cpu);
u8 instr_ld_c_n(CPU *cpu);
u8 instr_ld_d_n(CPU *cpu);
u8 instr_ld_e_n(CPU *cpu);
u8 instr_ld_h_n(CPU *cpu);
u8 instr_ld_l_n(CPU *cpu);
u8 instr_ld_a_n(CPU *cpu);

// Register <-> Register
u8 instr_ld_b_b(CPU *cpu);
u8 instr_ld_b_c(CPU *cpu);
u8 instr_ld_b_d(CPU *cpu);
u8 instr_ld_b_e(CPU *cpu);
u8 instr_ld_b_h(CPU *cpu);
u8 instr_ld_b_l(CPU *cpu);
u8 instr_ld_b_a(CPU *cpu);

u8 instr_ld_c_b(CPU *cpu);
u8 instr_ld_c_c(CPU *cpu);
u8 instr_ld_c_d(CPU *cpu);
u8 instr_ld_c_e(CPU *cpu);
u8 instr_ld_c_h(CPU *cpu);
u8 instr_ld_c_l(CPU *cpu);
u8 instr_ld_c_a(CPU *cpu);

u8 instr_ld_d_b(CPU *cpu);
u8 instr_ld_d_c(CPU *cpu);
u8 instr_ld_d_d(CPU *cpu);
u8 instr_ld_d_e(CPU *cpu);
u8 instr_ld_d_h(CPU *cpu);
u8 instr_ld_d_l(CPU *cpu);
u8 instr_ld_d_a(CPU *cpu);

u8 instr_ld_e_b(CPU *cpu);
u8 instr_ld_e_c(CPU *cpu);
u8 instr_ld_e_d(CPU *cpu);
u8 instr_ld_e_e(CPU *cpu);
u8 instr_ld_e_h(CPU *cpu);
u8 instr_ld_e_l(CPU *cpu);
u8 instr_ld_e_a(CPU *cpu);

u8 instr_ld_h_b(CPU *cpu);
u8 instr_ld_h_c(CPU *cpu);
u8 instr_ld_h_d(CPU *cpu);
u8 instr_ld_h_e(CPU *cpu);
u8 instr_ld_h_h(CPU *cpu);
u8 instr_ld_h_l(CPU *cpu);
u8 instr_ld_h_a(CPU *cpu);

u8 instr_ld_l_b(CPU *cpu);
u8 instr_ld_l_c(CPU *cpu);
u8 instr_ld_l_d(CPU *cpu);
u8 instr_ld_l_e(CPU *cpu);
u8 instr_ld_l_h(CPU *cpu);
u8 instr_ld_l_l(CPU *cpu);
u8 instr_ld_l_a(CPU *cpu);

u8 instr_ld_a_b(CPU *cpu);
u8 instr_ld_a_c(CPU *cpu);
u8 instr_ld_a_d(CPU *cpu);
u8 instr_ld_a_e(CPU *cpu);
u8 instr_ld_a_h(CPU *cpu);
u8 instr_ld_a_l(CPU *cpu);
u8 instr_ld_a_a(CPU *cpu);

// Memory via HL
u8 instr_ld_b_mem_hl(CPU *cpu);
u8 instr_ld_c_mem_hl(CPU *cpu);
u8 instr_ld_d_mem_hl(CPU *cpu);
u8 instr_ld_e_mem_hl(CPU *cpu);
u8 instr_ld_h_mem_hl(CPU *cpu);
u8 instr_ld_l_mem_hl(CPU *cpu);
u8 instr_ld_a_mem_hl(CPU *cpu);

u8 instr_ld_mem_hl_b(CPU *cpu);
u8 instr_ld_mem_hl_c(CPU *cpu);
u8 instr_ld_mem_hl_d(CPU *cpu);
u8 instr_ld_mem_hl_e(CPU *cpu);
u8 instr_ld_mem_hl_h(CPU *cpu);
u8 instr_ld_mem_hl_l(CPU *cpu);
u8 instr_ld_mem_hl_a(CPU *cpu);

u8 instr_ld_mem_hl_n(CPU *cpu);

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
// 8-bit Arithmetic & Logic
// =====================================================

u8 instr_add_a_b(CPU *cpu);
u8 instr_add_a_c(CPU *cpu);
u8 instr_add_a_d(CPU *cpu);
u8 instr_add_a_e(CPU *cpu);
u8 instr_add_a_h(CPU *cpu);
u8 instr_add_a_l(CPU *cpu);
u8 instr_add_a_mem_hl(CPU *cpu);
u8 instr_add_a_a(CPU *cpu);
u8 instr_add_a_n(CPU *cpu);

u8 instr_adc_a_b(CPU *cpu);
u8 instr_adc_a_c(CPU *cpu);
u8 instr_adc_a_d(CPU *cpu);
u8 instr_adc_a_e(CPU *cpu);
u8 instr_adc_a_h(CPU *cpu);
u8 instr_adc_a_l(CPU *cpu);
u8 instr_adc_a_mem_hl(CPU *cpu);
u8 instr_adc_a_a(CPU *cpu);
u8 instr_adc_a_n(CPU *cpu);

u8 instr_sub_a_b(CPU *cpu);
u8 instr_sub_a_c(CPU *cpu);
u8 instr_sub_a_d(CPU *cpu);
u8 instr_sub_a_e(CPU *cpu);
u8 instr_sub_a_h(CPU *cpu);
u8 instr_sub_a_l(CPU *cpu);
u8 instr_sub_a_mem_hl(CPU *cpu);
u8 instr_sub_a_a(CPU *cpu);
u8 instr_sub_a_n(CPU *cpu);

u8 instr_sbc_a_b(CPU *cpu);
u8 instr_sbc_a_c(CPU *cpu);
u8 instr_sbc_a_d(CPU *cpu);
u8 instr_sbc_a_e(CPU *cpu);
u8 instr_sbc_a_h(CPU *cpu);
u8 instr_sbc_a_l(CPU *cpu);
u8 instr_sbc_a_mem_hl(CPU *cpu);
u8 instr_sbc_a_a(CPU *cpu);
u8 instr_sbc_a_n(CPU *cpu);

u8 instr_and_a_b(CPU *cpu);
u8 instr_and_a_c(CPU *cpu);
u8 instr_and_a_d(CPU *cpu);
u8 instr_and_a_e(CPU *cpu);
u8 instr_and_a_h(CPU *cpu);
u8 instr_and_a_l(CPU *cpu);
u8 instr_and_a_mem_hl(CPU *cpu);
u8 instr_and_a_a(CPU *cpu);
u8 instr_and_a_n(CPU *cpu);

u8 instr_or_a_b(CPU *cpu);
u8 instr_or_a_c(CPU *cpu);
u8 instr_or_a_d(CPU *cpu);
u8 instr_or_a_e(CPU *cpu);
u8 instr_or_a_h(CPU *cpu);
u8 instr_or_a_l(CPU *cpu);
u8 instr_or_a_mem_hl(CPU *cpu);
u8 instr_or_a_a(CPU *cpu);
u8 instr_or_a_n(CPU *cpu);

u8 instr_xor_a_b(CPU *cpu);
u8 instr_xor_a_c(CPU *cpu);
u8 instr_xor_a_d(CPU *cpu);
u8 instr_xor_a_e(CPU *cpu);
u8 instr_xor_a_h(CPU *cpu);
u8 instr_xor_a_l(CPU *cpu);
u8 instr_xor_a_mem_hl(CPU *cpu);
u8 instr_xor_a_a(CPU *cpu);
u8 instr_xor_a_n(CPU *cpu);

u8 instr_cp_a_b(CPU *cpu);
u8 instr_cp_a_c(CPU *cpu);
u8 instr_cp_a_d(CPU *cpu);
u8 instr_cp_a_e(CPU *cpu);
u8 instr_cp_a_h(CPU *cpu);
u8 instr_cp_a_l(CPU *cpu);
u8 instr_cp_a_mem_hl(CPU *cpu);
u8 instr_cp_a_a(CPU *cpu);
u8 instr_cp_a_n(CPU *cpu);

// INC / DEC
u8 instr_inc_b(CPU *cpu);
u8 instr_inc_c(CPU *cpu);
u8 instr_inc_d(CPU *cpu);
u8 instr_inc_e(CPU *cpu);
u8 instr_inc_h(CPU *cpu);
u8 instr_inc_l(CPU *cpu);
u8 instr_inc_a(CPU *cpu);
u8 instr_inc_mem_hl(CPU *cpu);

u8 instr_dec_b(CPU *cpu);
u8 instr_dec_c(CPU *cpu);
u8 instr_dec_d(CPU *cpu);
u8 instr_dec_e(CPU *cpu);
u8 instr_dec_h(CPU *cpu);
u8 instr_dec_l(CPU *cpu);
u8 instr_dec_a(CPU *cpu);
u8 instr_dec_mem_hl(CPU *cpu);

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
// TODO:
// u8 instr_prefix_cb(CPU *cpu);

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

#endif // !CPU_EXEC_H
