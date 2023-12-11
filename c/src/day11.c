#include "aoc.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint64_t y;
    uint64_t x;
} point;

typedef struct {
    point p;
    vec* points;
} map_item;

static uint64_t solve(const char* input, size_t input_len, uint64_t num_times);
static vec* row_expansions(const char* input, size_t input_len);
static vec* col_expansions(const char* input, size_t input_len);
static vec* find_galaxies(const char* input, size_t input_len);
static uint64_t dist(point* a, point* b);

uint64_t day11p1(const char* input, size_t input_len) {
    return solve(input, input_len, 1);
}

uint64_t day11p2(const char* input, size_t input_len) {
    return solve(input, input_len, 1000000);
}

static uint64_t solve(const char* input, size_t input_len, uint64_t num_times) {
    uint64_t res = 0;
    vec* row_exps = row_expansions(input, input_len);
    vec* col_exps = col_expansions(input, input_len);
    vec* galaxies = find_galaxies(input, input_len);
    size_t i, len = galaxies->len;

    for (i = 0; i < len; ++i) {
        point* p = vec_get_at(galaxies, i);
        point new_point = {0};
        uint64_t new_y;
        uint64_t new_x;
        uint64_t row_exp = *(uint64_t*)vec_get_at(row_exps, p->y);
        uint64_t col_exp = *(uint64_t*)vec_get_at(col_exps, p->x);
        if (num_times == 1) {
            new_y = p->y + row_exp;
            new_x = p->x + col_exp;
        } else {
            new_y = p->y + (row_exp * (num_times - 1));
            new_x = p->x + (col_exp * (num_times - 1));
        }
        new_point.y = new_y;
        new_point.x = new_x;
        vec_set_at(galaxies, i, &new_point, NULL);
    }

    for (i = 0; i < len; ++i) {
        uint64_t c = 0;
        point* p = vec_get_at(galaxies, i);
        size_t j;
        for (j = i + 1; j < len; ++j) {
            point* pi = vec_get_at(galaxies, j);
            uint64_t d = dist(p, pi);
            c += d;
        }
        res += c;
    }

    vec_free(row_exps, NULL);
    vec_free(col_exps, NULL);
    vec_free(galaxies, NULL);
    return res;
}

static vec* row_expansions(const char* input, size_t input_len) {
    vec* res = vec_new(sizeof(uint64_t));
    line_iter iter = line_iter_new(input, input_len);
    uint64_t num_expansions = 0;
    while (iter.cur) {
        set s = set_new(NULL);
        char* cur = iter.cur;
        size_t cur_len = iter.cur_len;
        size_t i;
        for (i = 0; i < cur_len; ++i) {
            char ch = cur[i];
            set_insert(&s, &ch, sizeof(char));
        }
        if (s.len == 1) {
            num_expansions++;
        }
        vec_push(&res, &num_expansions);
        set_free(&s, NULL);
        line_iter_next(&iter);
    }
    return res;
}

static vec* col_expansions(const char* input, size_t input_len) {
    vec* res = vec_new(sizeof(uint64_t));
    line_iter iter = line_iter_new(input, input_len);
    size_t line_len = iter.cur_len;
    size_t i;
    uint64_t num_expansions = 0;
    for (i = 0; i < line_len; ++i) {
        set s = set_new(NULL);
        iter = line_iter_new(input, input_len);
        while (iter.cur) {
            char c = iter.cur[i];
            set_insert(&s, &c, sizeof(char));
            line_iter_next(&iter);
        }
        if (s.len == 1) {
            num_expansions++;
        }
        vec_push(&res, &num_expansions);
        set_free(&s, NULL);
    }
    return res;
}

static vec* find_galaxies(const char* input, size_t input_len) {
    vec* res = vec_new(sizeof(point));
    line_iter iter = line_iter_new(input, input_len);
    size_t i = 0;
    while (iter.cur) {
        char* cur = iter.cur;
        size_t j, len = iter.cur_len;
        for (j = 0; j < len; ++j) {
            char c = cur[j];
            if (c == '#') {
                point p = {i, j};
                vec_push(&res, &p);
            }
        }
        i++;
        line_iter_next(&iter);
    }
    return res;
}

static uint64_t dist(point* a, point* b) {
    uint64_t y = abs((int)(a->y - b->y));
    uint64_t x = abs((int)(a->x - b->x));
    return y + x;
}
