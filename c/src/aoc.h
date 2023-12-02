#ifndef __AOC_H__

#define __AOC_H__

#include <stddef.h>
#include <sys/types.h>

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
void line_iter_next(line_iter* iter);

ssize_t read_file(const char* path, char** buf, size_t* bytes_read);

int day1p1(const char* input, size_t input_len);
int day1p2(const char* input, size_t input_len);

int day2p1(const char* input, size_t input_len);
int day2p2(const char* input, size_t input_len);

#endif /* __AOC_H__ */
