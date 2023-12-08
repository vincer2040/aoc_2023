#include "aoc.h"
#include <ctype.h>
#include <stdio.h>

typedef enum {
    HighCard = 0,
    OnePair = 1,
    TwoPair = 2,
    ThreeOfAKind = 3,
    FullHouse = 4,
    FourOfAKind = 5,
    FiveOfAKind = 6,
} hand_result;

typedef struct {
    hand_result result;
    vstr hand;
    int bid;
} hand_data;

static void vec_free_fn(void* ptr);
static hand_result calculate_hand_result(vstr* hand);
static hand_result calculate_hand_result2(vstr* hand);
static vstr order_string(vstr* hand);
static vstr order_string2(vstr* hand);
static int sort_fn(void* a, void* b);
static int sort_fn2(void* a, void* b);

int day7p1(const char* input, size_t input_len) {
    int res = 0;
    line_iter iter = line_iter_new(input, input_len);
    vec* hands = vec_new(sizeof(hand_data));
    size_t i, len;

    while (iter.cur) {
        size_t i = 0, cur_len = iter.cur_len;
        char* cur = iter.cur;
        vstr hand = vstr_new();
        int bid = 0;
        hand_result hr;
        hand_data hd = {0};
        while (cur[i] != ' ') {
            vstr_push_char(&hand, cur[i]);
            i++;
        }
        i++;
        while (i < cur_len && isdigit(cur[i])) {
            bid = (bid * 10) + (cur[i] - '0');
            i++;
        }

        hr = calculate_hand_result(&hand);
        hd.bid = bid;
        hd.hand = hand;
        hd.result = hr;
        vec_push(&hands, &hd);
        line_iter_next(&iter);
    }

    quick_sort(hands->data, hands->len, hands->data_size, sort_fn);

    len = hands->len;
    for (i = 0; i < len; ++i) {
        hand_data* data = vec_get_at(hands, i);
        res += ((i + 1) * data->bid);
    }

    vec_free(hands, vec_free_fn);
    return res;
}

int day7p2(const char* input, size_t input_len) {
    int res = 0;
    line_iter iter = line_iter_new(input, input_len);
    vec* hands = vec_new(sizeof(hand_data));
    size_t i, len;

    while (iter.cur) {
        size_t i = 0, cur_len = iter.cur_len;
        char* cur = iter.cur;
        vstr hand = vstr_new();
        int bid = 0;
        hand_result hr;
        hand_data hd = {0};
        while (cur[i] != ' ') {
            vstr_push_char(&hand, cur[i]);
            i++;
        }
        i++;
        while (i < cur_len && isdigit(cur[i])) {
            bid = (bid * 10) + (cur[i] - '0');
            i++;
        }

        hr = calculate_hand_result2(&hand);
        hd.bid = bid;
        hd.hand = hand;
        hd.result = hr;
        vec_push(&hands, &hd);
        line_iter_next(&iter);
    }

    quick_sort(hands->data, hands->len, hands->data_size, sort_fn2);

    len = hands->len;
    for (i = 0; i < len; ++i) {
        hand_data* data = vec_get_at(hands, i);
        res += ((i + 1) * data->bid);
    }

    vec_free(hands, vec_free_fn);
    return res;
}

static hand_result calculate_hand_result(vstr* hand) {
    size_t i, len = vstr_len(hand);
    const char* data = vstr_data(hand);
    hand_result hr = HighCard;
    ht map = ht_new(sizeof(int), NULL);
    ht_iter iter;
    for (i = 0; i < len; ++i) {
        char at = data[i];
        if (ht_has(&map, &at, sizeof(char))) {
            int cur = *(int*)ht_get(&map, &at, sizeof(char));
            int new = cur + 1;
            ht_insert(&map, &at, sizeof(char), &new, NULL);
        } else {
            int new = 1;
            ht_insert(&map, &at, sizeof(char), &new, NULL);
        }
    }

    iter = ht_iter_new(&map);

    while (iter.cur) {
        ht_entry* cur = iter.cur;
        int at = *(int*)(cur->data + sizeof(char) + ht_padding(sizeof(char)));
        switch (at) {
        case 1:
            break;
        case 2:
            switch (hr) {
            case HighCard:
                hr = OnePair;
                break;
            case OnePair:
                hr = TwoPair;
                break;
            case ThreeOfAKind:
                hr = FullHouse;
                break;
            default:
                break;
            }
            break;
        case 3:
            switch (hr) {
            case HighCard:
                hr = ThreeOfAKind;
                break;
            case OnePair:
                hr = FullHouse;
                break;
            default:
                break;
            }
            break;
        case 4:
            hr = FourOfAKind;
            break;
        case 5:
            hr = FiveOfAKind;
            break;
        }
        ht_iter_next(&iter);
    }

    ht_free(&map, NULL, NULL);
    return hr;
}

