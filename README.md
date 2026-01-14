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
    MMU mmu;

    uint64_t cycles;
    bool running;
}
```
Every subsystem recieves a pointer to the emulator context (or the specific subcomponents if needed).

<details>
    <summary><h2>Project Structure</h2></summary>

```
BareDMG/
├── CMakeLists.txt
│   # Build configuration
│
├── docs/
│   # Reference materials and technical documentation
│   ├── gbctr.pdf
│   └── The-Cycle-Accurate-GameBoy-Docs.pdf
│
├── external/
│   # Third-party libraries
│
├── include/
│   ├── baredmg.h
│   │   # Public API - interface between frontend and emulator core
│   │
│   ├── gbemu.h
│   │   # Emulator context - the "motherboard" that wires components together
│   │
│   ├── core/
│   │   # Hardware component headers
│   │   ├── cpu.h           # LR35902 CPU state and execution
│   │   ├── bus.h           # Memory mapping and address routing
│   │   ├── ppu.h           # Video timing and rendering
│   │   ├── apu.h           # Audio timing and sample generation
│   │   ├── timer.h         # DIV/TIMA timer logic
│   │   ├── joypad.h        # Input state
│   │   ├── cartridge.h     # ROM loading and metadata
│   │   ├── mbc.h           # Memory Bank Controller implementations
│   │   └── utils.h         # Bit operations, masks, and common helpers
│   │
│   └── frontend/
│       └── frontend.h
│           # Frontend abstraction (SDL, headless, debugger)
│
├── src/
│   ├── core/
│   │   # Emulator core - the actual Game Boy implementation
│   │   ├── gbemu.c        # System initialization and main loop
│   │   ├── bus.c          # Address decoding and memory routing
│   │   ├── cpu/
│   │   │   ├── cpu.c          # CPU state management
│   │   │   ├── cpu_decode.c   # Instruction decoding
│   │   │   ├── cpu_exec.c     # Instruction execution
│   │   │   └── cpu_tables.c   # Opcode lookup tables
│   │   ├── ppu.c          # PPU timing and rendering logic
│   │   ├── apu.c          # APU channels and audio output
│   │   ├── timer.c        # Timer register emulation
│   │   ├── joypad.c       # Button state updates
│   │   ├── cartridge.c    # ROM parsing and cartridge setup
│   │   ├── mbc.c          # Bank switching implementations
│   │   └── utils.c        # Helper function implementations
│   │
│   └── frontend/
│       # Platform and UI code - isolated from core emulation
│       ├── headless.c     # No UI, useful for testing
│       └── sdl_frontend.c # SDL-based window, input, and audio
│
├── roms/
│   # Test ROMs and game files (gitignored)
│
├── tests/
│   # Unit tests and ROM validation
│
├── LICENSE
├── CONTRIBUTING.md
└── README.md
```

</details>


<details>
    <summary><h2>Build Order</h2></summary>

The emulator will be built incrementally, implementing and testing each component before moving to the next.

### 1. **Foundation (Utils & Cartridges)**
- Implement bit manipulation utilities
- ROM file loading and header parsing
- Basic **MBC1** support

### 2. **CPU Core**
- Register implementation
- Instruction decoding and execution
- Interrupt handling
- Validate with **Blargg's CPU test ROMs**

### 3. **Memory System**
- MMU address routing
- Memory-mapped I/O
- Bank switching logic

### 4. **Timers & Joypad**
- `DIV` and `TIMA` registers
- Input state management

### 5. **PPU (Graphics)**
- LCD timing and modes
- Background rendering
- Sprite (OBJ) rendering
- Window layer

### 6. **APU (Sounds)**
- Sound channels (pulse, wave, noise)
- Audio mixing and output

Each phase will be tested before moving forward. The emulator should remain in a working state at each step.

</details>


## Building & Running

<details>
      <summary><h3>Required Tools & Libraries</h3></summary>

- `gcc` C Compiler
- `CMake` Build system
- `git` Version control

- `SDL2` Graphics, input and audio
- `Check` Unit testing framework

- `gdb` Debugger (optional)
- `valgrind` (optional)

</details>

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

#### Running
```zsh
./baredmg path/to/rom.gb
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
