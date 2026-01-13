// tests/test_utils.c
#include <check.h>
#include <core/utils.h>

// ==================================
// Bit Manipulation Tests
// ==================================

START_TEST(test_bit_macro) {
    ck_assert_uint_eq(BIT(0), 0x01);
    ck_assert_uint_eq(BIT(3), 0x08);
    ck_assert_uint_eq(BIT(7), 0x80);
}
END_TEST

START_TEST(test_check_bit) {
    u8 val = 0b10101010;
    ck_assert_int_eq(CHECK_BIT(val, 0), 0);
    ck_assert_int_eq(CHECK_BIT(val, 1), 1);
    ck_assert_int_eq(CHECK_BIT(val, 2), 0);
    ck_assert_int_eq(CHECK_BIT(val, 3), 1);
}
END_TEST

START_TEST(test_set_bit) {
    u8 val = 0x00;
    val    = SET_BIT(val, 3);
    ck_assert_uint_eq(val, 0x08);

    val = SET_BIT(val, 7);
    ck_assert_uint_eq(val, 0x88);
}
END_TEST

START_TEST(test_clear_bit) {
    u8 val = 0xFF;
    val    = CLEAR_BIT(val, 3);
    ck_assert_uint_eq(val, 0xF7);

    val = CLEAR_BIT(val, 0);
    ck_assert_uint_eq(val, 0xF6);
}
END_TEST

START_TEST(test_toggle_bit) {
    u8 val = 0x00;
    val    = TOGGLE_BIT(val, 2);
    ck_assert_uint_eq(val, 0x04);

    val = TOGGLE_BIT(val, 2);
    ck_assert_uint_eq(val, 0x00);
}
END_TEST

START_TEST(test_get_bits) {
    u8 val = 0b11010110;

    // Get lower 4 bits
    ck_assert_uint_eq(GET_BITS(val, 0, 4), 0b0110);

    // Get upper 4 bits
    ck_assert_uint_eq(GET_BITS(val, 4, 4), 0b1101);

    // Get middle 3 bits (bits 2-4)
    ck_assert_uint_eq(GET_BITS(val, 2, 3), 0b101);
}
END_TEST

START_TEST(test_set_bits) {
    u8 val = 0b11110000;

    // Set lower 4 bits to 0b1010
    val    = SET_BITS(val, 0, 4, 0b1010);
    ck_assert_uint_eq(val, 0b11111010);

    // Set upper 4 bits to 0b0101
    val = SET_BITS(val, 4, 4, 0b0101);
    ck_assert_uint_eq(val, 0b01011010);
}
END_TEST

// ==================================
// 16-bit Register Operation Tests
// ==================================

START_TEST(test_make_u16) {
    u8  high   = 0xAB;
    u8  low    = 0xCD;
    u16 result = MAKE_U16(high, low);
    ck_assert_uint_eq(result, 0xABCD);
}
END_TEST

START_TEST(test_get_high_byte) {
    u16 val = 0x1234;
    ck_assert_uint_eq(GET_HIGH_BYTE(val), 0x12);
}
END_TEST

START_TEST(test_get_low_byte) {
    u16 val = 0x1234;
    ck_assert_uint_eq(GET_LOW_BYTE(val), 0x34);
}
END_TEST

START_TEST(test_swap_bytes) {
    u16 val     = 0x1234;
    u16 swapped = swap_bytes(val);
    ck_assert_uint_eq(swapped, 0x3412);
}
END_TEST

// ==================================
// 8-bit Carry/Half-Carry Tests
// ==================================

START_TEST(test_check_half_carry_add_no_carry) {
    // 0x03 + 0x04 = 0x07, no half-carry (bit 3->4)
    ck_assert(!check_half_carry_add(0x03, 0x04));
}
END_TEST

START_TEST(test_check_half_carry_add_with_carry) {
    // 0x0F + 0x01 = 0x10, half-carry occurs (lower nibble overflows)
    ck_assert(check_half_carry_add(0x0F, 0x01));

    // 0x08 + 0x08 = 0x10, half-carry
    ck_assert(check_half_carry_add(0x08, 0x08));
}
END_TEST

START_TEST(test_check_carry_add_no_carry) {
    // 0x7F + 0x01 = 0x80, no carry
    ck_assert(!check_carry_add(0x7F, 0x01));
}
END_TEST

START_TEST(test_check_carry_add_with_carry) {
    // 0xFF + 0x01 = 0x100, carry occurs
    ck_assert(check_carry_add(0xFF, 0x01));

    // 0x80 + 0x80 = 0x100, carry occurs
    ck_assert(check_carry_add(0x80, 0x80));
}
END_TEST

START_TEST(test_check_half_carry_sub_no_carry) {
    // 0x0F - 0x01 = 0x0E, no half-carry (0xF >= 0x1 in lower nibble)
    ck_assert(!check_half_carry_sub(0x0F, 0x01));

    // 0x20 - 0x10 = 0x10, no half-carry (0x0 >= 0x0 in lower nibble)
    ck_assert(!check_half_carry_sub(0x20, 0x10));
}
END_TEST

START_TEST(test_check_half_carry_sub_with_carry) {
    // 0x10 - 0x11 requires borrow from bit 4
    ck_assert(check_half_carry_sub(0x10, 0x11));

    // 0x00 - 0x01 requires borrow
    ck_assert(check_half_carry_sub(0x00, 0x01));
}
END_TEST

START_TEST(test_check_carry_sub_no_carry) {
    // 0x10 - 0x01 = 0x0F, no borrow needed
    ck_assert(!check_carry_sub(0x10, 0x01));
}
END_TEST

