#include <limits.h>

int _srems(int a, int b) {
  int i;
  unsigned int ua, ub, quot, rem;

  /* Division by zero is undefined in C90, so we can omit the check */

  /* Be careful with INT_MIN, can't just negate it */
  if (a == INT_MIN) {
    ua = (unsigned int)INT_MAX + 1;
  } else {
    ua = (a < 0) ? -a : a;
  }

  if (b == INT_MIN) {
    ub = (unsigned int)INT_MAX + 1;
  } else {
    ub = (b < 0) ? -b : b;
  }

  quot = 0;
  rem = 0;

  for (i = 15; i >= 0; i--) {
    rem = (rem << 1) | ((ua >> i) & 1);

    if (rem >= ub) {
      rem -= ub;
      quot |= (1 << i);
    }
  }

  /* The sign of the remainder follows the sign of the dividend */
  if (a < 0) {
    rem = -rem;
  }

  return rem;
}
