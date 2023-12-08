#include "aoc.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    vstr left;
    vstr right;
} node;

typedef struct {
    vstr from;
    node node;
} line_data;

static line_data parse_line(char* cur, size_t cur_len);
static int key_cmp(void* a, void* b);
static bool is_letter(char c);
static int walk(ht* graph, vstr* cur_location, char* instructions,
                size_t instructions_len, size_t instructions_idx,
                int num_steps);
static uint64_t walk2(ht* graph, vstr* cur_location, char* instructions,
                      size_t instructions_len, size_t instructions_idx,
                      uint64_t num_steps);
static uint64_t lcm_of_vec(vec* v);

int day8p1(const char* input, size_t input_len) {
    int res = 0;
    ht map = ht_new(sizeof(node), key_cmp);
    line_iter iter = line_iter_new(input, input_len);
    vstr start = vstr_from("AAA");
    char* instructions = iter.cur;
    size_t instructions_len = iter.cur_len;
    line_iter_next(&iter);
    line_iter_next(&iter);
    while (iter.cur) {
        char* cur = iter.cur;
        size_t cur_len = iter.cur_len;
        line_data ld = parse_line(cur, cur_len);
        ht_insert(&map, &(ld.from), sizeof(vstr), &(ld.node), NULL);
        line_iter_next(&iter);
    }
    res = walk(&map, &start, instructions, instructions_len, 0, 0);
    ht_free(&map, NULL, NULL);
    return res;
}

uint64_t day8p2(const char* input, size_t input_len) {
    uint64_t res = 0;
    ht map = ht_new(sizeof(node), key_cmp);
    line_iter iter = line_iter_new(input, input_len);
    char* instructions = iter.cur;
    size_t instructions_len = iter.cur_len;
    ht_iter ht_iter;
    vec* path_lens = vec_new(sizeof(uint64_t));
    line_iter_next(&iter);
    line_iter_next(&iter);
    while (iter.cur) {
        char* cur = iter.cur;
        size_t cur_len = iter.cur_len;
        line_data ld = parse_line(cur, cur_len);
        ht_insert(&map, &(ld.from), sizeof(vstr), &(ld.node), NULL);
        line_iter_next(&iter);
    }
    ht_iter = ht_iter_new(&map);
    while (ht_iter.cur) {
        vstr* key = (vstr*)(ht_iter.cur->data);
        const char* key_str = vstr_data(key);
        size_t key_len = vstr_len(key);
        uint64_t path_len;
        if (key_str[key_len - 1] != 'A') {
            ht_iter_next(&ht_iter);
            continue;
        }
        path_len = walk2(&map, key, instructions, instructions_len, 0, 0);
        vec_push(&path_lens, &path_len);
        ht_iter_next(&ht_iter);
    }
    res = lcm_of_vec(path_lens);
    ht_free(&map, NULL, NULL);
    vec_free(path_lens, NULL);
    return res;
}

static line_data parse_line(char* cur, size_t cur_len) {
    line_data ld = {0};
    size_t pos = 0;
    vstr from = vstr_new();
    vstr left = vstr_new();
    vstr right = vstr_new();
    bool done_from = false;
    bool done_left = false;
    bool done_right = false;
    node n = {0};
    while (pos < cur_len) {
        if (is_letter(cur[pos])) {
            if (!done_from) {
                while (is_letter(cur[pos])) {
                    vstr_push_char(&from, cur[pos]);
                    pos++;
                }
                done_from = true;
                continue;
            }
            if (!done_left) {
                while (is_letter(cur[pos])) {
                    vstr_push_char(&left, cur[pos]);
                    pos++;
                }
                done_left = true;
                continue;
            }
            if (!done_right) {
                while (is_letter(cur[pos])) {
                    vstr_push_char(&right, cur[pos]);
                    pos++;
                }
                done_right = true;
                continue;
            }
        }
        pos++;
    }
    ld.from = from;
    n.left = left;
    n.right = right;
    ld.node = n;
    return ld;
}

static int walk(ht* graph, vstr* cur_location, char* instructions,
                size_t instructions_len, size_t instructions_idx,
                int num_steps) {
    char instruction;
    node* n;
    if (strncmp("ZZZ", vstr_data(cur_location), 3) == 0) {
        return num_steps;
    }
    if (instructions_idx >= instructions_len) {
        return walk(graph, cur_location, instructions, instructions_len, 0,
                    num_steps);
    }
    instruction = instructions[instructions_idx];
    n = ht_get(graph, cur_location, sizeof(vstr));
    switch (instruction) {
    case 'L':
        return walk(graph, &(n->left), instructions, instructions_len,
                    instructions_idx + 1, num_steps + 1);
    case 'R':
        return walk(graph, &(n->right), instructions, instructions_len,
                    instructions_idx + 1, num_steps + 1);
    }
    return -1;
}

static uint64_t walk2(ht* graph, vstr* cur_location, char* instructions,
                      size_t instructions_len, size_t instructions_idx,
                      uint64_t num_steps) {
    const char* cur_str = vstr_data(cur_location);
    size_t cur_len = vstr_len(cur_location);
    char instruction;
    node* n;
    if (cur_str[cur_len - 1] == 'Z') {
        return num_steps;
    }
    if (instructions_idx >= instructions_len) {
        return walk2(graph, cur_location, instructions, instructions_len, 0,
                     num_steps);
    }
    instruction = instructions[instructions_idx];
    n = ht_get(graph, cur_location, sizeof(vstr));
    switch (instruction) {
    case 'L':
        return walk2(graph, &(n->left), instructions, instructions_len,
                     instructions_idx + 1, num_steps + 1);
    case 'R':
        return walk2(graph, &(n->right), instructions, instructions_len,
                     instructions_idx + 1, num_steps + 1);
    }
    return -1;
}

static bool is_letter(char c) {
    return ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9');
}

static int key_cmp(void* a, void* b) {
    vstr* as = a;
    vstr* bs = b;
    return vstr_cmp(as, bs);
}

static uint64_t gcd(uint64_t a, uint64_t b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

static uint64_t lcm(uint64_t a, uint64_t b) { return (a * b) / gcd(a, b); }

static uint64_t lcm_of_vec(vec* v) {
    uint64_t result = *(uint64_t*)vec_get_at(v, 0);
    size_t i, len = v->len;
    for (i = 1; i < len; ++i) {
        uint64_t cur = *(uint64_t*)vec_get_at(v, i);
        result = lcm(result, cur);
    }
    return result;
}
