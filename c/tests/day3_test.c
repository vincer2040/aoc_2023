#include "../src/aoc.h"
#include <check.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

START_TEST(part_one) {
    const char* input = "467..114..\n\
...*......\n\
..35..633.\n\
......#...\n\
617*......\n\
.....+.58.\n\
..592.....\n\
......755.\n\
...$.*....\n\
.664.598..";
    int res = day3p1(input, strlen(input));
    ck_assert_int_eq(res, 4361);
}
END_TEST

START_TEST(part_two) {
    const char* input = "467..114..\n\
...*......\n\
..35..633.\n\
......#...\n\
617*......\n\
.....+.58.\n\
..592.....\n\
......755.\n\
...$.*....\n\
.664.598..";
    int res = day3p2(input, strlen(input));
    ck_assert_int_eq(res, 467835);
}
END_TEST

Suite* suite(void) {
    Suite* s;
    TCase* core;
    s = suite_create("day three");
    core = tcase_create("Core");
    tcase_add_test(core, part_one);
    tcase_add_test(core, part_two);
    suite_add_tcase(s, core);
    return s;
}

int main(void) {
    Suite* s;
    SRunner* sr;
    s = suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    int num_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
