#include "aoc.h"
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static vec* make_matrix(const char* input, size_t input_len);
static void matrix_free(vec* matrix);
static void nums_free(vec* nums);
static bool is_special(char ch);
static bool is_gear(char ch);
static void free_vec_in_ht(void* ptr);

typedef struct {
    int dy;
    int dx;
} dir;

typedef struct {
    size_t y;
    size_t x;
} pos;

typedef struct {
    int value;
    vec* positions;
} num;

dir dirs[] = {
    {0, -1}, {0, 1}, {-1, -1}, {-1, 0}, {-1, 1}, {1, -1}, {1, 0}, {1, 1},
};

size_t dirs_len = sizeof dirs / sizeof dirs[0];

int day3p1(const char* input, size_t input_len) {
    vec* matrix = make_matrix(input, input_len);
    vec* nums = vec_new(sizeof(num));
    vec* special_chars = vec_new(sizeof(pos));
    size_t i, len = matrix->len;
    size_t nums_len;
    int res = 0;
    for (i = 0; i < len; ++i) {
        vec* row = *(vec**)vec_get_at(matrix, i);
        size_t j = 0, row_len = row->len;
        while (j < row_len) {
            char ch = *(char*)vec_get_at(row, j);
            if (isdigit(ch)) {
                int num_val = 0;
                vec* positions = vec_new(sizeof(pos));
                num num = {0};
                while (j < row_len && isdigit(*(char*)vec_get_at(row, j))) {
                    pos pos = {i, j};
                    char ch_i = *(char*)vec_get_at(row, j);
                    num_val = (num_val * 10) + (ch_i - '0');
                    j++;
                    vec_push(&positions, &pos);
                }
                num.value = num_val;
                num.positions = positions;
                vec_push(&nums, &num);
                continue;
            } else if (is_special(ch)) {
                pos pos = {i, j};
                vec_push(&special_chars, &pos);
            }
            j++;
        }
    }

    nums_len = nums->len;
    for (i = 0; i < nums_len; ++i) {
        num* num = vec_get_at(nums, i);
        vec* positions = num->positions;
        size_t j, positions_len = positions->len;
        for (j = 0; j < positions_len; ++j) {
            pos* cur_pos = vec_get_at(positions, j);
            size_t k;
            for (k = 0; k < dirs_len; ++k) {
                dir dir = dirs[k];
                /* I know, I don't care */
                size_t y = cur_pos->y + dir.dy;
                size_t x = cur_pos->x + dir.dx;
                pos p = {y, x};
                bool found = vec_find(special_chars, &p, NULL);
                if (found) {
                    res += num->value;
                    goto next_num;
                }
            }
        }
    next_num:
        continue;
    }

    matrix_free(matrix);
    nums_free(nums);
    vec_free(special_chars, NULL);
    return res;
}

int day3p2(const char* input, size_t input_len) {
    vec* matrix = make_matrix(input, input_len);
    vec* nums = vec_new(sizeof(num));
    vec* gear_chars = vec_new(sizeof(pos));
    size_t i, len = matrix->len;
    size_t nums_len;
    int res = 0;
    ht map = ht_new(sizeof(vec*), NULL);
    ht_iter iter;
    for (i = 0; i < len; ++i) {
        vec* row = *(vec**)vec_get_at(matrix, i);
        size_t j = 0, row_len = row->len;
        while (j < row_len) {
            char ch = *(char*)vec_get_at(row, j);
            if (isdigit(ch)) {
                int num_val = 0;
                vec* positions = vec_new(sizeof(pos));
                num num = {0};
                while (j < row_len && isdigit(*(char*)vec_get_at(row, j))) {
                    pos pos = {i, j};
                    char ch_i = *(char*)vec_get_at(row, j);
                    num_val = (num_val * 10) + (ch_i - '0');
                    j++;
                    vec_push(&positions, &pos);
                }
                num.value = num_val;
                num.positions = positions;
                vec_push(&nums, &num);
                continue;
            } else if (is_gear(ch)) {
                pos pos = {i, j};
                vec_push(&gear_chars, &pos);
            }
            j++;
        }
    }

    nums_len = nums->len;
    for (i = 0; i < nums_len; ++i) {
        num* num = vec_get_at(nums, i);
        vec* positions = num->positions;
        size_t j, positions_len = positions->len;
        for (j = 0; j < positions_len; ++j) {
            pos* cur_pos = vec_get_at(positions, j);
            size_t k;
            for (k = 0; k < dirs_len; ++k) {
                dir dir = dirs[k];
                /* I know, I don't care */
                size_t y = cur_pos->y + dir.dy;
                size_t x = cur_pos->x + dir.dx;
                pos p = {y, x};
                bool found = vec_find(gear_chars, &p, NULL);
                if (found) {
                    if (ht_has(&map, &p, sizeof p)) {
                        vec** nums = ht_get(&map, &p, sizeof p);
                        vec_push(nums, &num->value);
                    } else {
                        vec* new_vec = vec_new(sizeof(int));
                        vec_push(&new_vec, &num->value);
                        ht_insert(&map, &p, sizeof p, &new_vec, NULL);
                    }
                    goto next_num;
                }
            }
        }
    next_num:
        continue;
    }

    iter = ht_iter_new(&map);

    while (iter.cur) {
        ht_entry* entry = iter.cur;
        size_t pos_size = sizeof(pos);
        size_t offset = pos_size + ht_padding(pos_size);
        vec* v = *(vec**)(entry->data + offset);
        if (v->len == 2) {
            int a1 = *(int*)vec_get_at(v, 0);
            int a2 = *(int*)vec_get_at(v, 1);
            int t = a1 * a2;
            res += t;
        }
        ht_iter_next(&iter);
    }

    matrix_free(matrix);
    nums_free(nums);
    vec_free(gear_chars, NULL);
    ht_free(&map, NULL, free_vec_in_ht);
    return res;
}

static vec* make_matrix(const char* input, size_t input_len) {
    vec* matrix = vec_new(sizeof(vec*));
    line_iter iter = line_iter_new(input, input_len);
    while (iter.cur) {
        size_t i, len = iter.cur_len;
        vec* row = vec_new(sizeof(char));
        for (i = 0; i < len; ++i) {
            vec_push(&row, &(iter.cur[i]));
        }
        vec_push(&matrix, &row);
        line_iter_next(&iter);
    }
    return matrix;
}

static void row_free(void* ptr) {
    vec* row = *((vec**)ptr);
    vec_free(row, NULL);
}

static void matrix_free(vec* matrix) { vec_free(matrix, row_free); }

static void num_positions_free(void* ptr) {
    num* num = ptr;
    vec_free(num->positions, NULL);
}

static void nums_free(vec* nums) { vec_free(nums, num_positions_free); }

static bool is_special(char ch) { return !isdigit(ch) && ch != '.'; }

static bool is_gear(char ch) { return ch == '*'; }

static void free_vec_in_ht(void* ptr) {
    vec* v = *((vec**)ptr);
    vec_free(v, NULL);
}
