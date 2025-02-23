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
