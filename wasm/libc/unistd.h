#ifndef _UNISTD_H
#define _UNISTD_H

#include <stdint.h>
#include <stddef.h>

typedef int32_t ssize_t;

ssize_t read(int fd, void *buf, size_t size);
ssize_t write(int fd, const void *buf, size_t size);

#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#endif