START_TEST(test_check_carry_sub_with_carry) {
    // 0x00 - 0x01 requires borrow (underflow)
    ck_assert(check_carry_sub(0x00, 0x01));

    // 0x50 - 0x60 requires borrow
    ck_assert(check_carry_sub(0x50, 0x60));
}
END_TEST

// ==================================
// 16-bit Carry/Half-Carry Tests
// ==================================

START_TEST(test_check_half_carry_add_u16_no_carry) {
    // No half-carry from bit 11->12
    ck_assert(!check_half_carry_add_u16(0x0700, 0x0400));
}
END_TEST

START_TEST(test_check_half_carry_add_u16_with_carry) {
    // 0x0FFF + 0x0001 = 0x1000, half-carry from bit 11->12
    ck_assert(check_half_carry_add_u16(0x0FFF, 0x0001));

    // 0x0800 + 0x0800 = 0x1000, half-carry
    ck_assert(check_half_carry_add_u16(0x0800, 0x0800));
}
END_TEST

START_TEST(test_check_carry_add_u16_no_carry) {
    // 0x7FFF + 0x0001 = 0x8000, no carry
    ck_assert(!check_carry_add_u16(0x7FFF, 0x0001));
}
END_TEST

START_TEST(test_check_carry_add_u16_with_carry) {
    // 0xFFFF + 0x0001 = 0x10000, carry occurs
    ck_assert(check_carry_add_u16(0xFFFF, 0x0001));

    // 0x8000 + 0x8000 = 0x10000, carry
    ck_assert(check_carry_add_u16(0x8000, 0x8000));
}
END_TEST

// ==================================
// Sign Extension Tests
// ==================================

START_TEST(test_sign_extend_positive) {
    // 0x7F is positive (bit 7 = 0), should remain 0x007F
    i16 result = sign_extend_i8(0x7F);
    ck_assert_int_eq(result, 0x007F);
}
END_TEST

START_TEST(test_sign_extend_negative) {
    // 0x80 is negative (bit 7 = 1), should become 0xFF80 (-128)
    i16 result = sign_extend_i8(0x80);
    ck_assert_int_eq(result, (i16)0xFF80);
    ck_assert_int_eq(result, -128);

    // 0xFF is -1, should become 0xFFFF (-1)
    result = sign_extend_i8(0xFF);
    ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(test_sign_extend_zero) {
    i16 result = sign_extend_i8(0x00);
    ck_assert_int_eq(result, 0);
}
END_TEST

// ==================================
// Test Suite Setup
// ==================================

Suite *utils_suite(void) {
    Suite *s;
    TCase *tc_bits, *tc_u16, *tc_carry8, *tc_carry16, *tc_sign;

    s       = suite_create("Utils");

    // Bit manipulation tests
    tc_bits = tcase_create("Bit Operations");
    tcase_add_test(tc_bits, test_bit_macro);
    tcase_add_test(tc_bits, test_check_bit);
    tcase_add_test(tc_bits, test_set_bit);
    tcase_add_test(tc_bits, test_clear_bit);
    tcase_add_test(tc_bits, test_toggle_bit);
    tcase_add_test(tc_bits, test_get_bits);
    tcase_add_test(tc_bits, test_set_bits);
    suite_add_tcase(s, tc_bits);

    // 16-bit register tests
    tc_u16 = tcase_create("16-bit Operations");
    tcase_add_test(tc_u16, test_make_u16);
    tcase_add_test(tc_u16, test_get_high_byte);
    tcase_add_test(tc_u16, test_get_low_byte);
    tcase_add_test(tc_u16, test_swap_bytes);
    suite_add_tcase(s, tc_u16);

    // 8-bit carry tests
    tc_carry8 = tcase_create("8-bit Carry/Half-Carry");
    tcase_add_test(tc_carry8, test_check_half_carry_add_no_carry);
    tcase_add_test(tc_carry8, test_check_half_carry_add_with_carry);
    tcase_add_test(tc_carry8, test_check_carry_add_no_carry);
    tcase_add_test(tc_carry8, test_check_carry_add_with_carry);
    tcase_add_test(tc_carry8, test_check_half_carry_sub_no_carry);
    tcase_add_test(tc_carry8, test_check_half_carry_sub_with_carry);
    tcase_add_test(tc_carry8, test_check_carry_sub_no_carry);
    tcase_add_test(tc_carry8, test_check_carry_sub_with_carry);
    suite_add_tcase(s, tc_carry8);

    // 16-bit carry tests
    tc_carry16 = tcase_create("16-bit Carry/Half-Carry");
    tcase_add_test(tc_carry16, test_check_half_carry_add_u16_no_carry);
    tcase_add_test(tc_carry16, test_check_half_carry_add_u16_with_carry);
    tcase_add_test(tc_carry16, test_check_carry_add_u16_no_carry);
    tcase_add_test(tc_carry16, test_check_carry_add_u16_with_carry);
    suite_add_tcase(s, tc_carry16);

    // Sign extension tests
    tc_sign = tcase_create("Sign Extension");
    tcase_add_test(tc_sign, test_sign_extend_positive);
    tcase_add_test(tc_sign, test_sign_extend_negative);
    tcase_add_test(tc_sign, test_sign_extend_zero);
    suite_add_tcase(s, tc_sign);

    return s;
}

int main(void) {
    int      number_failed;
    Suite   *s;
    SRunner *sr;

    s  = utils_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}