static hand_result calculate_hand_result2(vstr* hand) {
    size_t i, len = vstr_len(hand);
    const char* data = vstr_data(hand);
    hand_result hr = HighCard;
    hand_result new_result;
    ht map = ht_new(sizeof(int), NULL);
    ht_iter iter;
    char j = 'J';
    bool has_j;
    int* num_j;
    for (i = 0; i < len; ++i) {
        char at = data[i];
        if (ht_has(&map, &at, sizeof(char))) {
            int cur = *(int*)ht_get(&map, &at, sizeof(char));
            int new = cur + 1;
            ht_insert(&map, &at, sizeof(char), &new, NULL);
        } else {
            int new = 1;
            ht_insert(&map, &at, sizeof(char), &new, NULL);
        }
    }

    iter = ht_iter_new(&map);

    while (iter.cur) {
        ht_entry* cur = iter.cur;
        int at = *(int*)(cur->data + sizeof(char) + ht_padding(sizeof(char)));
        switch (at) {
        case 1:
            break;
        case 2:
            switch (hr) {
            case HighCard:
                hr = OnePair;
                break;
            case OnePair:
                hr = TwoPair;
                break;
            case ThreeOfAKind:
                hr = FullHouse;
                break;
            default:
                break;
            }
            break;
        case 3:
            switch (hr) {
            case HighCard:
                hr = ThreeOfAKind;
                break;
            case OnePair:
                hr = FullHouse;
                break;
            default:
                break;
            }
            break;
        case 4:
            hr = FourOfAKind;
            break;
        case 5:
            hr = FiveOfAKind;
            break;
        }
        ht_iter_next(&iter);
    }

    new_result = hr;

    has_j = ht_has(&map, &j, sizeof(char));
    num_j = ht_get(&map, &j, sizeof(char));

    switch (hr) {
    case HighCard:
        if (has_j) {
            new_result = OnePair;
        }
        break;
    case OnePair:
        if (has_j) {
            new_result = ThreeOfAKind;
        }
        break;
    case TwoPair:
        if (has_j) {
            if (*num_j == 1) {
                new_result = FullHouse;
            } else if (*num_j == 2) {
                new_result = FourOfAKind;
            }
        }
        break;
    case ThreeOfAKind:
        if (has_j) {
            new_result = FourOfAKind;
        }
        break;
    case FullHouse:
        if (has_j) {
            new_result = FiveOfAKind;
        }
        break;
    case FourOfAKind:
        if (has_j) {
            new_result = FiveOfAKind;
        }
        break;
    default:
        break;
    }

    ht_free(&map, NULL, NULL);
    return new_result;
}

static void vec_free_fn(void* ptr) {
    hand_data* hd = ptr;
    vstr_free(&(hd->hand));
}

static int sort_fn(void* a, void* b) {
    hand_data* ad = a;
    hand_data* bd = b;
    vstr ordered_a, ordered_b;
    if (ad->result != bd->result) {
        return ad->result - bd->result;
    }
    ordered_a = order_string(&(ad->hand));
    ordered_b = order_string(&(bd->hand));
    return vstr_cmp(&ordered_a, &ordered_b);
}

static int sort_fn2(void* a, void* b) {
    hand_data* ad = a;
    hand_data* bd = b;
    vstr ordered_a, ordered_b;
    if (ad->result != bd->result) {
        return ad->result - bd->result;
    }
    ordered_a = order_string2(&(ad->hand));
    ordered_b = order_string2(&(bd->hand));
    return vstr_cmp(&ordered_a, &ordered_b);
}

static vstr order_string(vstr* hand) {
    vstr s = vstr_new();
    size_t i, len = vstr_len(hand);
    const char* data = vstr_data(hand);
    for (i = 0; i < len; ++i) {
        char ch = data[i];
        switch (ch) {
        case 'A':
            vstr_push_char(&s, 'z');
            break;
        case 'K':
            vstr_push_char(&s, 'y');
            break;
        case 'Q':
            vstr_push_char(&s, 'x');
            break;
        case 'J':
            vstr_push_char(&s, 'w');
            break;
        case 'T':
            vstr_push_char(&s, 'v');
            break;
        case '9':
            vstr_push_char(&s, 'u');
            break;
        case '8':
            vstr_push_char(&s, 't');
            break;
        case '7':
            vstr_push_char(&s, 's');
            break;
        case '6':
            vstr_push_char(&s, 'r');
            break;
        case '5':
            vstr_push_char(&s, 'q');
            break;
        case '4':
            vstr_push_char(&s, 'p');
            break;
        case '3':
            vstr_push_char(&s, 'o');
            break;
        case '2':
            vstr_push_char(&s, 'n');
            break;
        case '1':
            vstr_push_char(&s, 'm');
            break;
        }
    }
    return s;
}

static vstr order_string2(vstr* hand) {
    vstr s = vstr_new();
    size_t i, len = vstr_len(hand);
    const char* data = vstr_data(hand);
    for (i = 0; i < len; ++i) {
        char ch = data[i];
        switch (ch) {
        case 'A':
            vstr_push_char(&s, 'z');
            break;
        case 'K':
            vstr_push_char(&s, 'y');
            break;
        case 'Q':
            vstr_push_char(&s, 'x');
            break;
        case 'T':
            vstr_push_char(&s, 'w');
            break;
        case '9':
            vstr_push_char(&s, 'v');
            break;
        case '8':
            vstr_push_char(&s, 'u');
            break;
        case '7':
            vstr_push_char(&s, 't');
            break;
        case '6':
            vstr_push_char(&s, 's');
            break;
        case '5':
            vstr_push_char(&s, 'r');
            break;
        case '4':
            vstr_push_char(&s, 'q');
            break;
        case '3':
            vstr_push_char(&s, 'p');
            break;
        case '2':
            vstr_push_char(&s, 'o');
            break;
        case '1':
            vstr_push_char(&s, 'n');
            break;
        case 'J':
            vstr_push_char(&s, 'm');
            break;
        }
    }
    return s;
}
