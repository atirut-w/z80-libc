#pragma once
#include <stddef.h>

/* Integer expression of type `int` and a negative value */
#define EOF (-1)

typedef struct {
  int fd;
} FILE;

/* Expression of type `FILE *` associated with the input stream */
extern FILE *stdin;
/* Expression of type `FILE *` associated with the output stream */
extern FILE *stdout;
/* Expression of type `FILE *` associated with the error output stream */
extern FILE *stderr;

/* Direct I/O */

/* Reads from a file */
size_t fread(void *buffer, size_t size, size_t count, FILE *stream);

/* Writes to a file */
size_t fwrite(const void *buffer, size_t size, size_t count, FILE *stream);

/* Unformatted I/O */

/* Gets a character from a file stream */
int fgetc(FILE *stream);
int getc(FILE *stream);

/* Gets a character string from a file stream */
char *fgets(char *str, int count, FILE *stream);

/* Writes a character to a file stream */
int fputc(int ch, FILE *stream);
int putc(int ch, FILE *stream);

/* Writes a character string to a file stream */
int fputs(const char *str, FILE *stream);

/* Writes a character to `stdout` */
int putchar(int ch);

/* Writes a character string to `stdout` */
int puts(const char *str);
