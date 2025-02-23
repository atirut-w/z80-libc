#include <stdio.h>
#include <string.h>
#include <unistd.h>

static FILE __stdin = {0};
static FILE __stdout = {1};
static FILE __stderr = {2};

FILE *stdin = &__stdin;
FILE *stdout = &__stdout;
FILE *stderr = &__stderr;

size_t fread(void *buffer, size_t size, size_t count, FILE *stream) {
  unsigned char *buf = buffer;
  size_t i, j;

  for (i = 0; i < count; i++) {
    for (j = 0; j < size; j++) {
      int c = fgetc(stream);
      if (c == EOF) {
        return i;
      }
      *buf++ = c;
    }
  }

  return i;
}

size_t fwrite(const void *buffer, size_t size, size_t count, FILE *stream) {
  const unsigned char *buf = buffer;
  size_t i, j;

  for (i = 0; i < count; i++) {
    for (j = 0; j < size; j++) {
      if (fputc(*buf++, stream) == EOF) {
        return i;
      }
    }
  }

  return i;
}

int fgetc(FILE *stream) {
  unsigned char c;
  if (read(stream->fd, &c, 1) == 1) {
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

  if (i == 0) {
    return NULL;
  }

  str[i] = '\0';
  return str;
}

int fputc(int ch, FILE *stream) {
  unsigned char c = ch;
  if (write(stream->fd, &c, 1) == 1) {
    return ch;
  }
  return EOF;
}

int putc(int ch, FILE *stream) {
  return fputc(ch, stream);
}

int fputs(const char *str, FILE *stream) {
  int len = strlen(str);
  if (write(stream->fd, str, len) == len) {
    return len;
  }
  return EOF;
}

int getchar(void) {
  return getc(stdin);
}

char *gets(char *str) {
  char *p = str;
  int i, ch;

  ch = getchar();
  while (ch != EOF && ch != '\n') {
    *p++ = ch;
    ch = getchar();
  }

  if (ch == EOF && p == str) {
    return NULL;
  }

  *p = '\0';
  return str;
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
