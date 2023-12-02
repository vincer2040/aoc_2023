#include "aoc.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    Illegal,
    Eof,
    Game,
    Int,
    Blue,
    Red,
    Green,
    Comma,
    Colon,
    Semicolon,
} token_t;

typedef struct {
    token_t type;
    int num;
} token;

typedef struct {
    char* input;
    size_t input_len;
    size_t pos;
    char ch;
} lexer;

typedef struct {
    token cur;
    token peek;
    lexer l;
} parser;

typedef struct {
    int green;
    int blue;
    int red;
} pull;

typedef struct {
    size_t len;
    size_t cap;
    pull pulls[];
} game_pulls;

typedef struct {
    int id;
    game_pulls* pulls;
} game;

static lexer lexer_new(char* input, size_t input_len);
static void lexer_read_char(lexer* l);
static token lexer_next_token(lexer* l);
static void read_string(lexer* l);
static int read_int(lexer* l);
static bool is_letter(char ch);
static void skip_white_space(lexer* l);
static token_t lookup_string(char* ptr);

static parser parser_new(lexer* l);
static game parse(parser* p);
static game_pulls* parse_pulls(parser* p);
static pull parse_pull(parser* p);
static void parser_next_token(parser* p);
static bool cur_tok_is(parser* p, token_t type);
static bool peek_tok_is(parser* p, token_t type);
static bool expect_peek(parser* p, token_t type);

static game_pulls* game_pulls_new(void);
static int game_pulls_push(game_pulls** pulls, pull* p);
static void game_pulls_free(game_pulls* pulls);

static void game_free(game* game);

int day2p1(const char* input, size_t input_len) {
    line_iter iter = line_iter_new(input, input_len);
    int res = 0;
    while (iter.cur) {
        size_t i, game_len, len = iter.cur_len;
        lexer l;
        parser p;
        game g;
        bool possible = true;

        l = lexer_new(iter.cur, len);
        p = parser_new(&l);
        g = parse(&p);
        game_len = g.pulls->len;

        for (i = 0; i < game_len; ++i) {
            pull p = g.pulls->pulls[i];
            if (p.red > 12) {
                possible = false;
            } else if (p.green > 13) {
                possible = false;
            } else if (p.blue > 14) {
                possible = false;
            }
        }

        if (possible) {
            res += g.id;
        }

        game_free(&g);

        line_iter_next(&iter);
    }
    return res;
}

int day2p2(const char* input, size_t input_len) {
    line_iter iter = line_iter_new(input, input_len);
    int res = 0;
    while (iter.cur) {
        size_t i, game_len, len = iter.cur_len;
        lexer l;
        parser p;
        game g;
        int green_amt = 0;
        int blue_amt = 0;
        int red_amt = 0;

        l = lexer_new(iter.cur, len);
        p = parser_new(&l);
        g = parse(&p);
        game_len = g.pulls->len;

        for (i = 0; i < game_len; ++i) {
            pull p = g.pulls->pulls[i];
            if (green_amt < p.green) {
                green_amt = p.green;
            }
            if (blue_amt < p.blue) {
                blue_amt = p.blue;
            }
            if (red_amt < p.red) {
                red_amt = p.red;
            }
        }

        int full = green_amt * blue_amt * red_amt;

        res += full;

        game_free(&g);

        line_iter_next(&iter);
    }
    return res;
}

static lexer lexer_new(char* input, size_t input_len) {
    lexer l = {0};
    l.input = input;
    l.input_len = input_len;
    lexer_read_char(&l);
    return l;
}

static void lexer_read_char(lexer* l) {
    if (l->pos >= l->input_len) {
        l->ch = 0;
    } else {
        l->ch = l->input[l->pos];
    }
    l->pos++;
}

static token lexer_next_token(lexer* l) {
    token tok = {0};
    tok.num = -1;
    skip_white_space(l);
    switch (l->ch) {
    case ':':
        tok.type = Colon;
        break;
    case ';':
        tok.type = Semicolon;
        break;
    case ',':
        tok.type = Comma;
        break;
    case 0:
        tok.type = Eof;
        break;
    default:
        if (is_letter(l->ch)) {
            char* ptr = l->input + (l->pos - 1);
            read_string(l);
            tok.type = lookup_string(ptr);
            return tok;
        } else if (isdigit(l->ch)) {
            int num = read_int(l);
            tok.type = Int;
            tok.num = num;
            return tok;
        }
        break;
    }
    lexer_read_char(l);
    return tok;
}

