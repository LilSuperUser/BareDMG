// src/main.c
#include <core/cartridge.h>
#include <core/bus.h>
#include <core/cpu/cpu.h>
#include <gbemu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RUN_DEBUG_INTERVAL 1000

// Config structure for CLI args
typedef enum { MODE_INFO, MODE_STEP, MODE_RUN, MODE_TEST } EmulatorMode;

typedef struct {
    const char  *rom_path;
    EmulatorMode mode;
    int          step_count;
    bool         debug_mode;
} CliConfig;

// Print the usage information
static void print_usage(const char *program_name) {
    printf("Usage: %s [options] <path_to_rom>\n", program_name);
    printf("\n");
    printf("Modes (mutually exclusive):\n");
    printf("  -i               Info mode (default): load ROM, print header info, then exit\n");
    printf("  -s <num>         Step mode: execute exactly <num> CPU instructions\n");
    printf("  -r               Run mode: execute instructions until timeout or HALT\n");
    printf("\n");
    printf("Other options:\n");
    printf("  -d               Debug mode (verbose CPU state output)\n");
    printf("  -t               Test mode: run ROM until completion (for test ROMs)\n");
    printf("  -h               Show this help message\n");
}

// NOTE: Test function to test the serial output
// Working as of now
static void test_serial_output(void) {
    printf("\n=== Testing Serial Output ===\n");

    GameBoy gb;
    gb_init(&gb);

    // Manually write to serial registers (simulating what ROM does)
    io_write(&gb, 0xFF01, 'H');  // Write 'H' to SB
    io_write(&gb, 0xFF02, 0x81); // Start transfer (bit 7 set)

    printf("Serial cycles initialized: %d\n", gb.serial_cycles);
    printf("Running cycles to complete transfer...\n");

    // Run for 600 cycles to complete the 512-cycle transfer
    for (int i = 0; i < 150; i++) { // 150 * 4 = 600 cycles
        u8 cycles = 4;
        gb.cycles += cycles;

        // Handle serial transfer (copy from gb_step)
        if (gb.serial_cycles > 0) {
            if (gb.serial_cycles <= cycles) {
                gb.serial_cycles = 0;
                printf("[SERIAL] Outputting: '%c' (0x%02X)\n", gb.io.sb, gb.io.sb);
                putchar(gb.io.sb);
                fflush(stdout);
                gb.io.sc     = CLEAR_BIT(gb.io.sc, 7);
                gb.io.if_reg = SET_BIT(gb.io.if_reg, 3);
            } else {
                gb.serial_cycles -= cycles;
            }
        }
    }

    printf("\n=== Serial Test Complete ===\n\n");
}

// Print the CPU state
static void print_cpu_state(GameBoy *gb) {
    printf("\nFinal state:\n");
    printf("  PC = 0x%04X\n", gb->cpu.pc);
    printf("  SP = 0x%04X\n", gb->cpu.sp);
    printf("  AF = 0x%04X\n", cpu_read_af(&gb->cpu));
    printf("  BC = 0x%04X\n", cpu_read_bc(&gb->cpu));
    printf("  DE = 0x%04X\n", cpu_read_de(&gb->cpu));
    printf("  HL = 0x%04X\n", cpu_read_hl(&gb->cpu));
    printf("  Flags: Z=%d N=%d H=%d C=%d\n", cpu_get_flag(&gb->cpu, FLAG_ZERO),
           cpu_get_flag(&gb->cpu, FLAG_SUBT), cpu_get_flag(&gb->cpu, FLAG_HF_CARRY),
           cpu_get_flag(&gb->cpu, FLAG_CARRY));
    printf("  Total cycles: %llu\n", (unsigned long long)gb->cycles);
}

