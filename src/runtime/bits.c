__attribute__((naked)) int _sshl(int a, int b) {
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
    "sla l\n"
    "rl h\n"
    "djnz 0b\n"
    "1:\n"

    "ld sp, ix\n"
    "pop ix\n"
    "ret\n"
  );
}

__attribute__((naked)) int _sshr(int a, int b) {
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
    "sra h\n"
    "srl l\n"
    "djnz 0b\n"
    "1:\n"

    "ld sp, ix\n"
    "pop ix\n"
    "ret\n"
  );
}

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

__attribute__((naked)) int _sctlz(int a) {
  __asm__(
    "push ix\n"
    "ld ix, 0\n"
    "add ix, sp\n"

    "ld b, 0\n"
    "ld l, (ix + 4)\n"
    "ld h, (ix + 5)\n"
    
    "0:\n"
    "sla h\n"
    "jr c, 1f\n"
    "rl l\n" /* Avoid discarding the carry flag from `sla h` */
    "inc b\n"
    "ld a, b\n"
    "cp 16\n"
    "jr nz, 0b\n"

    "1:\n"
    "ld l, b\n"
    "ld h, 0\n"

    "ld sp, ix\n"
    "pop ix\n"
    "ret\n"
  );
}
