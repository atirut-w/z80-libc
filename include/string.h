#pragma once
#include <stddef.h>

/* String examination */

/* Returns the length of a given string */
size_t strlen(const char *str);

/* Character array manipulation */

/* Fills a buffer with a character */
void *memset(void *dest, int ch, size_t count);

/* Copies one buffer to another */
void *memcpy(void *dest, const void *src, size_t count);
