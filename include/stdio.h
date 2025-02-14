#pragma once

#define EOF (-1)

typedef struct {
  void *data; /* Empty struct is a GNU extension */
} FILE;

/* Unformatted I/O */

/* Writes a character to a file stream */
int fputc(int ch, FILE *stream);
