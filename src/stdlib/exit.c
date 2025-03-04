#include <stdlib.h>
#include <unistd.h>

#define MAX_ATEXIT 32

static void (*atexit_funcs[MAX_ATEXIT])(void);
static int atexit_count;

void exit(int status) {
  int i = 0;
  
  for (i = atexit_count - 1; i >= 0; i--) {
    atexit_funcs[i]();
  }
  _exit(status);
}

int atexit(void (*func)(void)) {
  if (atexit_count < MAX_ATEXIT) {
    atexit_funcs[atexit_count++] = func;
    return 0;
  }
  return 1;
}
