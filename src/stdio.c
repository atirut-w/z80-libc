#include <stdio.h>

FILE *stdin;
FILE *stdout;
FILE *stderr;

__attribute__((weak)) int fputc(int ch, FILE *stream) {
  return EOF;
}

int putc(int ch, FILE *stream) {
  return fputc(ch, stream);
}

int fputs(const char *str, FILE *stream) {
  while (*str) {
    if (fputc(*str++, stream) == EOF) {
      return EOF;
    }
  }
  return 0;
}

int putchar(int ch) {
  return putc(ch, stdout);
}

int puts(const char *str) {
  if (fputs(str, stdout) == EOF) {
    return EOF;
  }
  return putc('\n', stdout);
}
