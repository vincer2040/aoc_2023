#include "../src/aoc.h"
#include <check.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

START_TEST(part_one) {
    const char* input = "\
1abc2\n\
pqr3stu8vwx\n\
a1b2c3d4e5f\n\
treb7uchet";
    size_t input_len = strlen(input);
    int res = day1p1(input, input_len);
    ck_assert_int_eq(res, 142);
}
END_TEST

START_TEST(part_two) {
    const char* input = "\
two1nine\n\
eightwothree\n\
abcone2threexyz\n\
xtwone3four\n\
4nineeightseven2\n\
zoneight234\n\
7pqrstsixteen";
    size_t input_len = strlen(input);
    int res = day1p2(input, input_len);
    ck_assert_int_eq(res, 281);
}
END_TEST

Suite* suite(void) {
    Suite* s;
    TCase* tc_core;
    s = suite_create("day one");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, part_one);
    tcase_add_test(tc_core, part_two);
    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    int number_failed;
    Suite* s;
    SRunner* sr;
    s = suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
