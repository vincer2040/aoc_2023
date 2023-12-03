#include "aoc.h"
#include <assert.h>
#include <memory.h>
#include <stdlib.h>

#define VEC_INITIAL_CAP 2

vec* vec_new(size_t data_size) {
    vec* vec;
    size_t size = (sizeof *vec) + (data_size * VEC_INITIAL_CAP);
    vec = malloc(size);
    assert(vec != NULL);
    memset(vec, 0, size);
    vec->data_size = data_size;
    vec->cap = VEC_INITIAL_CAP;
    return vec;
}

int vec_push(vec** vec, void* data) {
    size_t len = (*vec)->len, cap = (*vec)->cap, data_size = (*vec)->data_size;
    if (len == cap) {
        void* tmp;
        cap <<= 1;
        tmp = realloc(*vec, (sizeof **vec) + (data_size * cap));
        if (tmp == NULL) {
            return -1;
        }
        *vec = tmp;
        memset((*vec)->data + (len * data_size), 0, (cap - len) * data_size);
        (*vec)->cap = cap;
    }
    memcpy((*vec)->data + (len * data_size), data, data_size);
    (*vec)->len++;
    return 0;
}

void* vec_get_at(vec* vec, size_t idx) {
    if (idx >= vec->len) {
        return NULL;
    }
    return vec->data + (idx * vec->data_size);
}

bool vec_find(vec* vec, void* find, CmpFn* fn) {
    size_t i, len = vec->len, data_size = vec->data_size;
    for (i = 0; i < len; ++i) {
        void* ptr = vec->data + (i * data_size);
        if (fn) {
            if (fn(find, ptr) == 0) {
                return true;
            }
        } else {
            if (memcmp(ptr, find, data_size) == 0) {
                return true;
            }
        }
    }
    return false;
}

void vec_free(vec* vec, FreeFn* fn) {
    if (fn) {
        size_t i, len = vec->len, data_size = vec->data_size;
        for (i = 0; i < len; ++i) {
            void* ptr = vec->data + (i * data_size);
            fn(ptr);
        }
    }
    free(vec);
}
