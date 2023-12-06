#include "aoc.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <sys/types.h>

static vec* parse_line(char* line, size_t line_len);
static uint64_t get_possible_ways_to_win(uint64_t time, uint64_t dist);
static uint64_t parse_num(char* line, size_t line_len);

int day6p1(const char* input, size_t input_len) {
    line_iter iter = line_iter_new(input, input_len);
    char* times_str = iter.cur;
    size_t times_str_len = iter.cur_len;
    char* distances_str;
    size_t distances_str_len;
    vec* times;
    vec* distances;
    size_t i, len;
    line_iter_next(&iter);
    int res = 1;
    distances_str = iter.cur;
    distances_str_len = iter.cur_len;

    times = parse_line(times_str, times_str_len);
    distances = parse_line(distances_str, distances_str_len);

    len = times->len;
    for (i = 0; i < len; ++i) {
        int time = *(int*)vec_get_at(times, i);
        int dist = *(int*)vec_get_at(distances, i);
        int possible = get_possible_ways_to_win(time, dist);
        res *= possible;
    }
    vec_free(times, NULL);
    vec_free(distances, NULL);
    return res;
}

uint64_t day6p2(const char* input, size_t input_len) {
    line_iter iter = line_iter_new(input, input_len);
    char* times_str = iter.cur;
    size_t times_str_len = iter.cur_len;
    char* distances_str;
    size_t distances_str_len;
    line_iter_next(&iter);
    uint64_t time, dist;
    distances_str = iter.cur;
    distances_str_len = iter.cur_len;
    time = parse_num(times_str, times_str_len);
    dist = parse_num(distances_str, distances_str_len);
    return get_possible_ways_to_win(time, dist);
}

static uint64_t get_possible_ways_to_win(uint64_t time, uint64_t dist) {
    uint64_t d = time * time - 4 * dist;
    uint64_t sqrt_d = sqrt(d);
    if (sqrt_d * sqrt_d == d) {
        return sqrt_d - 1;
    } else {
        return sqrt_d + 1 - ((time & 1) ^ (sqrt_d & 1));
    }
}

static vec* parse_line(char* line, size_t line_len) {
    vec* vec = vec_new(sizeof(int));
    size_t pos = 0;
    while (pos < line_len) {
        char ch = line[pos];
        if (isdigit(ch)) {
            int cur = 0;
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

static uint64_t parse_num(char* line, size_t line_len) {
    uint64_t res = 0;
    size_t pos = 0;
    while (pos < line_len) {
        char ch = line[pos];
        if (isdigit(ch)) {
            while (pos < line_len && isdigit(line[pos])) {
                res = (res * 10) + (line[pos] - '0');
                pos++;
            }
            continue;
        }
        pos++;
    }
    return res;
}
