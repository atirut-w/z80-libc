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
