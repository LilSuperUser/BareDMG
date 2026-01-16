// tests/test_cartridge.c
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <core/cartridge.h>

// ============================================================================
// Helper Functions Tests
// ============================================================================

START_TEST(test_get_ram_size_no_ram) {
    ck_assert_uint_eq(get_ram_size(0x00), 0);
}
END_TEST

START_TEST(test_get_ram_size_2kb) {
    ck_assert_uint_eq(get_ram_size(0x01), 2 * 1024);
}
END_TEST

START_TEST(test_get_ram_size_8kb) {
    ck_assert_uint_eq(get_ram_size(0x02), 8 * 1024);
}
END_TEST

START_TEST(test_get_ram_size_32kb) {
    ck_assert_uint_eq(get_ram_size(0x03), 32 * 1024);
}
END_TEST

START_TEST(test_get_ram_size_128kb) {
    ck_assert_uint_eq(get_ram_size(0x04), 128 * 1024);
}
END_TEST

START_TEST(test_get_ram_size_64kb) {
    ck_assert_uint_eq(get_ram_size(0x05), 64 * 1024);
}
END_TEST

START_TEST(test_get_rom_size_32kb) {
    ck_assert_uint_eq(get_rom_size(0x00), 32 * 1024);
}
END_TEST

START_TEST(test_get_rom_size_64kb) {
    ck_assert_uint_eq(get_rom_size(0x01), 64 * 1024);
}
END_TEST

START_TEST(test_get_rom_size_128kb) {
    ck_assert_uint_eq(get_rom_size(0x02), 128 * 1024);
}
END_TEST

START_TEST(test_get_rom_size_1mb) {
    ck_assert_uint_eq(get_rom_size(0x05), 1024 * 1024);
}
END_TEST

START_TEST(test_get_rom_size_8mb) {
    ck_assert_uint_eq(get_rom_size(0x08), 8 * 1024 * 1024);
}
END_TEST

// ============================================================================
// Cartridge Type Name Tests
// ============================================================================

START_TEST(test_cart_type_rom_only) {
    ck_assert_str_eq(get_cart_type_name(0x00), "ROM ONLY");
}
END_TEST

START_TEST(test_cart_type_mbc1) {
    ck_assert_str_eq(get_cart_type_name(0x01), "MBC1");
}
END_TEST

START_TEST(test_cart_type_mbc1_ram) {
    ck_assert_str_eq(get_cart_type_name(0x02), "MBC1+RAM");
}
END_TEST

START_TEST(test_cart_type_mbc1_ram_battery) {
    ck_assert_str_eq(get_cart_type_name(0x03), "MBC1+RAM+BATTERY");
}
END_TEST

START_TEST(test_cart_type_mbc3) {
    ck_assert_str_eq(get_cart_type_name(0x11), "MBC3");
}
END_TEST

START_TEST(test_cart_type_mbc5) {
    ck_assert_str_eq(get_cart_type_name(0x19), "MBC5");
}
END_TEST

START_TEST(test_cart_type_unknown) {
    ck_assert_str_eq(get_cart_type_name(0xAB), "UNKNOWN");
}
END_TEST

// ============================================================================
// Publisher Name Tests
// ============================================================================

START_TEST(test_publisher_old_nintendo) {
    // Old code 0x01 = Nintendo
    ck_assert_str_eq(get_publisher_name(0x01, true), "Nintendo");
}
END_TEST

START_TEST(test_publisher_old_capcom) {
    // Old code 0x08 = Capcom
    ck_assert_str_eq(get_publisher_name(0x08, true), "Capcom");
}
END_TEST

START_TEST(test_publisher_new_nintendo) {
    // New code "01" = 0x3031 = Nintendo
    ck_assert_str_eq(get_publisher_name(0x3031, false), "Nintendo");
}
END_TEST

START_TEST(test_publisher_new_ocean) {
    // New code "33" = 0x3333 = Ocean/Acclaim
    ck_assert_str_eq(get_publisher_name(0x3333, false), "Ocean/Acclaim");
}
END_TEST

START_TEST(test_publisher_old_unknown) {
    ck_assert_str_eq(get_publisher_name(0xAB, true), "Unknown");
}
END_TEST

START_TEST(test_publisher_new_unknown) {
    ck_assert_str_eq(get_publisher_name(0xFFFF, false), "Unknown");
}
END_TEST

// ============================================================================
// Header Parsing Tests
// ============================================================================

