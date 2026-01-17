// include/gbemu.h
#ifndef GBEMU_H
#define GBEMU_H

#include <core/cartridge.h>
#include <core/utils.h>

// ---------------------------------------------
// Main GameBoy Struct
// ---------------------------------------------
typedef struct GameBoy {
    // TODO: CPU
    Cartridge cart;

    // Work RAM (8 KB)
    u8        wram[0x2000]; // 0xC000 - 0xDFFF

    // High RAM (127 bytes)
    u8        hram[0x7F]; // 0xFF80 - 0xFFFE

    // Interrupt Enable register
    u8        ie_register; // 0xFFFF

    // System state
    u64       cycles;
    bool      running;
} GameBoy;

// ---------------------------------------------
// Emulator Functions
// ---------------------------------------------
void gb_init(GameBoy *gb);
void gb_load_rom(GameBoy *gb, const char *path);
void gb_step(GameBoy *gb);
void gb_run_frame(GameBoy *gb);

#endif // !GBEMU_H
