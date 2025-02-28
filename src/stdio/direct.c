#include <stdio.h>

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
