__attribute__((naked)) long _land(long a, long b) {
  __asm__(
    "push ix\n"
    "ld ix, 0\n"
    "add ix, sp\n"

    "ld l, (ix + 4)\n"
    "ld h, (ix + 5)\n"
    "ld e, (ix + 6)\n"
    "ld d, (ix + 7)\n"

    "ld a, (ix + 8)\n"
    "and l\n"
    "ld l, a\n"

    "ld a, (ix + 9)\n"
    "and h\n"
    "ld h, a\n"

    "ld a, (ix + 10)\n"
    "and e\n"
    "ld e, a\n"

    "ld a, (ix + 11)\n"
    "and d\n"
    "ld d, a\n"

    "ld sp, ix\n"
    "pop ix\n"
    "ret\n"
  );
}
