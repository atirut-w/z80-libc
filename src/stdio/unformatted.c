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
  int i = 0;
  int c;

  /* C90 doesn't require parameter validation - undefined behavior if invalid */
  
  /* Read characters until newline, EOF, or count-1 characters read */
  while (i < count - 1) {
    c = fgetc(stream);
    
    /* Check for EOF */
    if (c == EOF) {
      if (i == 0) {
        return NULL;  /* No characters read before EOF */
      }
      break;  /* Some characters read before EOF */
    }
    
    /* Store the character */
    str[i++] = c;
    
    /* Break if newline */
    if (c == '\n') {
      break;
    }
  }

  /* Null-terminate the string */
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
    return 0;  /* Success return value should be non-negative per C standard */
  }
  return EOF;
}

int getchar(void) {
  return getc(stdin);
}

char *gets(char *str) {
  /* C90 implementation: reads until newline or EOF */
  char *p = str;
  int ch;

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
