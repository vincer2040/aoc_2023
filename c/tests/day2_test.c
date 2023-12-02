#include "../src/aoc.h"
#include <check.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

START_TEST(part_one) {
    const char* input = "\
Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green\n\
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue\n\
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red\n\
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red\n\
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green";
    size_t input_len = strlen(input);
    int res = day2p1(input, input_len);
    ck_assert_int_eq(res, 8);
}
END_TEST

START_TEST(part_two) {
    const char* input = "\
Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green\n\
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue\n\
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red\n\
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red\n\
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green";
    size_t input_len = strlen(input);
    int res = day2p2(input, input_len);
    ck_assert_int_eq(res, 2286);
}
END_TEST

Suite* suite(void) {
    Suite* s;
    TCase* core;
    s = suite_create("day two");
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
