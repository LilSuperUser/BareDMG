## BareDMG

A **Game Boy emulator** written in **C**, focused on clarity and hardware accuracy.

### Philosophy

**BareDMG** models the **Game Boy as actual hardware components**, not as a single blob of logic. Each part of the system (**CPU**, **PPU**, **memory bus**, **cartridge**) is implemented as separate module with its own state and interface.

### Hardware-First Design

The emulator is structured around the same major components that exist in real hardware:

- **CPU (`LR35902`)** - instruction fetch, decode, execute
- **BUS/MMU** - routes all memory access between components
- **Cartridge** - ROM data, external RAM, and blank switching (MBC)
- **PPU** - video timing, scanline rendering, & display
- **APU** - audio timing and mixing
- **Timers** - `DIV` and `TIMA` behavior
- **Joypad** - input state management

#### Each of these components:

- owns its **own state**.
- exposes a **small, explicit interface**.
- does **not** directly reach into other components' internals.

Components communicate through the **central emulator context**, which acts as the system bus.

### The Emulator Context

At the center of the project is a single struct (defined in `gbemu.h`) that represents the entire Game Boy system. It contains all hardware components and wiring between them:

```C
typedef struct GameBoy {
    CPU cpu;
    PPU ppu;
    APU apu;
    Timer timer;
    Joypad joypad;
    Cartridge cart;

    u8          vram[0x2000];
    u8          wram[0x2000];
    u8          oam[0xA0];
    u8          hram[0x7F];

    IORegisters io;
    u8          ie_register;

    u8          serial_data;
    u16         serial_cycles;

    u64         cycles;
    bool        running;
} GameBoy
```

Every subsystem recieves a pointer to the emulator context (or the specific subcomponents if needed).

<details>
    <summary><h2>Project Structure</h2></summary>

```BareDMG/
├── CMakeLists.txt     # Build configuration
│
├── docs/              # Reference materials and technical documentation
|
├── external/          # Third-party libraries
│
├── include/
│   ├── baredmg.h      # Interface between frontend and emulator core
|
│   ├── gbemu.h        # "Motherboard" that wires components together
│   │
│   ├── core/          # Hardware component headers
│   │   ├── bus.h           # Memory mapping and address routing
│   │   ├── ppu.h           # Video timing and rendering
│   │   ├── apu.h           # Audio timing and sample generation
│   │   ├── timer.h         # DIV/TIMA timer logic
│   │   ├── joypad.h        # Input state
│   │   ├── cartridge.h     # ROM loading and metadata
│   │   ├── mbc.h           # Memory Bank Controller implementations
│   │   └── utils.h         # Bit operations, masks, and common helpers
│   │   └── cpu/
|   │       └── cpu.h       # LR35902 CPU (registers & helper func)
|   │       └── cpu_exec.h  # Declaration of CPU instructions (func)
│   │
│   └── frontend/
│       └── frontend.h      # Frontend abstraction
│
├── src/
│   └── main.c              # Parsing the CLI arguments
│   │
│   ├── core/
│   │   ├── gbemu.c         # System initialization and main loop
│   │   ├── cpu/
│   │   │   ├── cpu.c           # CPU state management
│   │   │   ├── cpu_decode.c    # Instruction decoding
│   │   │   ├── cpu_exec.c      # Implementation of each instruction
│   │   │   └── cpu_tables.c    # Opcode lookup tables
│   │   |
│   │   ├── bus.c          # Address decoding and memory routing
│   │   ├── ppu.c          # PPU timing and rendering logic
│   │   ├── apu.c          # APU channels and audio output
│   │   ├── timer.c        # Timer register emulation
│   │   ├── joypad.c       # Button state updates
│   │   ├── cartridge.c    # ROM parsing and cartridge setup
│   │   ├── mbc.c          # Bank switching implementations
│   │   └── utils.c        # Helper function implementations
│   │
│   └── frontend/          # Platform and UI code
│       ├── headless.c         # No UI, useful for testing
│       └── sdl_frontend.c     # SDL-based window, input, and audio
|
├── roms/                  # Test ROMs and game files (git ignored)
│
├── tests/                 # Unit tests and ROM validation
│
├── LICENSE
├── CONTRIBUTING.md
└── README.md
```

</details>


## Building & Running

### Required Tools & Libraries

- `gcc` C Compiler
- `CMake` Build system
- `git` Version control

- `SDL2` Graphics, input and audio
- `Check` Unit testing framework

- `gdb` Debugger (optional)
- `valgrind` (optional)

#### Installing required tools & libraries:

```zsh
# Debian & Debian based:
sudo apt install build-essential cmake git libsdl2-dev gdb valgrind

## Arch & Arch based
sudo pacman -S base-devel cmake git sdl2 gdb valgrind
```

#### Cloning & Building

```zsh
git clone https://github.com/LilSuperUser/BareDMG.git
cd BareDMG
mkdir build && cd build
cmake ..
make
```

#### Running & Options

```zsh
Usage: ./baredmg [options] <path_to_rom>

Modes (mutually exclusive):
  -i               Info mode (default): load ROM, print header info, then exit
  -s <num>         Step mode: execute exactly <num> CPU instructions
  -r               Run mode: execute instructions until timeout or HALT

Other options:
  -d               Debug mode (verbose CPU state output)
  -h               Show this help message
```

<details>
    <summary><h2>Testing</h2></summary>

The emulator uses two types of testing:

### 1. Unit Tests (`Check` Framework)

`check` is a unit testing framework for C that lets you write and run tests for individual components.

Tests are located in tests/ and test individual functions and components in isolation:

- `test_utils.c` - tests bit manipulation helpers
- `test_cartridge.c` - tests ROM parsing
- `test_cpu.c` - tests CPU instruction execution
- `test_mmu.c` - tests memory routing logic

Run unit tests:

```zsh
mkdir build && cd build
cmake ..

make test
# or
ctest
```

### 2. Integration Tests (Test ROMs)

**Test ROMs** are actual Game Boy programs that validate hardware behavior by running on the emulator and **reporting PASS/FAIL results**.

- [Blargg's test ROMs](https://github.com/retrio/gb-test-roms)
    - `cpu_instrs.gb` - Validates all CPU instructions
    - `instr_timing.gb` - Tests instruction cycle accuracy
    - `mem_timing.gb` - Verifies memory access timing
- [Mooneye Test Suite](https://github.com/Gekkio/mooneye-test-suite) - Additional hardware accuracy tests
- [dmg-acid2](https://github.com/mattcurrie/dmg-acid2) - PPU rendering validation

Place test ROM in `roms/tests/` and run them through the emulator to verify correctness.

</details>

## Resources

- [Pan Docs](https://gbdev.io/pandocs/)
- [Game Boy Complete Technical Reference](https://gekkio.fi/files/gb-docs/gbctr.pdf)
- [Cycle-Accurate Game Boy Docs](https://raw.githubusercontent.com/rockytriton/LLD_gbemu/main/docs/The%20Cycle-Accurate%20Game%20Boy%20Docs.pdf)
- [Opcode Reference](https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html)
- [Game Boy Programming Manual](https://archive.org/details/GameBoyProgManVer1.1/mode/2up)

## Contributing

Want to help improve BareDMG? Check out [CONTRIBUTING.md](./CONTRIBUTING.md) for instructions on contributing code, tests, and documentation.

## License

This project is licensed under the GPL v3 License. You are free to use, modify, and distribute this software under the terms of the [GPL v3 license](./LICENSE)
