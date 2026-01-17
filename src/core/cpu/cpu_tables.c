// src/core/cpu/cpu_tables.c
#include <core/cpu/cpu.h>
#include <core/cpu/cpu_exec.h>
#include <core/bus.h>
#include <gbemu.h>
#include <stdio.h>

// ---------------------------------------------
// Instruction table (256 entries)
// https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
// ---------------------------------------------
static const InstrFunc instr_table[256] = {
    // 0x0_
    [0x00] = instr_nop,
    [0x01] = instr_ld_bc_nn,
    [0x02] = instr_ld_mem_bc_a,
    [0x03] = instr_inc_bc,
    [0x04] = instr_inc_b,
    [0x05] = instr_dec_b,
    [0x06] = instr_ld_b_n,
    [0x07] = instr_rlca,
    [0x08] = instr_ld_mem_a16_sp,
    [0x09] = instr_add_hl_bc,
    [0x0A] = instr_ld_a_mem_bc,
    [0x0B] = instr_dec_bc,
    [0x0C] = instr_inc_c,
    [0x0D] = instr_dec_c,
    [0x0E] = instr_ld_c_n,
    [0x0F] = instr_rrca,

    // 0x1_
    [0x10] = instr_stop,
    [0x11] = instr_ld_de_nn,
    [0x12] = instr_ld_mem_de_a,
    [0x13] = instr_inc_de,
    [0x14] = instr_inc_d,
    [0x15] = instr_dec_d,
    [0x16] = instr_ld_d_n,
    [0x17] = instr_rla,
    [0x18] = instr_jr_r8,
    [0x19] = instr_add_hl_de,
    [0x1A] = instr_ld_a_mem_de,
    [0x1B] = instr_dec_de,
    [0x1C] = instr_inc_e,
    [0x1D] = instr_dec_e,
    [0x1E] = instr_ld_e_n,
    [0x1F] = instr_rra,

    // 0x2_
    [0x20] = instr_jr_nz_r8,
    [0x21] = instr_ld_hl_nn,
    [0x22] = instr_ld_mem_hli_a,
    [0x23] = instr_inc_hl,
    [0x24] = instr_inc_h,
    [0x25] = instr_dec_h,
    [0x26] = instr_ld_h_n,
    [0x27] = instr_daa,
    [0x28] = instr_jr_z_r8,
    [0x29] = instr_add_hl_hl,
    [0x2A] = instr_ld_a_mem_hli,
    [0x2B] = instr_dec_hl,
    [0x2C] = instr_inc_l,
    [0x2D] = instr_dec_l,
    [0x2E] = instr_ld_l_n,
    [0x2F] = instr_cpl,

    // 0x3_
    [0x30] = instr_jr_nc_r8,
    [0x31] = instr_ld_sp_nn,
    [0x32] = instr_ld_mem_hld_a,
    [0x33] = instr_inc_sp,
    [0x34] = instr_inc_mem_hl,
    [0x35] = instr_dec_mem_hl,
    [0x36] = instr_ld_mem_hl_n,
    [0x37] = instr_scf,
    [0x38] = instr_jr_c_r8,
    [0x39] = instr_add_hl_sp,
    [0x3A] = instr_ld_a_mem_hld,
    [0x3B] = instr_dec_sp,
    [0x3C] = instr_inc_a,
    [0x3D] = instr_dec_a,
    [0x3E] = instr_ld_a_n,
    [0x3F] = instr_ccf,

    // 0x4_
    [0x40] = instr_ld_b_b,
    [0x41] = instr_ld_b_c,
    [0x42] = instr_ld_b_d,
    [0x43] = instr_ld_b_e,
    [0x44] = instr_ld_b_h,
    [0x45] = instr_ld_b_l,
    [0x46] = instr_ld_b_mem_hl,
    [0x47] = instr_ld_b_a,
    [0x48] = instr_ld_c_b,
    [0x49] = instr_ld_c_c,
    [0x4A] = instr_ld_c_d,
    [0x4B] = instr_ld_c_e,
    [0x4C] = instr_ld_c_h,
    [0x4D] = instr_ld_c_l,
    [0x4E] = instr_ld_c_mem_hl,
    [0x4F] = instr_ld_c_a,

    // 0x5_
    [0x50] = instr_ld_d_b,
    [0x51] = instr_ld_d_c,
    [0x52] = instr_ld_d_d,
    [0x53] = instr_ld_d_e,
    [0x54] = instr_ld_d_h,
    [0x55] = instr_ld_d_l,
    [0x56] = instr_ld_d_mem_hl,
    [0x57] = instr_ld_d_a,
    [0x58] = instr_ld_e_b,
    [0x59] = instr_ld_e_c,
    [0x5A] = instr_ld_e_d,
    [0x5B] = instr_ld_e_e,
    [0x5C] = instr_ld_e_h,
    [0x5D] = instr_ld_e_l,
    [0x5E] = instr_ld_e_mem_hl,
    [0x5F] = instr_ld_e_a,

    // 0x6_
    [0x60] = instr_ld_h_b,
    [0x61] = instr_ld_h_c,
    [0x62] = instr_ld_h_d,
    [0x63] = instr_ld_h_e,
    [0x64] = instr_ld_h_h,
    [0x65] = instr_ld_h_l,
    [0x66] = instr_ld_h_mem_hl,
    [0x67] = instr_ld_h_a,
    [0x68] = instr_ld_l_b,
    [0x69] = instr_ld_l_c,
    [0x6A] = instr_ld_l_d,
    [0x6B] = instr_ld_l_e,
    [0x6C] = instr_ld_l_h,
    [0x6D] = instr_ld_l_l,
    [0x6E] = instr_ld_l_mem_hl,
    [0x6F] = instr_ld_l_a,

    // 0x7_
    [0x70] = instr_ld_mem_hl_b,
    [0x71] = instr_ld_mem_hl_c,
    [0x72] = instr_ld_mem_hl_d,
    [0x73] = instr_ld_mem_hl_e,
    [0x74] = instr_ld_mem_hl_h,
    [0x75] = instr_ld_mem_hl_l,
    [0x76] = instr_halt,
    [0x77] = instr_ld_mem_hl_a,
    [0x78] = instr_ld_a_b,
    [0x79] = instr_ld_a_c,
    [0x7A] = instr_ld_a_d,
    [0x7B] = instr_ld_a_e,
    [0x7C] = instr_ld_a_h,
    [0x7D] = instr_ld_a_l,
    [0x7E] = instr_ld_a_mem_hl,
    [0x7F] = instr_ld_a_a,

    // 0x8_
    [0x80] = instr_add_a_b,
    [0x81] = instr_add_a_c,
    [0x82] = instr_add_a_d,
    [0x83] = instr_add_a_e,
    [0x84] = instr_add_a_h,
    [0x85] = instr_add_a_l,
    [0x86] = instr_add_a_mem_hl,
    [0x87] = instr_add_a_a,
    [0x88] = instr_adc_a_b,
    [0x89] = instr_adc_a_c,
    [0x8A] = instr_adc_a_d,
    [0x8B] = instr_adc_a_e,
    [0x8C] = instr_adc_a_h,
    [0x8D] = instr_adc_a_l,
    [0x8E] = instr_adc_a_mem_hl,
    [0x8F] = instr_adc_a_a,

    // 0x9_
    [0x90] = instr_sub_a_b,
    [0x91] = instr_sub_a_c,
    [0x92] = instr_sub_a_d,
    [0x93] = instr_sub_a_e,
    [0x94] = instr_sub_a_h,
    [0x95] = instr_sub_a_l,
    [0x96] = instr_sub_a_mem_hl,
    [0x97] = instr_sub_a_a,
    [0x98] = instr_sbc_a_b,
    [0x99] = instr_sbc_a_c,
    [0x9A] = instr_sbc_a_d,
    [0x9B] = instr_sbc_a_e,
    [0x9C] = instr_sbc_a_h,
    [0x9D] = instr_sbc_a_l,
    [0x9E] = instr_sbc_a_mem_hl,
    [0x9F] = instr_sbc_a_a,

    // 0xA_
    [0xA0] = instr_and_a_b,
    [0xA1] = instr_and_a_c,
    [0xA2] = instr_and_a_d,
    [0xA3] = instr_and_a_e,
    [0xA4] = instr_and_a_h,
    [0xA5] = instr_and_a_l,
    [0xA6] = instr_and_a_mem_hl,
    [0xA7] = instr_and_a_a,
    [0xA8] = instr_xor_a_b,
    [0xA9] = instr_xor_a_c,
    [0xAA] = instr_xor_a_d,
    [0xAB] = instr_xor_a_e,
    [0xAC] = instr_xor_a_h,
    [0xAD] = instr_xor_a_l,
    [0xAE] = instr_xor_a_mem_hl,
    [0xAF] = instr_xor_a_a,

    // 0xB_
    [0xB0] = instr_or_a_b,
    [0xB1] = instr_or_a_c,
    [0xB2] = instr_or_a_d,
    [0xB3] = instr_or_a_e,
    [0xB4] = instr_or_a_h,
    [0xB5] = instr_or_a_l,
    [0xB6] = instr_or_a_mem_hl,
    [0xB7] = instr_or_a_a,
    [0xB8] = instr_cp_a_b,
    [0xB9] = instr_cp_a_c,
    [0xBA] = instr_cp_a_d,
    [0xBB] = instr_cp_a_e,
    [0xBC] = instr_cp_a_h,
    [0xBD] = instr_cp_a_l,
    [0xBE] = instr_cp_a_mem_hl,
    [0xBF] = instr_cp_a_a,

    // 0xC_
    [0xC0] = instr_ret_nz,
    [0xC1] = instr_pop_bc,
    [0xC2] = instr_jp_nz_a16,
    [0xC3] = instr_jp_a16,
    [0xC4] = instr_call_nz_a16,
    [0xC5] = instr_push_bc,
    [0xC6] = instr_add_a_n,
    [0xC7] = instr_rst_00,
    [0xC8] = instr_ret_z,
    [0xC9] = instr_ret,
    [0xCA] = instr_jp_z_a16,
    [0xCB] = instr_prefix_cb,
    [0xCC] = instr_call_z_a16,
    [0xCD] = instr_call_a16,
    [0xCE] = instr_adc_a_n,
    [0xCF] = instr_rst_08,

    // 0xD_
    [0xD0] = instr_ret_nc,
    [0xD1] = instr_pop_de,
    [0xD2] = instr_jp_nc_a16,
    [0xD3] = NULL,
    [0xD4] = instr_call_nc_a16,
    [0xD5] = instr_push_de,
    [0xD6] = instr_sub_a_n,
    [0xD7] = instr_rst_10,
    [0xD8] = instr_ret_c,
    [0xD9] = instr_reti,
    [0xDA] = instr_jp_c_a16,
    [0xDB] = NULL,
    [0xDC] = instr_call_c_a16,
    [0xDD] = NULL,
    [0xDE] = instr_sbc_a_n,
    [0xDF] = instr_rst_18,

    // 0xE_
    [0xE0] = instr_ldh_mem_a8_a,
    [0xE1] = instr_pop_hl,
    [0xE2] = instr_ldh_mem_c_a,
    [0xE3] = NULL,
    [0xE4] = NULL,
    [0xE5] = instr_push_hl,
    [0xE6] = instr_and_a_n,
    [0xE7] = instr_rst_20,
    [0xE8] = instr_add_sp_e8,
    [0xE9] = instr_jp_hl,
    [0xEA] = instr_ld_mem_a16_a,
    [0xEB] = NULL,
    [0xEC] = NULL,
    [0xED] = NULL,
    [0xEE] = instr_xor_a_n,
    [0xEF] = instr_rst_28,

    // 0xF_
    [0xF0] = instr_ldh_a_mem_a8,
    [0xF1] = instr_pop_af,
    [0xF2] = instr_ldh_a_mem_c,
    [0xF3] = instr_di,
    [0xF4] = NULL,
    [0xF5] = instr_push_af,
    [0xF6] = instr_or_a_n,
    [0xF7] = instr_rst_30,
    [0xF8] = instr_ld_hl_sp_e8,
    [0xF9] = instr_ld_sp_hl,
    [0xFA] = instr_ld_a_mem_a16,
    [0xFB] = instr_ei,
    [0xFC] = NULL,
    [0xFD] = NULL,
    [0xFE] = instr_cp_a_n,
    [0xFF] = instr_rst_38,
};

