#include "aoc.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char* buf = NULL;
    size_t bytes_read;
    ssize_t read = read_file(NULL, &buf, &bytes_read);
    assert(read != -1);
    int res = day2p2(buf, bytes_read);
    printf("%d\n", res);
    free(buf);
    return 0;
}
