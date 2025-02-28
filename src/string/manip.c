#include <string.h>

char *strcpy(char *dest, const char *src) {
  char *ret = dest;
  while ((*dest++ = *src++));
  return ret;
}

char *strncpy(char *dest, const char *src, size_t count) {
  char *ret = dest;
  size_t i;

  for (i = 0; i < count && (*dest++ = *src++); i++);
  for (; i < count; i++) *dest++ = '\0';

  return ret;
}

char *strcat(char *dest, const char *src) {
  char *ret = dest;

  while (*dest) dest++;
  while ((*dest++ = *src++));

  return ret;
}

char *strncat(char *dest, const char *src, size_t count) {
  char *ret = dest;
  size_t i;

  while (*dest) dest++;
  for (i = 0; i < count && (*dest++ = *src++); i++);
  *dest = '\0';
  
  return ret;
}
