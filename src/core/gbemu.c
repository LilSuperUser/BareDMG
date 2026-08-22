// src/core/gbemu.c
#include <gbemu.h>
#include <core/bus.h>
#include <string.h>
#include <stdio.h>

// Initialize the GameBoy instance
void gb_init(GameBoy *gb) {
    memset(gb, 0, sizeof(GameBoy));
    cpu_init(&gb->cpu, gb);

    // Initialize I/O registers to power-up state
    put_emulator("Initializing I/O registers to power-up state...\n");
    gb->io.joyp     = 0xCF;

    gb->io.sb       = 0x00;
    gb->io.sc       = 0x7E;

    gb->io.div      = 0xAB;
    gb->io.tima     = 0x00;
    gb->io.tma      = 0x00;
    gb->io.tac      = 0xF8;

    gb->io.if_reg   = 0xE1;
    gb->ie_register = 0x00;

    gb->io.lcdc     = 0x91;
    gb->io.stat     = 0x85;
    gb->io.scy      = 0x00;
    gb->io.scx      = 0x00;
    gb->io.ly       = 0x00;
    gb->io.lyc      = 0x00;
    gb->io.bgp      = 0xFC;
    gb->io.obp0     = 0x00;
    gb->io.obp1     = 0x00;
    gb->io.wy       = 0x00;
    gb->io.wx       = 0x00;

    gb->io.boot     = 0x00;
    put_success("I/O registers initialized successfully!\n\n");
    gb->running = true;
}

// Load a cartridge into GameBoy
// TODO: Remove the call to cart_print_header
// Create a proper gb_print_cart_info() to print header when info mode is set
bool gb_load_rom(GameBoy *gb, const char *path) {
    // Try to load the cartridge
    put_emulator("Loading ROM...\n");

    // TODO: Might print details about the error (using error codes)
    if (cart_load(&gb->cart, path) != 0) {
        put_error("Failed to load ROM!\n");
        gb->running = false;
        return false;
    }

    return true;
}

// Execute a single CPU instruction step
void gb_step(GameBoy *gb) {
    if (!gb->running)
        return;

    u8 cycles = cpu_step(&gb->cpu);
    gb->cycles += cycles;

    // Handle serial transfer
    if (gb->serial_cycles > 0) {
        if (gb->serial_cycles <= cycles) {
            // Transfer complete
            gb->serial_cycles = 0;
            printf("[SERIAL] Outputting: '%c' (0x%02X)\n",
                   gb->io.sb >= 0x20 && gb->io.sb < 0x7F ? gb->io.sb : '?', gb->io.sb);
            putchar(gb->io.sb);
            fflush(stdout);
            gb->io.sc     = CLEAR_BIT(gb->io.sc, 7);
            gb->io.if_reg = SET_BIT(gb->io.if_reg, 3);
        }
        else {
            gb->serial_cycles -= cycles;
        }
    }
}

// Run the emulator for the duration of one video frame
void gb_run_frame(GameBoy *gb) {
    if (!gb->running)
        return;

    // GameBoy runs at ~4.19 MHz
    // 1 frame @ 60 Hz = 70224 cycles
    u32 frame_cycles = 0;

    while (frame_cycles < 70224) {
        u8 cycles = cpu_step(&gb->cpu);
        frame_cycles += cycles;
        gb->cycles += cycles;
    }
}

// Dump PC/SP/register pairs/flags/cycle count (for debugging)
void gb_print_state(GameBoy *gb) {
    printf("\n%sFinal state:%s\n", BOLD_WHITE, RESET);
    printf("  PC = 0x%04X\n", gb->cpu.pc);
    printf("  SP = 0x%04X\n", gb->cpu.sp);
    printf("  AF = 0x%04X\n", cpu_read_af(&gb->cpu));
    printf("  BC = 0x%04X\n", cpu_read_bc(&gb->cpu));
    printf("  DE = 0x%04X\n", cpu_read_de(&gb->cpu));
    printf("  HL = 0x%04X\n", cpu_read_hl(&gb->cpu));
    printf("  Flags: Z=%d N=%d H=%d C=%d\n", cpu_get_flag(&gb->cpu, FLAG_ZERO),
           cpu_get_flag(&gb->cpu, FLAG_SUBT), cpu_get_flag(&gb->cpu, FLAG_HF_CARRY),
           cpu_get_flag(&gb->cpu, FLAG_CARRY));
    printf("  Total cycles: %llu\n\n", (unsigned long long)gb->cycles);
}

// Print cartridge information to stdout
void gb_print_cart_info(GameBoy *gb) {
    put_emulator("Printing cartridge information below...\n\n");
    cart_print_header(&gb->cart.header);
}

