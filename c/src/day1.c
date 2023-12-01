#include "aoc.h"
#include <assert.h>
#include <ctype.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

int day1p1(const char* input, size_t input_len) {
    line_iter iter = line_iter_new(input, input_len);
    int res = 0;
    while (iter.cur) {
        size_t i, len = iter.cur_len;
        int num1 = -1;
        int num2 = -1;
        int num;
        for (i = 0; i < len; ++i) {
            char ch = iter.cur[i];
            if (isdigit(ch)) {
                if (num1 == -1) {
                    num1 = ch - '0';
                }
                num2 = ch - '0';
            }
        }
        num = (num1 * 10) + num2;
        res += num;
        line_iter_next(&iter);
    }
    return res;
}

typedef struct {
    const char* str;
    size_t str_len;
    int num;
} lookup;

lookup lookups[] = {
    {"one", 3, 1},   {"two", 3, 2},   {"three", 5, 3},
    {"four", 4, 4},  {"five", 4, 5},  {"six", 3, 6},
    {"seven", 5, 7}, {"eight", 5, 8}, {"nine", 4, 9},
};

size_t lookups_len = sizeof lookups / sizeof lookups[0];

int lookup_str(char* str) {
    size_t i;
    for (i = 0; i < lookups_len; ++i) {
        if (strncmp(lookups[i].str, str, lookups[i].str_len) == 0) {
            return lookups[i].num;
        }
    }
    return -1;
}

int day1p2(const char* input, size_t input_len) {
    line_iter iter = line_iter_new(input, input_len);
    int res = 0;
    while (iter.cur) {
        size_t i, len = iter.cur_len;
        int left = -1, right = -1;
        for (i = 0; i < len; ++i) {
            char* slice = iter.cur + i;
            int lookup = lookup_str(slice);
            if (lookup != -1) {
                if (left == -1) {
                    left = lookup;
                    right = lookup;
                }
                right = lookup;
            } else {
                if (isdigit(iter.cur[i])) {
                    char ch = iter.cur[i];
                    if (left == -1) {
                        left = ch - 48;
                        right = ch - 48;
                    }
                    right = ch - 48;
                }
            }
        }
        int num = (left * 10) + right;
        res += num;
        line_iter_next(&iter);
    }
    return res;
}
