#include "aoc.h"
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static vec* parse_line(char* line, size_t line_len);
static vec* parse_maps(line_iter* iter);
static void maps_free(vec* maps);

int day5p1(const char* input, size_t input_len) {
    line_iter iter = line_iter_new(input, input_len);
    vec* seeds = parse_line(iter.cur, iter.cur_len);
    vec* maps;
    size_t i, j, map_len, len = seeds->len;
    int64_t res = INT64_MAX;
    line_iter_next(&iter);
    line_iter_next(&iter);
    maps = parse_maps(&iter);
    map_len = maps->len;
    for (i = 0; i < len; ++i) {
        int64_t seed = *(int64_t*)vec_get_at(seeds, i);
        for (j = 0; j < map_len; ++j) {
            vec* at = *(vec**)vec_get_at(maps, j);
            size_t k, at_len = at->len;
            for (k = 0; k < at_len; ++k) {
                vec* d = *(vec**)vec_get_at(at, k);
                int64_t dst = *(int64_t*)vec_get_at(d, 0);
                int64_t src = *(int64_t*)vec_get_at(d, 1);
                int64_t range = *(int64_t*)vec_get_at(d, 2);
                if ((seed >= src) && (seed <= src + range)) {
                    seed += dst - src;
                    break;
                }
            }
        }
        if (seed < res) {
            res = seed;
        }
    }
    maps_free(maps);
    vec_free(seeds, NULL);
    return res;
}

int day5p2(const char* input, size_t input_len) {
    line_iter iter = line_iter_new(input, input_len);
    vec* seeds = parse_line(iter.cur, iter.cur_len);
    vec* maps;
    size_t i, j, map_len, len = seeds->len;
    int64_t res = INT64_MAX;
    int64_t start = 0;
    bool is_range = false;
    line_iter_next(&iter);
    line_iter_next(&iter);
    maps = parse_maps(&iter);
    map_len = maps->len;
    for (i = 0; i < len; ++i) {
        int64_t s = *(int64_t*)vec_get_at(seeds, i);
        if (!is_range) {
            start = s;
            is_range = true;
            continue;
        } else {
            int64_t end = start + s - 1;
            printf("%ld %ld\n", start, end);
            for (; start < end; ++start) {
                int64_t seed = start;
                // printf("%ld\n", start);
                for (j = 0; j < map_len; ++j) {
                    vec* at = *(vec**)vec_get_at(maps, j);
                    size_t k, at_len = at->len;
                    for (k = 0; k < at_len; ++k) {
                        vec* d = *(vec**)vec_get_at(at, k);
                        int64_t dst = *(int64_t*)vec_get_at(d, 0);
                        int64_t src = *(int64_t*)vec_get_at(d, 1);
                        int64_t range = *(int64_t*)vec_get_at(d, 2);
                        if ((seed >= src) && (seed <= src + range)) {
                            seed += dst - src;
                            break;
                        }
                    }
                }
                if (seed < res) {
                    res = seed;
                }
            }
            is_range = false;
        }
    }
    maps_free(maps);
    vec_free(seeds, NULL);
    return res;
}

static vec* parse_line(char* line, size_t line_len) {
    vec* vec = vec_new(sizeof(int64_t));
    size_t pos = 0;
    while (pos < line_len) {
        char ch = line[pos];
        if (isdigit(ch)) {
            int64_t cur = 0;
            while (pos < line_len && isdigit(line[pos])) {
                cur = (cur * 10) + (line[pos] - '0');
                pos++;
            }
            vec_push(&vec, &cur);
            continue;
        }
        pos++;
    }
    return vec;
}

static vec* parse_maps(line_iter* iter) {
    vec* res = vec_new(sizeof(vec*));
    while (iter->cur) {
        if (isdigit(*iter->cur)) {
            vec* cur = vec_new(sizeof(vec*));
            while (iter->cur && isdigit(*iter->cur)) {
                vec* nums = parse_line(iter->cur, iter->cur_len);
                vec_push(&cur, &nums);
                line_iter_next(iter);
            }
            vec_push(&res, &cur);
            continue;
        }
        line_iter_next(iter);
    }
    return res;
}

static void map_items_free(void* ptr) {
    vec* v = *(vec**)ptr;
    vec_free(v, NULL);
}

static void map_vec_free(void* ptr) {
    vec* v = *(vec**)ptr;
    vec_free(v, map_items_free);
}

static void maps_free(vec* maps) { vec_free(maps, map_vec_free); }
