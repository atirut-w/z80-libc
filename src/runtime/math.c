int _smulu(unsigned int a, unsigned int b) {
  int sign, i;
  unsigned int ua, ub, prod;

  sign = ((a ^ b) < 0);

  ua = (a < 0) ? -a : a;
  ub = (b < 0) ? -b : b;

  prod = 0;

  for (i = 0; i < 16; i++) {
    if (ua & 1) {
      prod += ub;
    }

    ua >>= 1;
    ub <<= 1;
  }

  if (sign) {
    prod = -prod;
  }

  return prod;
}

long _lmulu(unsigned long a, unsigned long b) {
  int sign, i;
  unsigned long ua, ub, prod;

  sign = ((a ^ b) < 0);

  ua = (a < 0) ? -a : a;
  ub = (b < 0) ? -b : b;

  prod = 0;

  for (i = 0; i < 32; i++) {
    if (ua & 1) {
      prod += ub;
    }

    ua >>= 1;
    ub <<= 1;
  }

  if (sign) {
    prod = -prod;
  }

  return prod;
}

int _sdivs(int a, int b) {
  int sign, i;
  unsigned int ua, ub, quot, rem;

  if (b == 0) {
    return 0; /* TODO: Raise exception, somehow */
  }

  sign = ((a ^ b) < 0);

  ua = (a < 0) ? -a : a;
  ub = (b < 0) ? -b : b;

  quot = 0;
  rem = 0;

  for (i = 15; i >= 0; i--) {
    rem = (rem << 1) | ((ua >> i) & 1);

    if (rem >= ub) {
      rem -= ub;
      quot |= (1 << i);
    }
  }

  if (sign) {
    quot = -quot;
  }

  return quot;
}

int _srems(int a, int b) {
  int i;
  unsigned int ua, ub, quot, rem;

  if (b == 0) {
    return 0; /* TODO: Raise exception, somehow */
  }

  ua = (a < 0) ? -a : a;
  ub = (b < 0) ? -b : b;

  quot = 0;
  rem = 0;

  for (i = 15; i >= 0; i--) {
    rem = (rem << 1) | ((ua >> i) & 1);

    if (rem >= ub) {
      rem -= ub;
      quot |= (1 << i);
    }
  }

  if (a < 0) {
    rem = -rem;
  }

  return rem;
}

int _sremu(unsigned int a, unsigned int b) {
  int i;
  unsigned int ua, ub, quot, rem;

  if (b == 0) {
    return 0; /* TODO: Raise exception, somehow */
  }

  ua = a;
  ub = b;

  quot = 0;
  rem = 0;

  for (i = 15; i >= 0; i--) {
    rem = (rem << 1) | ((ua >> i) & 1);

    if (rem >= ub) {
      rem -= ub;
      quot |= (1 << i);
    }
  }

  return rem;
}

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

__attribute__((naked)) long _ladd(long a, long b) {
  __asm__(
    "push ix\n"
    "ld ix, 0\n"
    "add ix, sp\n"

    "ld l, (ix + 4)\n"
    "ld h, (ix + 5)\n"
    "ld e, (ix + 6)\n"
    "ld d, (ix + 7)\n"

    "ld a, (ix + 8)\n"
    "add a, l\n"
    "ld l, a\n"

    "ld a, (ix + 9)\n"
    "adc a, h\n"
    "ld h, a\n"

    "ld a, (ix + 10)\n"
    "adc a, e\n"
    "ld e, a\n"

    "ld a, (ix + 11)\n"
    "adc a, d\n"
    "ld d, a\n"

    "ld sp, ix\n"
    "pop ix\n"
    "ret\n"
  );
}