static bool is_letter(char ch) {
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
}

static void read_string(lexer* l) {
    while (is_letter(l->ch)) {
        lexer_read_char(l);
    }
}

static int read_int(lexer* l) {
    int res = 0;
    while (isdigit(l->ch)) {
        res = (res * 10) + (l->ch - '0');
        lexer_read_char(l);
    }
    return res;
}

static void skip_white_space(lexer* l) {
    while (l->ch == ' ') {
        lexer_read_char(l);
    }
}

static token_t lookup_string(char* ptr) {
    if (strncmp(ptr, "red", 3) == 0) {
        return Red;
    }
    if (strncmp(ptr, "blue", 4) == 0) {
        return Blue;
    }
    if (strncmp(ptr, "Game", 4) == 0) {
        return Game;
    }
    if (strncmp(ptr, "green", 5) == 0) {
        return Green;
    }
    return Illegal;
}

static parser parser_new(lexer* l) {
    parser p = {0};
    p.l = *l;
    parser_next_token(&p);
    parser_next_token(&p);
    return p;
}

static game parse(parser* p) {
    game game = {0};
    int id;
    game.id = -1;
    if (p->cur.type != Game) {
        return game;
    }
    if (!expect_peek(p, Int)) {
        return game;
    }
    id = p->cur.num;
    if (!expect_peek(p, Colon)) {
        return game;
    }
    parser_next_token(p);
    game.id = id;
    game.pulls = parse_pulls(p);
    return game;
}

static game_pulls* parse_pulls(parser* p) {
    game_pulls* pulls = game_pulls_new();
    while (true) {
        pull pull = parse_pull(p);
        game_pulls_push(&pulls, &pull);
        if (p->cur.type == Eof) {
            break;
        }
        parser_next_token(p);
    }
    return pulls;
}

static pull parse_pull(parser* p) {
    pull pull = {0};
    int num;
    if (!cur_tok_is(p, Int)) {
        return pull;
    }
    num = p->cur.num;
    parser_next_token(p);
    switch (p->cur.type) {
    case Blue:
        pull.blue = num;
        break;
    case Red:
        pull.red = num;
        break;
    case Green:
        pull.green = num;
        break;
    default:
        return pull;
    }
    while (peek_tok_is(p, Comma)) {
        parser_next_token(p);
        parser_next_token(p);
        if (!cur_tok_is(p, Int)) {
            memset(&pull, 0, sizeof pull);
            return pull;
        }
        num = p->cur.num;
        parser_next_token(p);
        switch (p->cur.type) {
        case Blue:
            pull.blue = num;
            break;
        case Red:
            pull.red = num;
            break;
        case Green:
            pull.green = num;
            break;
        default:
            return pull;
        }
    }
    parser_next_token(p);
    return pull;
}

static bool cur_tok_is(parser* p, token_t type) { return p->cur.type == type; }

static bool peek_tok_is(parser* p, token_t type) {
    return p->peek.type == type;
}

static bool expect_peek(parser* p, token_t type) {
    if (peek_tok_is(p, type)) {
        parser_next_token(p);
        return true;
    }
    return false;
}

static void parser_next_token(parser* p) {
    p->cur = p->peek;
    p->peek = lexer_next_token(&(p->l));
}

static game_pulls* game_pulls_new(void) {
    game_pulls* pulls;
    size_t size = (sizeof *pulls) + (3 * sizeof(pull));
    pulls = malloc(size);
    assert(pulls != NULL);
    memset(pulls, 0, size);
    pulls->cap = 3;
    return pulls;
}

static int game_pulls_push(game_pulls** pulls, pull* p) {
    size_t len = (*pulls)->len, cap = (*pulls)->cap;
    if (len == cap) {
        void* tmp;
        cap <<= 1;
        tmp = realloc(*pulls, sizeof **pulls + (sizeof(pull) * cap));
        if (tmp == NULL) {
            return -1;
        }
        *pulls = tmp;
        memset(&((*pulls)->pulls[len]), 0, ((cap - len) * sizeof(pull)));
        (*pulls)->cap = cap;
    }
    memcpy(&((*pulls)->pulls[len]), p, sizeof(pull));
    (*pulls)->len++;
    return 0;
}

static void game_pulls_free(game_pulls* pulls) { free(pulls); }

static void game_free(game* game) { game_pulls_free(game->pulls); }
