// tests/test_mmu.c
#include <check.h>
#include <gbemu.h>
#include <core/bus.h>
#include <stdlib.h>

// ============================================================================
// WRAM Tests
// ============================================================================

START_TEST(test_wram_read_write) {
    GameBoy gb = {0};
    gb_init(&gb);

    // Write to WRAM
    mmu_write(&gb, 0xC000, 0x42);
    mmu_write(&gb, 0xDFFF, 0x99);

    // Read back
    ck_assert_uint_eq(mmu_read(&gb, 0xC000), 0x42);
    ck_assert_uint_eq(mmu_read(&gb, 0xDFFF), 0x99);
}
END_TEST

START_TEST(test_wram_echo) {
    GameBoy gb = {0};
    gb_init(&gb);

    // Write to WRAM
    mmu_write(&gb, 0xC100, 0xAB);

    // Read from echo (0xE000 - 0xFDFF mirrors 0xC000 - 0xDDFF)
    ck_assert_uint_eq(mmu_read(&gb, 0xE100), 0xAB);

    // Write to echo
    mmu_write(&gb, 0xE200, 0xCD);

    // Read from WRAM
    ck_assert_uint_eq(mmu_read(&gb, 0xC200), 0xCD);
}
END_TEST

// ============================================================================
// HRAM Tests
// ============================================================================

START_TEST(test_hram_read_write) {
    GameBoy gb = {0};
    gb_init(&gb);

    // Write to HRAM
    mmu_write(&gb, 0xFF80, 0x11);
    mmu_write(&gb, 0xFFFE, 0x22);

    // Read back
    ck_assert_uint_eq(mmu_read(&gb, 0xFF80), 0x11);
    ck_assert_uint_eq(mmu_read(&gb, 0xFFFE), 0x22);
}
END_TEST

// ============================================================================
// ROM Tests
// ============================================================================

START_TEST(test_rom_read) {
    GameBoy gb = {0};
    gb_init(&gb);

    // Create fake ROM
    gb.cart.rom         = malloc(0x8000);
    gb.cart.rom_size    = 0x8000;

    gb.cart.rom[0x0100] = 0x3E; // LD A, n
    gb.cart.rom[0x0101] = 0x42;
    gb.cart.rom[0x4000] = 0xC9; // RET

    // Read from ROM
    ck_assert_uint_eq(mmu_read(&gb, 0x0100), 0x3E);
    ck_assert_uint_eq(mmu_read(&gb, 0x0101), 0x42);
    ck_assert_uint_eq(mmu_read(&gb, 0x4000), 0xC9);

    free(gb.cart.rom);
}
END_TEST

START_TEST(test_rom_write_ignored) {
    GameBoy gb = {0};
    gb_init(&gb);

    // Create fake ROM
    gb.cart.rom         = malloc(0x8000);
    gb.cart.rom_size    = 0x8000;
    gb.cart.rom[0x0100] = 0x00;

    // Try to write to ROM (should be ignored)
    mmu_write(&gb, 0x0100, 0xFF);

    // Value should not change
    ck_assert_uint_eq(mmu_read(&gb, 0x0100), 0x00);

    free(gb.cart.rom);
}
END_TEST

// ============================================================================
// Unusable Region Tests
// ============================================================================

START_TEST(test_unusable_region) {
    GameBoy gb = {0};
    gb_init(&gb);

    // Reads from 0xFEA0 - 0xFEFF should return 0x00
    ck_assert_uint_eq(mmu_read(&gb, 0xFEA0), 0x00);
    ck_assert_uint_eq(mmu_read(&gb, 0xFEFF), 0x00);

    // Writes should be ignored (no crash)
    mmu_write(&gb, 0xFEA0, 0xFF);
    ck_assert_uint_eq(mmu_read(&gb, 0xFEA0), 0x00);
}
END_TEST

// ============================================================================
// Interrupt Enable Register Tests
// ============================================================================

START_TEST(test_ie_register) {
    GameBoy gb = {0};
    gb_init(&gb);

    // Write to IE register
    mmu_write(&gb, 0xFFFF, 0x1F);

    // Read back
    ck_assert_uint_eq(mmu_read(&gb, 0xFFFF), 0x1F);
}
END_TEST

// ============================================================================
// Test Suite Setup
// ============================================================================

Suite *mmu_suite(void) {
    Suite *s;
    TCase *tc_wram, *tc_hram, *tc_rom, *tc_special;

    s       = suite_create("MMU");

    // WRAM tests
    tc_wram = tcase_create("Work RAM");
    tcase_add_test(tc_wram, test_wram_read_write);
    tcase_add_test(tc_wram, test_wram_echo);
    suite_add_tcase(s, tc_wram);

    // HRAM tests
    tc_hram = tcase_create("High RAM");
    tcase_add_test(tc_hram, test_hram_read_write);
    suite_add_tcase(s, tc_hram);

    // ROM tests
    tc_rom = tcase_create("ROM Access");
    tcase_add_test(tc_rom, test_rom_read);
    tcase_add_test(tc_rom, test_rom_write_ignored);
    suite_add_tcase(s, tc_rom);

    // Special regions
    tc_special = tcase_create("Special Regions");
    tcase_add_test(tc_special, test_unusable_region);
    tcase_add_test(tc_special, test_ie_register);
    suite_add_tcase(s, tc_special);

    return s;
}

int main(void) {
    int      number_failed;
    Suite   *s;
    SRunner *sr;

    s  = mmu_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}
