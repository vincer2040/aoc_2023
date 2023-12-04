#include "aoc.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>

typedef struct {
    int card_num;
    vec* win_nums;
    vec* got_nums;
} game;

static game parse_game(char* line, size_t line_len);
static bool is_letter(char ch);
static bool is_space(char ch);
static void game_free(game* game);

int day4p1(const char* input, size_t input_len) {
    line_iter iter = line_iter_new(input, input_len);
    int res = 0;
    while (iter.cur) {
        size_t line_len = iter.cur_len;
        char* line = iter.cur;
        game g = parse_game(line, line_len);
        vec* win = g.win_nums;
        vec* got = g.got_nums;
        size_t i, len = win->len;
        int num_found = 0;
        for (i = 0; i < len; ++i) {
            int cur = *(int*)vec_get_at(win, i);
            bool has = vec_find(got, &cur, NULL);
            if (has) {
                num_found += 1;
            }
        }
        res += pow(2, num_found - 1);
        game_free(&g);
        line_iter_next(&iter);
    }
    return res;
}

int day4p2(const char* input, size_t input_len) {
    line_iter iter = line_iter_new(input, input_len);
    int res = 0;
    int zero = 0;
    size_t line_num = 0;
    vec* played = vec_new(sizeof(int));
    size_t line_count = num_lines(&iter);
    size_t i, len;
    vec_set_cap(&played, line_count);
    vec_fill(played, &zero);
    while (iter.cur) {
        size_t line_len = iter.cur_len;
        char* line = iter.cur;
        game g = parse_game(line, line_len);
        vec* win = g.win_nums;
        vec* got = g.got_nums;
        size_t num_found = 0;
        int c = *(int*)vec_get_at(played, line_num) + 1;
        vec_set_at(played, line_num, &c, NULL);
        len = win->len;
        for (i = 0; i < len; ++i) {
            int cur = *(int*)vec_get_at(win, i);
            bool has = vec_find(got, &cur, NULL);
            if (has) {
                num_found += 1;
            }
        }
        for (i = 0; i < num_found; ++i) {
            size_t idx_to_set = i + line_num + 1;
            int c_old = *(int*)vec_get_at(played, idx_to_set);
            c = *(int*)vec_get_at(played, line_num);
            int n = c_old + c;
            vec_set_at(played, idx_to_set, &n, NULL);
        }
        game_free(&g);
        line_iter_next(&iter);
        line_num++;
    }
    len = played->len;
    for (i = 0; i < len; ++i) {
        int c = *(int*)vec_get_at(played, i);
        res += c;
    }

    vec_free(played, NULL);
    return res;
}

static game parse_game(char* line, size_t line_len) {
    game g = {0};
    size_t pos = 0;
    int card_num = 0;
    bool done_winnings = false;
    vec* winnings = vec_new(sizeof(int));
    vec* got = vec_new(sizeof(int));
    while (pos < line_len) {
        char cur = line[pos];
        if (is_letter(cur)) {
            while (is_letter(line[pos])) {
                pos++;
            }
            continue;
        }
        if (isdigit(cur)) {
            /* this digit is a card number */
            if (card_num == 0) {
                while (pos < line_len && isdigit(line[pos])) {
                    card_num = (card_num * 10) + (line[pos] - '0');
                    pos++;
                }
                continue;
            }

            /* this digit is a number in game */
            int cur = 0;
            while (pos < line_len && isdigit(line[pos])) {
                cur = (cur * 10) + (line[pos] - '0');
                pos++;
            }

            if (!done_winnings) {
                vec_push(&winnings, &cur);
            } else {
                vec_push(&got, &cur);
            }
            continue;
        }
        if (is_space(cur)) {
            while (pos < line_len && is_space(line[pos])) {
                pos++;
            }
            continue;
        }
        if (cur == '|') {
            done_winnings = true;
        }
        pos++;
    }
    g.win_nums = winnings;
    g.got_nums = got;
    g.card_num = card_num;
    return g;
}

static bool is_letter(char ch) {
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
}

static bool is_space(char ch) { return ch == ' '; }

static void game_free(game* game) {
    vec_free(game->win_nums, NULL);
    vec_free(game->got_nums, NULL);
}
