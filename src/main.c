#include <gbemu.h>
#include <core/cartridge.h>
#include <stdio.h>
#include <stdlib.h>

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

    const char *rom_path = argv[1];

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

    // Clean up
    cart_unload(&gb.cart);

    puts("\nExiting...\n");
    return 0;
}
