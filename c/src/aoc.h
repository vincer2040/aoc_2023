#ifndef __AOC_H__

#define __AOC_H__

#include <stddef.h>
#include <sys/types.h>

ssize_t read_file(const char* path, char** buf, size_t* bytes_read);

#endif /* __AOC_H__ */