// ---------------------------------------------
// Cycle counts for each instruction
// ---------------------------------------------
static const u8 instr_cycles[256] = {
    [0x00] = 4,       [0x01] = 12,      [0x02] = 8,  [0x03] = 8,
    [0x04] = 4,       [0x05] = 4,       [0x06] = 8,  [0x07] = 4,
    [0x08] = 20,      [0x09] = 8,       [0x0A] = 8,  [0x0B] = 8,
    [0x0C] = 4,       [0x0D] = 4,       [0x0E] = 8,  [0x0F] = 4,

    [0x10] = 4,       [0x11] = 12,      [0x12] = 8,  [0x13] = 8,
    [0x14] = 4,       [0x15] = 4,       [0x16] = 8,  [0x17] = 4,
    [0x18] = 12,      [0x19] = 8,       [0x1A] = 8,  [0x1B] = 8,
    [0x1C] = 4,       [0x1D] = 4,       [0x1E] = 8,  [0x1F] = 4,

    [0x20] = 12, // NOTE: 8 if Z flag set
    [0x21] = 12,      [0x22] = 8,       [0x23] = 8,  [0x24] = 4,
    [0x25] = 4,       [0x26] = 8,       [0x27] = 4,
    [0x28] = 12, // NOTE: 8 if Z flag not set
    [0x29] = 8,       [0x2A] = 8,       [0x2B] = 8,  [0x2C] = 4,
    [0x2D] = 4,       [0x2E] = 8,       [0x2F] = 4,

    [0x30] = 12, // NOTE: 8 if C flag set
    [0x31] = 12,      [0x32] = 8,       [0x33] = 8,  [0x34] = 12,
    [0x35] = 12,      [0x36] = 12,      [0x37] = 4,
    [0x38] = 12, // NOTE: 8 if C flag not set
    [0x39] = 8,       [0x3A] = 8,       [0x3B] = 8,  [0x3C] = 4,
    [0x3D] = 4,       [0x3E] = 8,       [0x3F] = 4,

    [0x40] = 4,       [0x41] = 4,       [0x42] = 4,  [0x43] = 4,
    [0x44] = 4,       [0x45] = 4,       [0x46] = 8,  [0x47] = 4,
    [0x48] = 4,       [0x49] = 4,       [0x4A] = 4,  [0x4B] = 4,
    [0x4C] = 4,       [0x4D] = 4,       [0x4E] = 8,  [0x4F] = 4,

    [0x50] = 4,       [0x51] = 4,       [0x52] = 4,  [0x53] = 4,
    [0x54] = 4,       [0x55] = 4,       [0x56] = 8,  [0x57] = 4,
    [0x58] = 4,       [0x59] = 4,       [0x5A] = 4,  [0x5B] = 4,
    [0x5C] = 4,       [0x5D] = 4,       [0x5E] = 8,  [0x5F] = 4,

    [0x60] = 4,       [0x61] = 4,       [0x62] = 4,  [0x63] = 4,
    [0x64] = 4,       [0x65] = 4,       [0x66] = 8,  [0x67] = 4,
    [0x68] = 4,       [0x69] = 4,       [0x6A] = 4,  [0x6B] = 4,
    [0x6C] = 4,       [0x6D] = 4,       [0x6E] = 8,  [0x6F] = 4,

    [0x70] = 8,       [0x71] = 8,       [0x72] = 8,  [0x73] = 8,
    [0x74] = 8,       [0x75] = 8,       [0x76] = 4,  [0x77] = 8,
    [0x78] = 4,       [0x79] = 4,       [0x7A] = 4,  [0x7B] = 4,
    [0x7C] = 4,       [0x7D] = 4,       [0x7E] = 8,  [0x7F] = 4,

    [0x80] = 4,       [0x81] = 4,       [0x82] = 4,  [0x83] = 4,
    [0x84] = 4,       [0x85] = 4,       [0x86] = 8,  [0x87] = 4,
    [0x88] = 4,       [0x89] = 4,       [0x8A] = 4,  [0x8B] = 4,
    [0x8C] = 4,       [0x8D] = 4,       [0x8E] = 8,  [0x8F] = 4,

    [0x90] = 4,       [0x91] = 4,       [0x92] = 4,  [0x93] = 4,
    [0x94] = 4,       [0x95] = 4,       [0x96] = 8,  [0x97] = 4,
    [0x98] = 4,       [0x99] = 4,       [0x9A] = 4,  [0x9B] = 4,
    [0x9C] = 4,       [0x9D] = 4,       [0x9E] = 8,  [0x9F] = 4,

    [0xA0] = 4,       [0xA1] = 4,       [0xA2] = 4,  [0xA3] = 4,
    [0xA4] = 4,       [0xA5] = 4,       [0xA6] = 8,  [0xA7] = 4,
    [0xA8] = 4,       [0xA9] = 4,       [0xAA] = 4,  [0xAB] = 4,
    [0xAC] = 4,       [0xAD] = 4,       [0xAE] = 8,  [0xAF] = 4,

    [0xB0] = 4,       [0xB1] = 4,       [0xB2] = 4,  [0xB3] = 4,
    [0xB4] = 4,       [0xB5] = 4,       [0xB6] = 8,  [0xB7] = 4,
    [0xB8] = 4,       [0xB9] = 4,       [0xBA] = 4,  [0xBB] = 4,
    [0xBC] = 4,       [0xBD] = 4,       [0xBE] = 8,  [0xBF] = 4,

    [0xC0] = 20, // NOTE: 8 if Z flag is set
    [0xC1] = 12,
    [0xC2] = 16, // NOTE: 12 if Z flag is set
    [0xC3] = 16,
    [0xC4] = 24, // NOTE: 12 if C not set
    [0xC5] = 16,      [0xC6] = 8,       [0xC7] = 16,
    [0xC8] = 20, // NOTE: 8 if Z flag is set
    [0xC9] = 16,
    [0xCA] = 16, // NOTE: 12 if Z is set
    [0xCB] = 4,
    [0xCC] = 24, // NOTE: 12 if Z is not set
    [0xCD] = 24,      [0xCE] = 8,       [0xCF] = 16,

    [0xD0] = 20, // NOTE: 8 if C is set
    [0xD1] = 12,
    [0xD2] = 16, // NOTE: 12 if C is set
    [0xD3] = ILLEGAL,
    [0xD4] = 24, // NOTE: 12 if C is set
    [0xD5] = 16,      [0xD6] = 8,       [0xD7] = 16,
    [0xD8] = 20, // NOTE: 8 if C is not set
    [0xD9] = 16,
    [0xDA] = 16, // NOTE: 12 if C not set
    [0xDB] = ILLEGAL,
    [0xDC] = 24, // NOTE: 12 if C not set
    [0xDD] = ILLEGAL, [0xDE] = 8,       [0xDF] = 16,

    [0xE0] = 12,      [0xE1] = 12,      [0xE2] = 8,  [0xE3] = ILLEGAL,
    [0xE4] = ILLEGAL, [0xE5] = 16,      [0xE6] = 8,  [0xE7] = 16,
    [0xE8] = 16,      [0xE9] = 4,       [0xEA] = 16, [0xEB] = ILLEGAL,
    [0xEC] = ILLEGAL, [0xED] = ILLEGAL, [0xEE] = 8,  [0xEF] = 16,

    [0xF0] = 12,      [0xF1] = 12,      [0xF2] = 8,  [0xF3] = 4,
    [0xF4] = ILLEGAL, [0xF5] = 16,      [0xF6] = 8,  [0xF7] = 16,
    [0xF8] = 12,      [0xF9] = 8,       [0xFA] = 16, [0xFB] = 4,
    [0xFC] = ILLEGAL, [0xFD] = ILLEGAL, [0xFE] = 8,  [0xFF] = 16,
};

// ---------------------------------------------
// Execute an instruction
// Called by cpu_step()
// ---------------------------------------------
u8 cpu_execute(CPU *cpu, u8 opcode) {
    // Check if instruction is implemented
    if (instr_table[opcode] == NULL) {
        fprintf(stderr, "Illegal Operation Code: 0x%02x at PC = 0x%04x\n", opcode, cpu->pc - 1);
        return ILLEGAL;
    }

    // Otherwise, call the instruction handler
    instr_table[opcode](cpu);

    // Return cycle count for the opcode
    return instr_cycles[opcode];
}
