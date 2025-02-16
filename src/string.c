#include <string.h>

size_t strlen(const char *str) {
  size_t len = 0;
  while (*str++) {
    len++;
  }
  return len;
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
