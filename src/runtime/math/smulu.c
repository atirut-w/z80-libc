#include <limits.h>

int _smulu(unsigned int a, unsigned int b) {
  int sign, i;
  unsigned int ua, ub, prod;

  /* Fix the function parameters - this is signed multiplication of unsigned values */
  int sa = (int)a;
  int sb = (int)b;
  
  sign = ((sa ^ sb) < 0);

  /* Be careful with INT_MIN, can't just negate it */
  if (sa == INT_MIN) {
    ua = (unsigned int)INT_MAX + 1;
  } else {
    ua = (sa < 0) ? -sa : sa;
  }

  if (sb == INT_MIN) {
    ub = (unsigned int)INT_MAX + 1;
  } else {
    ub = (sb < 0) ? -sb : sb;
  }

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
