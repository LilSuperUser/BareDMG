// src/main.c
#include <core/cartridge.h>
#include <core/bus.h>
#include <core/cpu/cpu.h>
#include <gbemu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Print the user Instructions
static void print_usage(const char *program_name) {
    printf("Usage: %s <path_to_rom>\n", program_name);
    printf("\n");
    printf("Options:\n");
    printf("  <path_to_rom>    Path to Game Boy ROM file (.gb)\n");
}

int main(int argc, char *argv[]) {
    // Check arguments
    if (argc < 2) {
        fprintf(stderr, "Error: No ROM file specified\n\n");
        print_usage(argv[0]);
        return -2;
    }

    const char *rom_path   = argv[1];
    bool        run_mode   = false;
    bool        debug_mode = false;
    int         step_count = 0;

    // Parse options
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--run") == 0)
            run_mode = true;
        else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0)
            debug_mode = true;
        else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--step") == 0) {
            if (i + 1 < argc)
                step_count = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--info") == 0) {
            // Info mode (default mode)
        } else {
            fprintf(stderr, "Unknown Options: %s\n", argv[i]);
            print_usage(argv[0]);
            return 1;
        }
    }

    // Print banner
    printf("=================================\n");
    printf("          BareDMG\n");
    printf("    Game Boy Emulator (DMG-01)\n");
    printf("=================================\n");
    printf("\n");

    // Initialize Game Boy
    GameBoy gb;
    gb_init(&gb);

    // Load ROM && Print the parsed header
    printf("Loading ROM: %s\n", rom_path);
    gb_load_rom(&gb, rom_path);

    // Check if the load was successful
    if (!gb.running) {
        fprintf(stderr, "Failed to load ROM\n");
        return -3;
    }

    // ROM loaded Successfully
    printf("ROM Loaded Successfully!\n");

    // If just info mode, exit
    if (!run_mode && step_count == 0) {
        cart_unload(&gb.cart);
        return 0;
    }

    // Run or Step mode
    if (step_count > 0) {
        printf("\nExecuting %d instructions...\n\n", step_count);

        for (int i = 0; i < step_count; i++) {
            u16 pc_before = gb.cpu.pc;
            u8  opcode    = mmu_read(&gb, pc_before);

            // Verbose output if debug mode
            if (debug_mode) {
                printf("[%04d] PC=0x%04X  Opcode=0x%02X  A=%02X B=%02X C=%02X D=%02X E=%02X H=%02X "
                       "L=%02X SP=%04X F=%02X\n",
                       i, pc_before, opcode, gb.cpu.regs.a, gb.cpu.regs.b, gb.cpu.regs.c,
                       gb.cpu.regs.d, gb.cpu.regs.e, gb.cpu.regs.h, gb.cpu.regs.l, gb.cpu.sp,
                       gb.cpu.regs.f);
            }
            gb_step(&gb);

            // Stop if HALT is encountered
            if (gb.cpu.halted) {
                printf("\nCPU halted at PC=0x%04X after %d instructions\n", pc_before, i + 1);
                break;
            }

            // Report if infinite loop is detected
            // 0x76 is HALT
            if (gb.cpu.pc == pc_before && opcode != 0x76) {
                printf("\nInfinite loop detected at PC=0x%04X\n", pc_before);
                break;
            }
        }
        // Print the final state of CPU
        printf("\nFinal state:\n");
        printf("  PC = 0x%04X\n", gb.cpu.pc);
        printf("  SP = 0x%04X\n", gb.cpu.sp);
        printf("  A  = 0x%02X  F = 0x%02X (AF = 0x%04X)\n", gb.cpu.regs.a, gb.cpu.regs.f,
               cpu_read_af(&gb.cpu));
        printf("  B  = 0x%02X  C = 0x%02X (BC = 0x%04X)\n", gb.cpu.regs.b, gb.cpu.regs.c,
               cpu_read_bc(&gb.cpu));
        printf("  D  = 0x%02X  E = 0x%02X (DE = 0x%04X)\n", gb.cpu.regs.d, gb.cpu.regs.e,
               cpu_read_de(&gb.cpu));
        printf("  H  = 0x%02X  L = 0x%02X (HL = 0x%04X)\n", gb.cpu.regs.h, gb.cpu.regs.l,
               cpu_read_hl(&gb.cpu));
        printf("  Flags: Z=%d N=%d H=%d C=%d\n", cpu_get_flag(&gb.cpu, FLAG_ZERO) ? 1 : 0,
               cpu_get_flag(&gb.cpu, FLAG_SUBT) ? 1 : 0,
               cpu_get_flag(&gb.cpu, FLAG_HF_CARRY) ? 1 : 0,
               cpu_get_flag(&gb.cpu, FLAG_CARRY) ? 1 : 0);
        printf("  Total cycles: %llu\n", (unsigned long long)gb.cycles);

    } else if (run_mode) {
        printf("Running emulator (press Ctrl+C to stop)...\n");
        printf("NOTE: No PPU/APU yet, this will just execute instructions.\n\n");

        // Run for a limited time (100000 instructions)
        for (int i = 0; i < 100000 && gb.running && !gb.cpu.halted; i++) {
            gb_step(&gb);
        }

        printf("\nEmulation Ran Out.\n");
        printf("Final PC: 0x%04X\n", gb.cpu.pc);
        printf("Total cycles: %llu\n", (unsigned long long)gb.cycles);
    }

    // Clean up
    cart_unload(&gb.cart);

    puts("\nExiting...\n");
    return 0;
}
