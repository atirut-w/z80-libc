#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
