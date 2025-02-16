#include <string.h>

size_t strlen(const char *str) {
  size_t len = 0;
  while (*str++) {
    len++;
  }
  return len;
}

void *memset(void *dest, int ch, size_t count) {
  unsigned char *d = dest;
  while (count--) {
    *d++ = ch;
  }
  return dest;
}

void *memcpy(void *dest, const void *src, size_t count) {
  unsigned char *d = dest;
  const unsigned char *s = src;
  while (count--) {
    *d++ = *s++;
  }
  return dest;
}