START_TEST(test_parse_header_old_license) {
    RawRomHeader raw    = {0};
    CartHeader   parsed = {0};

    // Setup raw header with old license code
    memcpy(raw.title, "TEST GAME", strlen("TEST GAME")+1);
    raw.old_lic_code = 0x01; // Nintendo (old)
    raw.type         = 0x00; // ROM ONLY
    raw.rom_size     = 0x00; // 32 KB
    raw.ram_size     = 0x00; // No RAM
    raw.version      = 0x01;
    raw.sgb_flag     = 0x00; // No SGB support

    parse_header(&raw, &parsed);

    ck_assert_str_eq(parsed.title, "TEST GAME");
    ck_assert_uint_eq(parsed.lic_code, 0x01);
    ck_assert_uint_eq(parsed.cart_type, 0x00);
    ck_assert_uint_eq(parsed.rom_size_code, 0x00);
    ck_assert_uint_eq(parsed.ram_size_code, 0x00);
    ck_assert_uint_eq(parsed.version, 0x01);
    ck_assert(!parsed.sgb_supported);
    ck_assert(!parsed.cgb_supported);
}
END_TEST

START_TEST(test_parse_header_new_license) {
    RawRomHeader raw    = {0};
    CartHeader   parsed = {0};

    // Setup raw header with new license code
    memcpy(raw.title, "POKEMON RED", strlen("POKEMON RED")+1);
    raw.old_lic_code = 0x33; // Magic value: use new license
    raw.new_lic_hi   = 0x30; // '0'
    raw.new_lic_lo   = 0x31; // '1'
    raw.type         = 0x13; // MBC3+RAM+BATTERY
    raw.rom_size     = 0x05; // 1 MB
    raw.ram_size     = 0x03; // 32 KB
    raw.version      = 0x00;
    raw.sgb_flag     = 0x03; // SGB support

    parse_header(&raw, &parsed);

    ck_assert_str_eq(parsed.title, "POKEMON RED");
    ck_assert_uint_eq(parsed.lic_code, 0x3031); // ASCII "01"
    ck_assert_uint_eq(parsed.cart_type, 0x13);
    ck_assert_uint_eq(parsed.rom_size_code, 0x05);
    ck_assert_uint_eq(parsed.ram_size_code, 0x03);
    ck_assert_uint_eq(parsed.version, 0x00);
    ck_assert(parsed.sgb_supported);
    ck_assert(!parsed.cgb_supported);
}
END_TEST

START_TEST(test_parse_header_cgb_flag) {
    RawRomHeader raw    = {0};
    CartHeader   parsed = {0};

    // Setup header with CGB flag
    // Fill entire title array (raw header has no null terminators)
    memset(raw.title, 'A', 15); // Fill first 15 bytes with 'A'
    raw.title[15]    = 0x80;    // CGB enhanced flag at byte 15
    raw.old_lic_code = 0x01;
    raw.type         = 0x00;
    raw.rom_size     = 0x00;
    raw.ram_size     = 0x00;
    raw.version      = 0x01;
    raw.sgb_flag     = 0x00;

    parse_header(&raw, &parsed);

    ck_assert(parsed.cgb_supported);
    // When CGB flag is present, title is truncated to 15 chars
    ck_assert_uint_eq(parsed.title[15], '\0');  // Null at position 15
    ck_assert_int_eq(strlen(parsed.title), 15); // Length is 15
}
END_TEST

START_TEST(test_parse_header_cgb_only_flag) {
    RawRomHeader raw    = {0};
    CartHeader   parsed = {0};

    // Setup header with CGB-only flag
    memset(raw.title, 'B', 15); // Fill first 15 bytes with 'B'
    raw.title[15]    = 0xC0;    // CGB only (at byte 15)
    raw.old_lic_code = 0x01;
    raw.type         = 0x00;
    raw.rom_size     = 0x00;
    raw.ram_size     = 0x00;
    raw.version      = 0x01;
    raw.sgb_flag     = 0x00;

    parse_header(&raw, &parsed);

    ck_assert(parsed.cgb_supported);
}
END_TEST

// ============================================================================
// Header Checksum Tests
// ============================================================================

START_TEST(test_header_checksum_valid) {
    // Create a minimal valid ROM with correct checksum
    Cartridge cart   = {0};
    cart.rom_size    = 0x8000; // 32 KB minimum
    cart.rom         = calloc(1, cart.rom_size);

    // Fill header area with known values
    // Title: "TEST"
    cart.rom[0x0134] = 'T';
    cart.rom[0x0135] = 'E';
    cart.rom[0x0136] = 'S';
    cart.rom[0x0137] = 'T';

    // Calculate correct checksum for this header
    u8 checksum      = 0;
    for (u16 addr = 0x0134; addr <= 0x014C; addr++) {
        checksum = checksum - cart.rom[addr] - 1;
    }
    cart.rom[0x014D] = checksum;

    ck_assert(cart_verify_header_checksum(&cart));

    free(cart.rom);
}
END_TEST

