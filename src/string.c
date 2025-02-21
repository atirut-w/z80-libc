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

__attribute__((naked)) size_t strlen(const char *str) {
  __asm__(
    "push ix\n"
    "ld ix, 0\n"
    "add ix, sp\n"

    "ld l, (ix + 4)\n"
    "ld h, (ix + 5)\n"
    "ld bc, 0\n"

    "0:\n"
    "ld a, (hl)\n"
    "or a\n"
    "jr z, 1f\n"
    "inc hl\n"
    "inc bc\n"
    "jr 0b\n"

    "1:\n"
    "ld l, c\n"
    "ld h, b\n"

    "ld sp, ix\n"
    "pop ix\n"
    "ret\n"
  );
}

__attribute__((naked)) void *memset(void *dest, int ch, size_t count) {
  __asm__(
    "push ix\n"
    "ld ix, 0\n"
    "add ix, sp\n"

    /* Load count and check for zero */
    "ld c, (ix + 8)\n"
    "ld b, (ix + 9)\n"
    "ld a, b\n"
    "or c\n"
    "jr z, 1f\n"

    /* Load other arguments */
    "ld l, (ix + 4)\n"
    "ld h, (ix + 5)\n"
    "ld a, (ix + 6)\n"

    /* Setup */
    "ld (hl), a\n"
    "ld e, l\n"
    "ld d, h\n"
    "inc de\n"
    "dec bc\n"
    
    /* Fill the rest */
    "ldir\n"

    /* Return a copy of the destination */
    "1:\n"
    "ld l, (ix + 4)\n"
    "ld h, (ix + 5)\n"

    "ld sp, ix\n"
    "pop ix\n"
    "ret\n"
  );
}

__attribute__((naked)) void *memcpy(void *dest, const void *src, size_t count) {
  __asm__(
    "push ix\n"
    "ld ix, 0\n"
    "add ix, sp\n"

    /* Load count and check for zero */
    "ld c, (ix + 8)\n"
    "ld b, (ix + 9)\n"
    "ld a, b\n"
    "or c\n"
    "jr z, 1f\n"

    /* Load other arguments */
    "ld e, (ix + 4)\n"
    "ld d, (ix + 5)\n"
    "ld l, (ix + 6)\n"
    "ld h, (ix + 7)\n"

    /* Copy */
    "ldir\n"

    /* Return a copy of the destination */
    "1:\n"
    "ld l, (ix + 4)\n"
    "ld h, (ix + 5)\n"

    "ld sp, ix\n"
    "pop ix\n"
    "ret\n"
  );
}
