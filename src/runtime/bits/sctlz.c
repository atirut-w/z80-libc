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
