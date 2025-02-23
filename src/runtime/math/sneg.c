__attribute__((naked)) int _sneg(int a) {
  __asm__(
    "push ix\n"
    "ld ix, 0\n"
    "add ix, sp\n"

    "ld hl, 0\n"
    "ld e, (ix + 4)\n"
    "ld d, (ix + 5)\n"

    "or a\n"
    "sbc hl, de\n"

    "ld sp, ix\n"
    "pop ix\n"
    "ret\n"
  );
}
