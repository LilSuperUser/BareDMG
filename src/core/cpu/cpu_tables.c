// src/core/cpu/cpu_tables.c
#include <core/cpu/cpu.h>
#include <core/cpu/cpu_exec.h>
#include <core/bus.h>
#include <core/utils.h>
#include <gbemu.h>
#include <stdio.h>

// ---------------------------------------------
// Instruction table (256 entries)
// https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
// ---------------------------------------------
static const InstrFunc instr_table[] = {
    // 0x0_
    [0x00] = instr_nop,
    [0x01] = instr_ld_bc_nn,
    [0x02] = instr_ld_mem_bc_a,
    [0x03] = instr_inc_bc,
    [0x07] = instr_rlca,
    [0x08] = instr_ld_mem_a16_sp,
    [0x09] = instr_add_hl_bc,
    [0x0A] = instr_ld_a_mem_bc,
    [0x0B] = instr_dec_bc,
    [0x0F] = instr_rrca,

    // 0x1_
    [0x10] = instr_stop,
    [0x11] = instr_ld_de_nn,
    [0x12] = instr_ld_mem_de_a,
    [0x13] = instr_inc_de,
    [0x17] = instr_rla,
    [0x18] = instr_jr_e8,
    [0x19] = instr_add_hl_de,
    [0x1A] = instr_ld_a_mem_de,
    [0x1B] = instr_dec_de,
    [0x1F] = instr_rra,

    // 0x2_
    [0x20] = instr_jr_nz_e8,
    [0x21] = instr_ld_hl_nn,
    [0x22] = instr_ld_mem_hli_a,
    [0x23] = instr_inc_hl,
    [0x27] = instr_daa,
    [0x28] = instr_jr_z_e8,
    [0x29] = instr_add_hl_hl,
    [0x2A] = instr_ld_a_mem_hli,
    [0x2B] = instr_dec_hl,
    [0x2F] = instr_cpl,

    // 0x3_
    [0x30] = instr_jr_nc_e8,
    [0x31] = instr_ld_sp_nn,
    [0x32] = instr_ld_mem_hld_a,
    [0x33] = instr_inc_sp,
    [0x37] = instr_scf,
    [0x38] = instr_jr_c_e8,
    [0x39] = instr_add_hl_sp,
    [0x3A] = instr_ld_a_mem_hld,
    [0x3B] = instr_dec_sp,
    [0x3F] = instr_ccf,

    // 0x4_ - 0x7_: LD r8,r8'
    // Block handled by: instr_ld_r8_r8_or_mem_hl() in cpu_execute()
    // 0x76 = HALT is an exception

    [0x76] = instr_halt,

    // 0x8_ - 0xB_: ALU A,r8
    // Block handled by: instr_alu_a_r8_or_mem_hl

    // 0xC_
    [0xC0] = instr_ret_nz,
    [0xC1] = instr_pop_bc,
    [0xC2] = instr_jp_nz_a16,
    [0xC3] = instr_jp_a16,
    [0xC4] = instr_call_nz_a16,
    [0xC5] = instr_push_bc,
    [0xC7] = instr_rst_00,
    [0xC8] = instr_ret_z,
    [0xC9] = instr_ret,
    [0xCA] = instr_jp_z_a16,
    [0xCB] = instr_prefix_cb,
    [0xCC] = instr_call_z_a16,
    [0xCD] = instr_call_a16,
    [0xCF] = instr_rst_08,

    // 0xD_
    [0xD0] = instr_ret_nc,
    [0xD1] = instr_pop_de,
    [0xD2] = instr_jp_nc_a16,
    [0xD3] = NULL,
    [0xD4] = instr_call_nc_a16,
    [0xD5] = instr_push_de,
    [0xD7] = instr_rst_10,
    [0xD8] = instr_ret_c,
    [0xD9] = instr_reti,
    [0xDA] = instr_jp_c_a16,
    [0xDB] = NULL,
    [0xDC] = instr_call_c_a16,
    [0xDD] = NULL,
    [0xDF] = instr_rst_18,

    // 0xE_
    [0xE0] = instr_ldh_mem_a8_a,
    [0xE1] = instr_pop_hl,
    [0xE2] = instr_ldh_mem_c_a,
    [0xE3] = NULL,
    [0xE4] = NULL,
    [0xE5] = instr_push_hl,
    [0xE7] = instr_rst_20,
    [0xE8] = instr_add_sp_e8,
    [0xE9] = instr_jp_hl,
    [0xEA] = instr_ld_mem_a16_a,
    [0xEB] = NULL,
    [0xEC] = NULL,
    [0xED] = NULL,
    [0xEF] = instr_rst_28,

    // 0xF_
    [0xF0] = instr_ldh_a_mem_a8,
    [0xF1] = instr_pop_af,
    [0xF2] = instr_ldh_a_mem_c,
    [0xF3] = instr_di,
    [0xF4] = NULL,
    [0xF5] = instr_push_af,
    [0xF7] = instr_rst_30,
    [0xF8] = instr_ld_hl_sp_e8,
    [0xF9] = instr_ld_sp_hl,
    [0xFA] = instr_ld_a_mem_a16,
    [0xFB] = instr_ei,
    [0xFC] = NULL,
    [0xFD] = NULL,
    [0xFF] = instr_rst_38,
};

// ---------------------------------------------
// Execute an instruction
// Called by cpu_step()
// ---------------------------------------------
u8 cpu_execute(CPU *cpu, u8 opcode) {

    // Instructions: LD r8, n
    // 8 Opcodes: (0x06,0x0E,0x16,0x1E,0x26,0x2E,0x3E & 0x36)
    // Encoding: 00 rrr 110
    if (MASK_BITS(opcode, 0xC7) == 0x06)
        return instr_ld_r8_or_mem_hl_n(cpu, opcode);

    // Instructions: LD r8, r8'
    // 63 Opcodes: (0x40-0x7F except 0x76=HALT)
    // Encoding: 01 ddd sss
    if (opcode >= 0x40 && opcode <= 0x7F && opcode != 0x76)
        return instr_ld_r8_r8_or_mem_hl(cpu, opcode);

    // Instructions: INC r8
    // 8 Opcodes: (0x04,0x14,0x24,0x34,0x0C,0x1C,0x2C,0x3C)
    // Encoding: 00 rrr 100
    if (MASK_BITS(opcode, 0xC7) == 0x04)
        return instr_inc_r8_or_mem_hl(cpu, opcode);

    // Instructions: DEC r8
    // 8 Opcodes: (0x05,0x15,0x25,0x35,0x0D,0x1D,0x2D,0x3D)
    // Encoding: 00 rrr 101
    if (MASK_BITS(opcode, 0xC7) == 0x05)
        return instr_dec_r8_or_mem_hl(cpu, opcode);

    // Instructions: ALU A, n
    // 8 Opcodes: (0xC6,0xD6,0xE6,0xF6,0xCE,0xDE,0xEE,0xFE)
    // Encoding: 11 ooo 110
    if (MASK_BITS(opcode, 0xC7) == 0xC6)
        return instr_alu_a_n(cpu, opcode);

    // Instructions: ALU A, r8
    // 64 Opcodes: (0x80-0xBF)
    // Encoding: 10 ooo sss
    if (opcode >= 0x80 && opcode <= 0xBF)
        return instr_alu_a_r8_or_mem_hl(cpu, opcode);

    if (instr_table[opcode] == NULL) {
        put_error("Illegal operation code: 0x%02x at PC = 0x%04x\n", opcode, cpu->pc - 1);
        return ILLEGAL;
    }
    return instr_table[opcode](cpu);
}
