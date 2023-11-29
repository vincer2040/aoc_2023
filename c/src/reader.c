#include <memory.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define BUF_INITIAL_CAP 32

ssize_t read_file(const char* path, char** buf, size_t* bytes_read) {
    size_t ins = 0, cap = BUF_INITIAL_CAP;
    FILE* file;
    int ch;

    if (path == NULL) {
        file = stdin;
    } else {
        file = fopen(path, "r");
    }

    if (file == NULL) {
        return -1;
    }

    *buf = calloc(cap, sizeof **buf);
    if (*buf == NULL) {
        return -1;
    }

    while ((ch = fgetc(file)) != EOF) {
        if (ins == (cap - 1)) {
            void* tmp;
            cap <<= 1;
            tmp = realloc(*buf, cap);
            if (tmp == NULL) {
                return -1;
            }
            *buf = tmp;
            memset(&((*buf)[ins]), 0, cap - ins);
        }
        (*buf)[ins] = ch;
        ins++;
    }

    fclose(file);
    *bytes_read = ins;
    return ins;
}