int main(int argc, char *argv[]) {
    /* test_serial_output(); */

    if (argc < 2) {
        fprintf(stderr, "Error: No ROM file specified\n\n");
        print_usage(argv[0]);
        return 1;
    }

    // Print banner
    printf("=================================\n");
    printf("          BareDMG\n");
    printf("    Game Boy Emulator (DMG-01)\n");
    printf("=================================\n\n");

    const char *rom_path       = NULL;
    bool        mode_specified = false;
    bool        run_mode       = false;
    bool        debug_mode     = false;
    bool        test_mode      = false;
    bool        info_mode      = false;
    int         step_count     = 0;

    // Parse arguments
    for (int i = 1; i < argc; i++) {

        // Flag
        if (argv[i][0] == '-') {

            if (strcmp(argv[i], "-h") == 0) {
                print_usage(argv[0]);
                return 0;
            }

            else if (strcmp(argv[i], "-r") == 0) {
                if (step_count > 0) {
                    fprintf(stderr, "Error: -r and -s cannot be used together\n");
                    return 1;
                }
                run_mode       = true;
                mode_specified = true;
            }

            else if (strcmp(argv[i], "-s") == 0) {
                if (run_mode) {
                    fprintf(stderr, "Error: -s and -r cannot be used together\n");
                    return 1;
                }
                if (i + 1 >= argc) {
                    fprintf(stderr, "Error: -s requires a number\n");
                    return 1;
                }
                step_count = atoi(argv[++i]);
                if (step_count <= 0) {
                    fprintf(stderr, "Error: Invalid step count\n");
                    return 1;
                }
                mode_specified = true;
            }

            else if (strcmp(argv[i], "-i") == 0) {
                info_mode      = true;
                mode_specified = true;
            }

            else if (strcmp(argv[i], "-d") == 0) {
                debug_mode = true;
            }

            else if (strcmp(argv[i], "-t") == 0) {
                if (step_count > 0 || run_mode) {
                    fprintf(stderr, "Error: -t cannot be used with -s or -r\n");
                    return 1;
                }
                test_mode      = true;
                mode_specified = true;
            }

            else {
                fprintf(stderr, "Unknown option: %s\n", argv[i]);
                print_usage(argv[0]);
                return 1;
            }
        }

        // Not a flag (ROM file)
        else {
            if (rom_path != NULL) {
                fprintf(stderr, "Error: Multiple ROM files specified\n");
                return 1;
            }
            rom_path = argv[i];
        }
    }

    // Check if the ROM file was provided
    if (!rom_path) {
        fprintf(stderr, "Error: No ROM file specified\n\n");
        print_usage(argv[0]);
        return 1;
    }

    // Default to info mode if no mode specified
    if (!mode_specified) {
        info_mode = true;
        printf("No mode specified; defaulting to info mode (-i)\n\n");
    }

    if (info_mode && debug_mode) {
        printf("Note: debug mode (-d) has no effect in info mode\n\n");
    }

    // Initialize Game Boy and load ROM
    GameBoy gb;
    gb_init(&gb);
    gb_load_rom(&gb, rom_path);

    if (!gb.running) {
        fprintf(stderr, "Failed to load ROM\n");
        return 1;
    }

    printf("ROM Loaded Successfully!\n");

    // Info mode: Exit after loading & printing cartridge info
    if (info_mode) {
        cart_unload(&gb.cart);
        return 0;
    }

    // Step mode
    if (step_count > 0) {
        printf("\nExecuting %d instructions...\n\n", step_count);

        for (int i = 0; i < step_count; i++) {
            u16 pc_before = gb.cpu.pc;
            u8  opcode    = mmu_read(&gb, pc_before);

            if (debug_mode) {
                printf("[%04d] PC=0x%04X Opcode=0x%02X "
                       "A=%02X B=%02X C=%02X D=%02X E=%02X H=%02X L=%02X "
                       "SP=%04X F=%02X\n",
                       i, pc_before, opcode, gb.cpu.regs.a, gb.cpu.regs.b, gb.cpu.regs.c,
                       gb.cpu.regs.d, gb.cpu.regs.e, gb.cpu.regs.h, gb.cpu.regs.l, gb.cpu.sp,
                       gb.cpu.regs.f);
            }

            gb_step(&gb);

            if (gb.cpu.halted) {
                printf("\nCPU halted at PC=0x%04X after %d instructions\n", pc_before, i + 1);
                print_cpu_state(&gb);
                break;
            }

            if (gb.cpu.pc == pc_before && opcode != 0x76) {
                printf("\nInfinite loop detected at PC=0x%04X\n", pc_before);
                print_cpu_state(&gb);
                break;
            }
        }
        // print the final state of the CPU
        print_cpu_state(&gb);
    }

    // Run mode
    else if (run_mode) {
        printf("Running emulator (press Ctrl+C to stop)...\n");
        printf("NOTE: No PPU/APU yet, this will just execute instructions.\n\n");

        for (int i = 0; i < 100000 && gb.running && !gb.cpu.halted; i++) {
            gb_step(&gb);

            // Verbose output per interval if debug mode
            if (debug_mode && (i % RUN_DEBUG_INTERVAL == 0)) {
                printf("[RUN %06d] PC=0x%04X SP=0x%04X AF=%04X BC=%04X DE=%04X HL=%04X\n", i,
                       gb.cpu.pc, gb.cpu.sp, cpu_read_af(&gb.cpu), cpu_read_bc(&gb.cpu),
                       cpu_read_de(&gb.cpu), cpu_read_hl(&gb.cpu));
            }
        }

        printf("\nEmulation finished.\n");
        print_cpu_state(&gb);
    }

    else if (test_mode) {
        printf("Running test ROM...\n");
        printf("(Serial output will appear below)\n");
        printf("─────────────────────────────────\n\n");

        u64 max_cycles     = 100000000; // 100M cycles = ~24 seconds
        u64 last_pc        = 0;
        u64 pc_stuck_count = 0;

        while (gb.cycles < max_cycles && gb.running && !gb.cpu.halted) {
            u16 pc_before = gb.cpu.pc;

            gb_step(&gb);

            // NOTE: Debug: Print first 100 instructions
            // To be removed later on (This shit just isnt working right now)
            if (gb.cycles < 500) {
                printf("[%llu] PC=0x%04X opcode=0x%02X A=%02X F=%02X BC=%04X DE=%04X HL=%04X "
                       "SP=%04X\n",
                       (unsigned long long)gb.cycles, pc_before, mmu_read(&gb, pc_before),
                       gb.cpu.regs.a, gb.cpu.regs.f, cpu_read_bc(&gb.cpu), cpu_read_de(&gb.cpu),
                       cpu_read_hl(&gb.cpu), gb.cpu.sp);
            }

            // Detect infinite loops
            if (pc_before == last_pc) {
                pc_stuck_count++;
                if (pc_stuck_count > 10000) {
                    printf("\n[ERROR] CPU stuck in infinite loop at PC=0x%04X\n", pc_before);
                    printf("Opcode at PC: 0x%02X\n", mmu_read(&gb, pc_before));
                    break;
                }

            } else {
                pc_stuck_count = 0;
                last_pc        = pc_before;
            }

            // Debug output if debug mode
            if (debug_mode && (gb.cycles % 10000 == 0)) {
                printf("[%llu cycles] PC=0x%04X\n", (unsigned long long)gb.cycles, gb.cpu.pc);
            }
        }

        printf("\n─────────────────────────────────\n");

        if (gb.cpu.halted) {
            printf("Test completed (CPU halted)\n");
            cart_unload(&gb.cart);
            return 0;

        } else if (gb.cycles >= max_cycles) {
            printf("Test timeout (exceeded %llu cycles)\n", (unsigned long long)max_cycles);
            printf("Final PC: 0x%04X\n", gb.cpu.pc);
            cart_unload(&gb.cart);
            return 1;
        }
    }

    cart_unload(&gb.cart);
    puts("\nExiting...\n");
    return 0;
}
