#pragma once
#include <stdint.h>
#include <sys/types.h>

/* Memory management */

/* Set program break */
int brk(void *addr);

/* Move program break */
void *sbrk(intptr_t increment);

/* Filesystem operations */

/* Read from a file descriptor */
ssize_t read(int fd, void *buf, size_t count);

/* Write to a file descriptor */
ssize_t write(int fd, const void *buf, size_t count);

/* Process control */

/* Terminate process */
void _exit(int status);
