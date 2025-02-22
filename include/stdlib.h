#pragma once
#include <stddef.h>

#define EXIT_SUCCESS (0)
#define EXIT_FAILURE (1)

/* Causes normal program termination with cleaning up */
void exit(int status);

/* Registers a function to be called on `exit()` invocation */
int atexit(void (*func)(void));

/* Allocates memory */
void *malloc(size_t size);

/* Allocates and zeroes memory */
void *calloc(size_t num, size_t size);

/* Expands previously allocated memory block */
void *realloc(void *ptr, size_t new_size);

/* Deallocates previously allocated memory */
void free(void *ptr);
