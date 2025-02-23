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