START_TEST(test_header_checksum_invalid) {
    // Create ROM with incorrect checksum
    Cartridge cart   = {0};
    cart.rom_size    = 0x8000;
    cart.rom         = calloc(1, cart.rom_size);

    // Fill header
    cart.rom[0x0134] = 'T';
    cart.rom[0x0135] = 'E';
    cart.rom[0x0136] = 'S';
    cart.rom[0x0137] = 'T';

    // Set WRONG checksum
    cart.rom[0x014D] = 0xFF;

    ck_assert(!cart_verify_header_checksum(&cart));

    free(cart.rom);
}
END_TEST

// ============================================================================
// Test Suite Setup
// ============================================================================

Suite *cartridge_suite(void) {
    Suite *s;
    TCase *tc_ram_size, *tc_rom_size, *tc_cart_type, *tc_publisher;
    TCase *tc_parse, *tc_checksum;

    s           = suite_create("Cartridge");

    // RAM size tests
    tc_ram_size = tcase_create("RAM Size Decoding");
    tcase_add_test(tc_ram_size, test_get_ram_size_no_ram);
    tcase_add_test(tc_ram_size, test_get_ram_size_2kb);
    tcase_add_test(tc_ram_size, test_get_ram_size_8kb);
    tcase_add_test(tc_ram_size, test_get_ram_size_32kb);
    tcase_add_test(tc_ram_size, test_get_ram_size_128kb);
    tcase_add_test(tc_ram_size, test_get_ram_size_64kb);
    suite_add_tcase(s, tc_ram_size);

    // ROM size tests
    tc_rom_size = tcase_create("ROM Size Decoding");
    tcase_add_test(tc_rom_size, test_get_rom_size_32kb);
    tcase_add_test(tc_rom_size, test_get_rom_size_64kb);
    tcase_add_test(tc_rom_size, test_get_rom_size_128kb);
    tcase_add_test(tc_rom_size, test_get_rom_size_1mb);
    tcase_add_test(tc_rom_size, test_get_rom_size_8mb);
    suite_add_tcase(s, tc_rom_size);

    // Cartridge type tests
    tc_cart_type = tcase_create("Cartridge Type Names");
    tcase_add_test(tc_cart_type, test_cart_type_rom_only);
    tcase_add_test(tc_cart_type, test_cart_type_mbc1);
    tcase_add_test(tc_cart_type, test_cart_type_mbc1_ram);
    tcase_add_test(tc_cart_type, test_cart_type_mbc1_ram_battery);
    tcase_add_test(tc_cart_type, test_cart_type_mbc3);
    tcase_add_test(tc_cart_type, test_cart_type_mbc5);
    tcase_add_test(tc_cart_type, test_cart_type_unknown);
    suite_add_tcase(s, tc_cart_type);

    // Publisher tests
    tc_publisher = tcase_create("Publisher Names");
    tcase_add_test(tc_publisher, test_publisher_old_nintendo);
    tcase_add_test(tc_publisher, test_publisher_old_capcom);
    tcase_add_test(tc_publisher, test_publisher_new_nintendo);
    tcase_add_test(tc_publisher, test_publisher_new_ocean);
    tcase_add_test(tc_publisher, test_publisher_old_unknown);
    tcase_add_test(tc_publisher, test_publisher_new_unknown);
    suite_add_tcase(s, tc_publisher);

    // Header parsing tests
    tc_parse = tcase_create("Header Parsing");
    tcase_add_test(tc_parse, test_parse_header_old_license);
    tcase_add_test(tc_parse, test_parse_header_new_license);
    tcase_add_test(tc_parse, test_parse_header_cgb_flag);
    tcase_add_test(tc_parse, test_parse_header_cgb_only_flag);
    suite_add_tcase(s, tc_parse);

    // Checksum tests
    tc_checksum = tcase_create("Header Checksum");
    tcase_add_test(tc_checksum, test_header_checksum_valid);
    tcase_add_test(tc_checksum, test_header_checksum_invalid);
    suite_add_tcase(s, tc_checksum);

    return s;
}

int main(void) {
    int      number_failed;
    Suite   *s;
    SRunner *sr;

    s  = cartridge_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}
