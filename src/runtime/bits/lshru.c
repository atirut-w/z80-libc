__attribute__((naked)) long _lshru(unsigned long a, unsigned int b) {
  __asm__(
    "push ix\n"
    "ld ix, 0\n"
    "add ix, sp\n"

    "ld l, (ix + 4)\n"
    "ld h, (ix + 5)\n"
    "ld e, (ix + 6)\n"
    "ld d, (ix + 7)\n"
    "ld b, (ix + 8)\n"

    "0:\n"
    "ld a, b\n"
    "or a\n"
    "jr z, 1f\n"
    "srl d\n"
    "rr e\n"
    "rr h\n"
    "rr l\n"
    "djnz 0b\n"
    "1:\n"

    "ld sp, ix\n"
    "pop ix\n"
    "ret\n"
  );
}
