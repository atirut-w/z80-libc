__attribute__((naked)) int _sshru(unsigned int a, unsigned int b) {
  __asm__(
    "push ix\n"
    "ld ix, 0\n"
    "add ix, sp\n"

    "ld l, (ix + 4)\n"
    "ld h, (ix + 5)\n"
    "ld b, (ix + 6)\n"

    "0:\n"
    "ld a, b\n"
    "or a\n"
    "jr z, 1f\n"
    "srl h\n"
    "rr l\n"
    "djnz 0b\n"
    "1:\n"

    "ld sp, ix\n"
    "pop ix\n"
    "ret\n"
  );
}
