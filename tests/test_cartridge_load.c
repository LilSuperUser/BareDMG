// tests/test_cartridge_load.c
// Temporary test file to test the functionality of cartridge loading
// TODO: Need to write a proper test suite for cartridge handling
#include <stdio.h>
#include "core/cartridge.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <rom_file.gb>\n", argv[0]);
        return 1;
    }

    Cartridge cart = {0};

    printf("Loading ROM: %s\n\n", argv[1]);

    int result = cart_load(&cart, argv[1]);

    if (result != 0) {
        printf("Failed to load ROM! Error code: %d\n", result);
        return 1;
    }

    printf("ROM loaded successfully!\n");
    printf("File size: %zu bytes\n\n", cart.rom_size);

    cart_print_header(&cart.header);

    cart_unload(&cart);
    printf("\nCartridge unloaded.\n");

    return 0;
}
