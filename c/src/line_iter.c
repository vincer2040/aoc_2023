#include "aoc.h"

line_iter line_iter_new(const char* input, size_t len) {
    line_iter iter = {0};
    iter.pos = 0;
    iter.len = len;
    iter.input = input;
    iter.cur = NULL;
    iter.next = NULL;
    line_iter_next(&iter);
    line_iter_next(&iter);
    return iter;
}

void line_iter_next(line_iter* iter) {
    size_t old_pos, pos;
    if (iter->pos >= iter->len) {
        iter->cur = iter->next;
        iter->next = NULL;
        iter->cur_len = iter->next_len;
        iter->next_len = 0;
        return;
    }

    iter->cur_len = iter->next_len;
    iter->cur = iter->next;
    iter->next = (char*)(iter->input) + iter->pos;
    pos = iter->pos;
    old_pos = pos;
    while (pos < iter->len && iter->input[pos] != '\n') {
        pos++;
    }
    iter->pos = pos + 1;
    iter->next_len = pos - old_pos;
}
