// src/core/cpu/cpu_decode.c
#include <core/cpu/cpu_decode.h>
#include <core/bus.h>

// Fetch and decode a CB-prefixed opcode's second byte
CBOpcode cpu_decode_cb(CPU *cpu) {
    u8       byte = mmu_read(cpu->gb, cpu->pc++);

    CBOpcode decoded;
    decoded.group     = (CBGroup)GET_BITS(byte, 6, 2);
    decoded.bit_or_op = GET_BITS(byte, 3, 3);
    decoded.r         = GET_BITS(byte, 0, 3);

    return decoded;
}

// r8 index convention shared across the CPU's opcode encoding:
// 0=B 1=C 2=D 3=E 4=H 5=L 6=(HL) 7=A
u8 cb_read_r8(CPU *cpu, u8 r) {
    switch (r) {
        case 0:
            return cpu->regs.b;
        case 1:
            return cpu->regs.c;
        case 2:
            return cpu->regs.d;
        case 3:
            return cpu->regs.e;
        case 4:
            return cpu->regs.h;
        case 5:
            return cpu->regs.l;
        case 6:
            return mmu_read(cpu->gb, cpu_read_hl(cpu));
        case 7:
            return cpu->regs.a;
        default:
            return 0xFF; // unreachable, r is always 3 bits
    }
}

void cb_write_r8(CPU *cpu, u8 r, u8 value) {
    switch (r) {
        case 0:
            cpu->regs.b = value;
            break;
        case 1:
            cpu->regs.c = value;
            break;
        case 2:
            cpu->regs.d = value;
            break;
        case 3:
            cpu->regs.e = value;
            break;
        case 4:
            cpu->regs.h = value;
            break;
        case 5:
            cpu->regs.l = value;
            break;
        case 6:
            mmu_write(cpu->gb, cpu_read_hl(cpu), value);
            break;
        case 7:
            cpu->regs.a = value;
            break;
    }
}
