int _smulu(int a, int b) {
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
