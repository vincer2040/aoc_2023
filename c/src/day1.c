#include "aoc.h"
#include <assert.h>
#include <ctype.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

void p1(const char* input, size_t input_len);
void p2(const char* input, size_t input_len);

int main(void) {
    char* buf = NULL;
    size_t bytes_read;
    ssize_t read = read_file(NULL, &buf, &bytes_read);
    assert(read != -1);
    p2(buf, bytes_read);
    free(buf);
    return 0;
}

void p1(const char* input, size_t input_len) {
    line_iter iter = line_iter_new(input, input_len);
    int res = 0;
    char state[3] = {0};
    while (iter.cur) {
        size_t i, len = iter.cur_len;
        for (i = 0; i < len; ++i) {
            char ch = iter.cur[i];
            if ('0' <= ch && ch <= '9') {
                state[0] = ch;
                break;
            }
        }
        for (i = len; i >= 0; i--) {
            char ch = iter.cur[i];
            if ('0' <= ch && ch <= '9') {
                state[1] = ch;
                break;
            }
        }
        int t = atoi(state);
        res += t;
        line_iter_next(&iter);
    }
    printf("%d\n", res);
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

void p2(const char* input, size_t input_len) {
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
    printf("%d\n", res);
}
