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

__attribute__((naked)) long _lshl(long a, long b) {
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
    "sla l\n"
    "rl h\n"
    "rl e\n"
    "rl d\n"
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
    "rr l\n"
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

__attribute__((naked)) int _sor(int a, int b) {
  __asm__(
    "push ix\n"
    "ld ix, 0\n"
    "add ix, sp\n"

    "ld l, (ix + 4)\n"
    "ld h, (ix + 5)\n"
    "ld e, (ix + 6)\n"
    "ld d, (ix + 7)\n"

    "ld a, l\n"
    "or e\n"
    "ld l, a\n"
    "ld a, h\n"
    "or d\n"
    "ld h, a\n"

    "ld sp, ix\n"
    "pop ix\n"
    "ret\n"
  );
}

__attribute__((naked)) int _sxor(int a, int b) {
  __asm__(
    "push ix\n"
    "ld ix, 0\n"
    "add ix, sp\n"

    "ld l, (ix + 4)\n"
    "ld h, (ix + 5)\n"
    "ld e, (ix + 6)\n"
    "ld d, (ix + 7)\n"

    "ld a, l\n"
    "xor e\n"
    "ld l, a\n"
    "ld a, h\n"
    "xor d\n"
    "ld h, a\n"
    
    "ld sp, ix\n"
    "pop ix\n"
    "ret\n"
  );
}

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
