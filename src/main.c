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

// Helper function to parse command line arguments into CliConfig
static bool parse_cli_args(int argc, char *argv[], CliConfig *config) {
    // Initialize defaults
    config->rom_path   = NULL;
    config->mode       = MODE_INFO; // Default mode
    config->step_count = 0;
    config->debug_mode = false;

    if (argc < 2) {
        fprintf(stderr, "Error: No ROM file specified\n\n");
        print_usage(argv[0]);
        return false;
    }
    bool mode_specified = false;

    // Parse arguments
    for (int i = 1; i < argc; i++) {

        // Detect a flag
        if (argv[i][0] == '-') {

            // Help mode
            if (strcmp(argv[i], "-h") == 0) {
                print_usage(argv[0]);
                exit(0);
            }

            // Run mode
            else if (strcmp(argv[i], "-r") == 0) {
                if (config->step_count > 0) {
                    fprintf(stderr, "Error: -r and -s cannot be used together\n");
                    return false;
                }
                config->mode   = MODE_RUN;
                mode_specified = true;
            }

            // Step mode
            else if (strcmp(argv[i], "-s") == 0) {
                if (config->mode == MODE_RUN) {
                    fprintf(stderr, "Error: -s and -r cannot be used together\n");
                    return false;
                }
                if (config->mode == MODE_TEST) {
                    fprintf(stderr, "Error: -s and -t cannot be used together\n");
                    return false;
                }
                if (i + 1 >= argc) {
                    fprintf(stderr, "Error: -s requires a number\n");
                    return false;
                }
                config->step_count = atoi(argv[++i]);
                if (config->step_count <= 0) {
                    fprintf(stderr, "Error: Invalid step count\n");
                    return false;
                }
                config->mode   = MODE_STEP;
                mode_specified = true;
            }

            // Info mode
            else if (strcmp(argv[i], "-i") == 0) {
                config->mode   = MODE_INFO;
                mode_specified = true;
            }

            // Debug mode
            else if (strcmp(argv[i], "-d") == 0) {
                config->debug_mode = true;
            }

            // Test mode
            else if (strcmp(argv[i], "-t") == 0) {
                if (config->step_count > 0 || config->mode == MODE_RUN) {
                    fprintf(stderr, "Error: -t cannot be used with -s or -r\n");
                    return false;
                }
                config->mode   = MODE_TEST;
                mode_specified = true;
            }

            else {
                fprintf(stderr, "Unknown option: %s\n", argv[i]);
                print_usage(argv[0]);
                return false;
            }
        }

        // Not a flag (ROM file)
        else {
            if (config->rom_path != NULL) {
                fprintf(stderr, "Error: Multiple ROM files specified\n");
                return false;
            }
            config->rom_path = argv[i];
        }
    }

    // Check if the ROM file was provided
    if (!config->rom_path) {
        fprintf(stderr, "Error: No ROM file specified\n\n");
        print_usage(argv[0]);
        return false;
    }

    // Default to info mode if no mode specified
    if (!mode_specified) {
        config->mode = MODE_INFO;
        printf("No mode specified; defaulting to info mode (-i)\n\n");
    }

    // Warn if info & debug mode both used
    if (config->mode == MODE_INFO && config->debug_mode) {
        printf("Note: debug mode (-d) has no effect in info mode\n\n");
    }

    return true;
}

// NOTE: Test function to test the serial output
// Working as of now
/* static void test_serial_output(void) { */
/*     printf("\n=== Testing Serial Output ===\n"); */
/**/
/*     GameBoy gb; */
/*     gb_init(&gb); */
/**/
/*     // Manually write to serial registers (simulating what ROM does) */
/*     io_write(&gb, 0xFF01, 'H');  // Write 'H' to SB */
/*     io_write(&gb, 0xFF02, 0x81); // Start transfer (bit 7 set) */
/**/
/*     printf("Serial cycles initialized: %d\n", gb.serial_cycles); */
/*     printf("Running cycles to complete transfer...\n"); */
/**/
/*     // Run for 600 cycles to complete the 512-cycle transfer */
/*     for (int i = 0; i < 150; i++) { // 150 * 4 = 600 cycles */
/*         u8 cycles = 4; */
/*         gb.cycles += cycles; */
/**/
/*         // Handle serial transfer (copy from gb_step) */
/*         if (gb.serial_cycles > 0) { */
/*             if (gb.serial_cycles <= cycles) { */
/*                 gb.serial_cycles = 0; */
/*                 printf("[SERIAL] Outputting: '%c' (0x%02X)\n", gb.io.sb, gb.io.sb); */
/*                 putchar(gb.io.sb); */
/*                 fflush(stdout); */
/*                 gb.io.sc     = CLEAR_BIT(gb.io.sc, 7); */
/*                 gb.io.if_reg = SET_BIT(gb.io.if_reg, 3); */
/*             } else { */
/*                 gb.serial_cycles -= cycles; */
/*             } */
/*         } */
/*     } */
/**/
/*     printf("\n=== Serial Test Complete ===\n\n"); */
/* } */

// Map a GbRunStatus from one of the gb_run_* drivers to a process exit code
static int status_to_exit_code(GbRunStatus status) {
    switch (status) {
        case GB_RUN_TIMEOUT:
            return 1;
        case GB_RUN_STUCK:
            return 2;
        case GB_RUN_OK:
        case GB_RUN_HALTED:
        default:
            return 0;
    }
}

int main(int argc, char *argv[]) {
    // Print banner
    printf("=================================\n");
    printf("          BareDMG\n");
    printf("    Game Boy Emulator (DMG-01)\n");
    printf("=================================\n\n");

    // Parse CLI args
    CliConfig config;
    if (!parse_cli_args(argc, argv, &config)) {
        return 1;
    }

    // Initialize Game Boy and load ROM
    GameBoy gb;
    gb_init(&gb);
    gb_load_rom(&gb, config.rom_path);

    if (!gb.running) {
        fprintf(stderr, "Failed to load ROM\n");
        return 1;
    }

    // Dispatch to the driver for the selected mode
    // Each gb_run_* function owns its own loop, diagnostics, and halt/stuck/timeout detection
    // main() will just pick which one to invoke and what to do with the result
    GbRunStatus status = GB_RUN_OK;

    switch (config.mode) {
        case MODE_INFO:
            // Nothing to do
            // gb_load_rom already prints the header
            break;

        case MODE_STEP:
            status = gb_run_step(&gb, config.step_count, config.debug_mode);
            break;

        case MODE_RUN:
            status = gb_run_continuous(&gb, config.debug_mode);
            break;

        case MODE_TEST:
            status = gb_run_test(&gb, config.debug_mode);
            break;
    }

    cart_unload(&gb.cart);
    puts("\nExiting...\n");

    return status_to_exit_code(status);
}
