#include <stdio.h>
#include <stdlib.h>

/* ----------------------------------------------------------------------------
 * Output Routines
 * -------------------------------------------------------------------------- */

/* Writes an unsigned integer in hexadecimal */
void puthex(unsigned int n) {
  const char *hex = "0123456789abcdef";

  if (n >= 16) {
    puthex(n >> 4);
  }
  putchar(hex[n & 0xF]);
}

/* Writes a signed integer in decimal */
void putint(int n) {
  if (n < 0) {
    putchar('-');
    n = -n;
  }
  if (n >= 10) {
    putint(n / 10);
  }
  putchar('0' + (n % 10));
}

/* Writes a null-terminated string */
void putstr(const char *s) {
  while (*s) {
    putchar(*s++);
  }
}

/* Writes a single character followed by a newline */
void putline(const char *s) {
  putstr(s);
  putchar('\n');
}

/* ----------------------------------------------------------------------------
 * Test Framework
 * -------------------------------------------------------------------------- */

static int totalTests = 0;
static int passedTests = 0;

/* Report the result of a single test */
void reportTest(const char* testName, int condition) {
  totalTests++;
  if (condition) {
    passedTests++;
    putstr("PASS: ");
  } else {
    putstr("FAIL: ");
  }
  putstr(testName);
  putchar('\n');
}

/* ----------------------------------------------------------------------------
 * Test Cases
 * -------------------------------------------------------------------------- */

/* Test malloc: Basic allocation and read/write */
void test_malloc(void) {
  putline("Running test_malloc...");

  /* 1) Allocate 10 bytes. */
  {
    char *p = (char *)malloc(10);
    reportTest("malloc(10) returns non-NULL", p != NULL);
    if (p != NULL) {
      /* 2) Write a value and read it back. */
      p[0] = 42;
      p[1] = 99;
      reportTest("Can write/read single byte", (p[0] == 42));
      reportTest("Can write/read another byte", (p[1] == 99));
      free(p);
    }
  }

  /* 2) malloc(0) is implementation-dependent; test it doesn't crash. */
  {
    char *p = (char *)malloc(0);
    /* C standard: malloc(0) can return NULL or a valid pointer. We just check no crash. */
    reportTest("malloc(0) didn't crash", 1 /* always pass if we got here */);
    free(p);
  }
}

/* Test calloc: Zero-initialization and read/write */
void test_calloc(void) {
  putline("Running test_calloc...");

  /* 1) Allocate an array of 5 ints. */
  {
    int i;
    int *arr = (int *)calloc(5, sizeof(int));
    reportTest("calloc(5, sizeof(int)) returns non-NULL", arr != NULL);
    if (arr != NULL) {
      /* 2) Check zero-initialization. */
      int allZero = 1;
      for (i = 0; i < 5; i++) {
        if (arr[i] != 0) {
          allZero = 0;
          break;
        }
      }
      reportTest("Memory is zero-initialized", allZero);

      /* 3) Write and read values */
      for (i = 0; i < 5; i++) {
        arr[i] = i * 10;
      }
      {
        int correct = 1;
        for (i = 0; i < 5; i++) {
          if (arr[i] != i * 10) {
            correct = 0;
            break;
          }
        }
        reportTest("Can write/read array elements", correct);
      }
      free(arr);
    }
  }
}

/* Test realloc: Growing and shrinking */
void test_realloc(void) {
  putline("Running test_realloc...");

  /* 1) Start with a small allocation */
  {
    int i;
    int *arr = (int *)malloc(3 * sizeof(int));
    reportTest("malloc(3 * sizeof(int)) returns non-NULL", arr != NULL);
    if (arr != NULL) {
      for (i = 0; i < 3; i++) {
        arr[i] = i + 1;  /* 1,2,3 */
      }

      /* 2) Grow the allocation to hold 6 ints */
      arr = (int *)realloc(arr, 6 * sizeof(int));
      reportTest("realloc() to bigger size returns non-NULL", arr != NULL);
      if (arr != NULL) {
        /* Old data should still be there */
        int dataPreserved = 1;
        for (i = 0; i < 3; i++) {
          if (arr[i] != i + 1) {
            dataPreserved = 0;
            break;
          }
        }
        reportTest("Old data preserved after growing", dataPreserved);

        /* Fill the new slots */
        for (i = 3; i < 6; i++) {
          arr[i] = i + 1; /* 4,5,6 */
        }

        /* 3) Shrink the allocation back down */
        arr = (int *)realloc(arr, 4 * sizeof(int));
        reportTest("realloc() to smaller size returns non-NULL", arr != NULL);

        if (arr != NULL) {
          /* Data up to the new size should be preserved */
          int correct = 1;
          for (i = 0; i < 4; i++) {
            /* We originally wrote i+1 in the bigger array */
            if (arr[i] != i + 1) {
              correct = 0;
              break;
            }
          }
          reportTest("Old data preserved after shrinking", correct);
          free(arr);
        }
      }
    }
  }
}

/* Test free: Basic test (there is limited valid behavior to check) */
void test_free_func(void) {
  putline("Running test_free_func...");

  /* 1) Allocate and free. If we don't crash, it's a pass. */
  {
    char *p = (char *)malloc(50);
    free(p);
    reportTest("free() didn't crash after allocation", 1 /* pass */);

    /*
     * We won't test double-free since that's undefined behavior.
     * We also won't test usage after free, as that too is undefined.
     */
  }
}

/* ----------------------------------------------------------------------------
 * Main
 * -------------------------------------------------------------------------- */

int main(void) {
  test_malloc();
  test_calloc();
  test_realloc();
  test_free_func();

  putstr("Passed ");
  putint(passedTests);
  putstr(" of ");
  putint(totalTests);
  putstr(" tests.\n");

  return 0;
}