// Execute exactly `step_count` instructions (-s <num>)
GbRunStatus gb_run_step(GameBoy *gb, int step_count, bool debug_mode) {
    if (debug_mode)
        put_emulator("Executing %d instructions (in debug mode)...\n\n", step_count);
    else
        put_emulator("Executing %d instructions...\n", step_count);

    GbRunStatus status = GB_RUN_OK;

    for (int i = 0; i < step_count; i++) {
        u16 pc_before = gb->cpu.pc;
        u8  opcode    = mmu_read(gb, pc_before);

        if (debug_mode) {
            put_debug("[%04d] PC=0x%04X Opcode=0x%02X "
                      "A=%02X B=%02X C=%02X D=%02X E=%02X H=%02X L=%02X "
                      "SP=%04X F=%02X\n",
                      i, pc_before, opcode, gb->cpu.regs.a, gb->cpu.regs.b, gb->cpu.regs.c,
                      gb->cpu.regs.d, gb->cpu.regs.e, gb->cpu.regs.h, gb->cpu.regs.l, gb->cpu.sp,
                      gb->cpu.regs.f);
        }

        gb_step(gb);

        if (gb->cpu.halted) {
            put_info("\nCPU halted at PC=0x%04X after %d instructions\n", pc_before, i + 1);
            status = GB_RUN_HALTED;
            break;
        }

        if (gb->cpu.pc == pc_before && opcode != 0x76) {
            put_error("\nInfinite loop detected at PC=0x%04X\n", pc_before);
            status = GB_RUN_STUCK;
            break;
        }
    }

    gb_print_state(gb);
    return status;
}

// Execute until HALT or an internal iteration cap (-r)
GbRunStatus gb_run_continuous(GameBoy *gb, bool debug_mode) {
    if (debug_mode) {
        put_emulator("Running emulator in debug mode (press Ctrl+C to stop)...\n\n");
        put_warning("No PPU/APU yet; this will only execute CPU instructions.\n\n");
    }
    else {
        put_emulator("Running emulator (press Ctrl+C to stop)...\n\n");
        put_warning("No PPU/APU yet; this will only execute CPU instructions.\n\n");
    }

    GbRunStatus status = GB_RUN_OK;

    for (int i = 0; i < GB_RUN_MAX_ITERATIONS && gb->running && !gb->cpu.halted; i++) {
        gb_step(gb);

        if (debug_mode && (i % GB_RUN_DEBUG_INTERVAL == 0)) {
            put_debug("[RUN %06d] PC=0x%04X SP=0x%04X AF=%04X BC=%04X DE=%04X HL=%04X\n", i,
                      gb->cpu.pc, gb->cpu.sp, cpu_read_af(&gb->cpu), cpu_read_bc(&gb->cpu),
                      cpu_read_de(&gb->cpu), cpu_read_hl(&gb->cpu));
        }
    }

    if (gb->cpu.halted) {
        status = GB_RUN_HALTED;
    }
    else if (gb->running) {
        put_error("Emulation timed out after %d iterations\n", GB_RUN_MAX_ITERATIONS);
        status = GB_RUN_TIMEOUT;
    }

    puts("");
    put_info("Emulation finished!\n");
    gb_print_state(gb);

    return status;
}

// Execute until HALT / cycle budget reached / PC gets stuck (used by `-t`)
GbRunStatus gb_run_test(GameBoy *gb, bool debug_mode) {
    if (debug_mode) {
        put_emulator("Running test ROM in debug mode...\n");
        put_info("Serial output will appear below.\n\n");
    }
    else {
        put_emulator("Running test ROM...\n");
        put_info("Serial output will appear below.\n\n");
    }
    put_bold("────────────────────────────────────────────────────────────────\n\n");

    u64         last_pc        = 0;
    u64         pc_stuck_count = 0;
    GbRunStatus status         = GB_RUN_OK;

    while (gb->cycles < GB_TEST_MAX_CYCLES && gb->running && !gb->cpu.halted) {
        u16 pc_before = gb->cpu.pc;

        gb_step(gb);

        // Debug: Print full trace for the first GB_TEST_TRACE_CYCLES cycles
        if (gb->cycles < GB_TEST_TRACE_CYCLES) {
            put_debug("[%llu] PC=0x%04X opcode=0x%02X A=%02X F=%02X BC=%04X DE=%04X HL=%04X "
                      "SP=%04X\n",
                      (unsigned long long)gb->cycles, pc_before, mmu_read(gb, pc_before),
                      gb->cpu.regs.a, gb->cpu.regs.f, cpu_read_bc(&gb->cpu), cpu_read_de(&gb->cpu),
                      cpu_read_hl(&gb->cpu), gb->cpu.sp);
        }

        // Detect infinite loops
        if (pc_before == last_pc) {
            pc_stuck_count++;
            if (pc_stuck_count > GB_TEST_STUCK_LIMIT) {
                puts("");
                put_error("CPU stuck in infinite loop at PC=0x%04X\n", pc_before);
                put_error("Opcode at PC: 0x%02X\n", mmu_read(gb, pc_before));
                status = GB_RUN_STUCK;
                break;
            }
        }
        else {
            pc_stuck_count = 0;
            last_pc        = pc_before;
        }

        if (debug_mode && (gb->cycles % GB_TEST_DEBUG_INTERVAL == 0)) {
            put_debug("[%llu cycles] PC=0x%04X\n", (unsigned long long)gb->cycles, gb->cpu.pc);
        }
    }

    puts("");
    put_bold("────────────────────────────────────────────────────────────────\n\n");

    if (status == GB_RUN_STUCK) {
        // Already reported above
    }
    else if (gb->cpu.halted) {
        put_success("Test completed (CPU halted)\n");
        status = GB_RUN_HALTED;
    }
    else if (gb->cycles >= GB_TEST_MAX_CYCLES) {
        put_error("Test timeout (exceeded %llu cycles)\n", (unsigned long long)GB_TEST_MAX_CYCLES);
        put_error("Final PC: 0x%04X\n\n", gb->cpu.pc);
        status = GB_RUN_TIMEOUT;
    }

    return status;
}
