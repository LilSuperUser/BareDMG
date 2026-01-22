// include/gbemu.h
#ifndef GBEMU_H
#define GBEMU_H

#include <core/cpu/cpu.h>
#include <core/cartridge.h>
#include <core/utils.h>

// ---------------------------------------------
// Main GameBoy Struct
// ---------------------------------------------
typedef struct GameBoy {
    // Components will be added as they are implemented.
    CPU       cpu;
    Cartridge cart;

    // Memory
    // https://gbdev.io/pandocs/Memory_Map.html#memory-map
    u8        vram[0x2000]; // Video RAM - 8 KB (0x8000 - 0x9FFF)
    u8        wram[0x2000]; // Work RAM - 8 KB (0xC000 - 0xDFFF)
    u8        oam[0xA0];    // Object Attribute Memory - 160 B (0xFE00 - 0xFE9E)
    u8        hram[0x7F];   // High RAM - 127 B (0xFF88 - 0xFFFE)

    // I/O Registers
    u8        ie_register; // Interrupt Enable Register (0xFFFF)

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

// ---------------------------------------------
// I/O Handlers (called by MMU)
// ---------------------------------------------
u8   io_read(GameBoy *gb, u16 addr);
void io_write(GameBoy *gb, u16 addr, u8 value);

#endif // !GBEMU_H
