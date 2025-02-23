__attribute__((naked)) int _sand(int a, int b) {
  __asm__(
    "push ix\n"
    "ld ix, 0\n"
    "add ix, sp\n"

    "ld l, (ix + 4)\n"
    "ld h, (ix + 5)\n"
    "ld e, (ix + 6)\n"
    "ld d, (ix + 7)\n"

    "ld a, l\n"
    "and e\n"
    "ld l, a\n"
    "ld a, h\n"
    "and d\n"
    "ld h, a\n"

    "ld sp, ix\n"
    "pop ix\n"
    "ret\n"
  );
}
