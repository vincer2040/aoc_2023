#include "aoc.h"
#include <ctype.h>
#include <stdio.h>

static vec* parse_line(char* line, size_t line_len);
static vec* get_difs(vec* nums);
static void free_difs(vec* v);

int day9p1(const char* input, size_t input_len) {
    int res = 0;
    line_iter iter = line_iter_new(input, input_len);
    while (iter.cur) {
        char* line = iter.cur;
        size_t line_len = iter.cur_len;
        vec* nums = parse_line(line, line_len);
        size_t i, len = nums->len;
        vec* difs = get_difs(nums);
        int num_to_add = 0;
        int num_to_add_to = *(int*)vec_get_at(nums, len - 1);
        int num_to_add_to_res;
        i = difs->len - 1;
        for (; i != -1; i--) {
            vec* cur_difs = *(vec**)vec_get_at(difs, i);
            size_t cur_idx = cur_difs->len - 1;
            int c = *(int*)vec_get_at(cur_difs, cur_idx);
            num_to_add += c;
        }
        num_to_add_to_res = num_to_add_to + num_to_add;
        free_difs(difs);
        vec_free(nums, NULL);
        line_iter_next(&iter);
        res += num_to_add_to_res;
    }
    return res;
}

int day9p2(const char* input, size_t input_len) {
    int res = 0;
    line_iter iter = line_iter_new(input, input_len);
    while (iter.cur) {
        char* line = iter.cur;
        size_t line_len = iter.cur_len;
        vec* nums = parse_line(line, line_len);
        size_t i;
        vec* difs = get_difs(nums);
        int num_to_subtract = 0;
        int num_to_subtract_from = *(int*)vec_get_at(nums, 0);
        int num_to_add_to_res;
        i = difs->len - 1;
        for (; i != -1; i--) {
            vec* cur_difs = *(vec**)vec_get_at(difs, i);
            int c = *(int*)vec_get_at(cur_difs, 0);
            num_to_subtract = c - num_to_subtract;
        }
        free_difs(difs);
        vec_free(nums, NULL);
        line_iter_next(&iter);
        num_to_add_to_res = num_to_subtract_from - num_to_subtract;
        res += num_to_add_to_res;
    }
    return res;
}

static vec* parse_line(char* line, size_t line_len) {
    vec* line_data = vec_new(sizeof(int));
    size_t pos = 0;
    while (pos < line_len) {
        if (isdigit(line[pos]) || line[pos] == '-') {
            bool is_negative = false;
            int cur = 0;
            if (line[pos] == '-') {
                is_negative = true;
                pos++;
            }
            while (isdigit(line[pos])) {
                cur = (cur * 10) + (line[pos] - '0');
                pos++;
            }
            if (is_negative) {
                cur *= -1;
            }
            vec_push(&line_data, &cur);
            continue;
        }
        pos++;
    }
    return line_data;
}

static vec* get_difs_of_cur(vec* nums) {
    vec* difs = vec_new(sizeof(int));
    size_t i, len = nums->len;
    for (i = 1; i < len; ++i) {
        int cur = *(int*)vec_get_at(nums, i);
        int prev = *(int*)vec_get_at(nums, i - 1);
        int n = cur - prev;
        vec_push(&difs, &n);
    }
    return difs;
}

static vec* get_difs(vec* nums) {
    vec* difs = vec_new(sizeof(vec*));
    vec* cur_nums = nums;
    while (true) {
        set s = set_new(NULL);
        vec* cur_difs = get_difs_of_cur(cur_nums);
        size_t i, len = cur_difs->len;
        for (i = 0; i < len; ++i) {
            set_insert(&s, vec_get_at(cur_difs, i), sizeof(int));
        }
        if (s.len == 1) {
            set_free(&s, NULL);
            vec_push(&difs, &cur_difs);
            break;
        }
        vec_push(&difs, &cur_difs);
        set_free(&s, NULL);
        cur_nums = cur_difs;
    }
    return difs;
}

static void free_cur_dif(void* p) {
    vec* v = *(vec**)p;
    vec_free(v, NULL);
}

static void free_difs(vec* v) { vec_free(v, free_cur_dif); }
