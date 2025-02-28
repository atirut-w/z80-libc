#include <string.h>

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
