#include "aoc.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char* buf = NULL;
    size_t bytes_read;
    ssize_t read = read_file(NULL, &buf, &bytes_read);
    if (read == -1) {
        return 1;
    }
    uint64_t res = day11p2(buf, bytes_read);
    printf("%lu\n", res);
    free(buf);
    return 0;
}
