# Core emulator library

# List all core source files
set(CORE_SOURCES
    utils.c
    cartridge.c
    bus.c
    gbemu.c
    cpu/cpu.c
    cpu/cpu_tables.c
    cpu/cpu_exec.c
    # NOTE: We'll add more as they are written
    # cpu/cpu.c
    # cpu/cpu_decode.c
    # cpu/cpu_exec.c
    # cpu/cpu_tables.c
    # ppu.c
    # apu.c
    # timer.c
    # joypad.c
    # mbc.c
)

# Create static library
add_library(gbcore STATIC ${CORE_SOURCES})

# Make headers available
target_include_directories(gbcore PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Link math library (We'll prolly need this later)
target_link_libraries(gbcore m)
