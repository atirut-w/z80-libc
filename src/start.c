#include <stdlib.h>

int __libc_start_main(int (*main)(int, char **, char **), int argc, char **argv, void (*init)(void), void (*fini)(void), void (*rtld_fini)(void), void *stack_end) {
  char **environ = argv + argc + 1;
  
  if (rtld_fini) {
    atexit(rtld_fini);
  }
  if (fini) {
    atexit(fini);
  }

  if (init) {
    init();
  }

  exit(main(argc, argv, environ));
}
