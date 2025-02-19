#pragma once
#include <stddef.h>

/* String manipulation */

/* Copies one string to another */
char *strcpy(char *dest, const char *src);

/* Copies a certain amount of characters from one string to another */
char *strncpy(char *dest, const char *src, size_t count);

/* Concatenates two strings */
char *strcat(char *dest, const char *src);

/* Concatenates a certain amount of characters of two strings */
char *strncat(char *dest, const char *src, size_t count);

/* String examination */

/* Returns the length of a given string */
size_t strlen(const char *str);

/* Character array manipulation */

/* Fills a buffer with a character */
void *memset(void *dest, int ch, size_t count);

/* Copies one buffer to another */
void *memcpy(void *dest, const void *src, size_t count);
