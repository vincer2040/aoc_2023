#ifndef __AOC_H__

#define __AOC_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

ssize_t read_file(const char* path, char** buf, size_t* bytes_read);

int day1p1(const char* input, size_t input_len);
int day1p2(const char* input, size_t input_len);

int day2p1(const char* input, size_t input_len);
int day2p2(const char* input, size_t input_len);

int day3p1(const char* input, size_t input_len);
int day3p2(const char* input, size_t input_len);

int day4p1(const char* input, size_t input_len);
int day4p2(const char* input, size_t input_len);

typedef struct {
    size_t pos;
    size_t len;
    size_t cur_len;
    size_t next_len;
    const char* input;
    char* cur;
    char* next;
} line_iter;

line_iter line_iter_new(const char* input, size_t len);
size_t num_lines(line_iter* iter);
void line_iter_next(line_iter* iter);

typedef struct {
    size_t len;
    size_t cap;
    size_t data_size;
    unsigned char data[];
} vec;

typedef int CmpFn(void* a, void* b);
typedef void FreeFn(void* ptr);

vec* vec_new(size_t data_size);
int vec_push(vec** vec, void* data);
int vec_set_cap(vec** vec, size_t cap);
void vec_fill(vec* vec, void* data);
void* vec_get_at(vec* vec, size_t idx);
int vec_set_at(vec* vec, size_t idx, void* data, FreeFn* fn);
bool vec_find(vec* vec, void* find, CmpFn* fn);
void vec_free(vec* vec, FreeFn* free_fn);

void get_random_bytes(uint8_t* p, size_t len);

typedef struct ht_entry {
    size_t key_len;
    unsigned char data[];
} ht_entry;

ht_entry* ht_entry_new(void* key, size_t key_len, void* data, size_t data_size);
void ht_entry_free(ht_entry* entry, FreeFn* free_key, FreeFn* free_val);

typedef struct {
    size_t len;
    size_t cap;
    struct ht_entry** entries;
} ht_bucket;

#define HT_SEED_SIZE 16
#define HT_INITIAL_CAP 32
#define HT_BUCKET_INITIAL_CAP 2

#define ht_padding(size)                                                       \
    ((sizeof(void*) - ((size + 8) % sizeof(void*))) & (sizeof(void*) - 1))

typedef struct {
    size_t len;
    size_t cap;
    size_t data_size;
    CmpFn* cmp_key;
    unsigned char seed[HT_SEED_SIZE];
    ht_bucket* buckets;
} ht;

ht ht_new(size_t data_size, CmpFn* cmp_key);
size_t ht_len(ht* ht);
bool ht_has(ht* ht, void* key, size_t key_len);
int ht_insert(ht* ht, void* key, size_t key_len, void* value, FreeFn* fn);
int ht_try_insert(ht* ht, void* key, size_t key_len, void* value);
void* ht_get(ht* ht, void* key, size_t key_len);
int ht_delete(ht* ht, void* key, size_t key_len, FreeFn* free_key,
              FreeFn* free_val);
void ht_free(ht* ht, FreeFn* free_key, FreeFn* free_val);

typedef struct {
    ht_entry* cur;
    ht_entry* next;
    size_t bucket_idx;
    size_t ht_idx;
    ht* ht;
} ht_iter;

ht_iter ht_iter_new(ht* ht);

void ht_iter_next(ht_iter* iter);

#endif /* __AOC_H__ */
