#include <stdio.h>
#include <string.h>

FILE *stdin;
FILE *stdout;
FILE *stderr;

__attribute__((weak)) int __read(int fd, void *buf, int count) {
  return -1;
}

__attribute__((weak)) int __write(int fd, const void *buf, int count) {
  return -1;
}

int fgetc(FILE *stream) {
  char c;
  if (__read(stream->fd, &c, 1) == 1) {
    return c;
  }
  return EOF;
}

int getc(FILE *stream) {
  return fgetc(stream);
}

char *fgets(char *str, int count, FILE *stream) {
  int i;
  for (i = 0; i < count - 1; i++) {
    int c = fgetc(stream);
    if (c == EOF) {
      break;
    }
    str[i] = c;
    if (c == '\n') {
      i++;
      break;
    }
  }
  str[i] = '\0';
  return str;
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
