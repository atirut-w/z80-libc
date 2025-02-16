#include <stdio.h>
#include <string.h>

FILE *stdin;
FILE *stdout;
FILE *stderr;

__attribute__((weak)) int __write(int fd, const void *buf, int count) {
  return -1;
}

int fputc(int ch, FILE *stream) {
  char c = ch;
  if (__write(stream->fd, &c, 1) == 1) {
    return ch;
  }
  return EOF;
}

int putc(int ch, FILE *stream) {
  return fputc(ch, stream);
}

int fputs(const char *str, FILE *stream) {
  int len = strlen(str);
  if (__write(stream->fd, str, len) == len) {
    return len;
  }
  return EOF;
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
