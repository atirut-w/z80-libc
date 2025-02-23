#include <unistd.h>

extern char __heap_start[];
extern char __heap_end[];
static void *heap_ptr = __heap_start;

int brk(void *addr) {
  if ((char*)addr < __heap_start || (char*)addr > __heap_end) {
    return -1;
  }

  heap_ptr = addr;
  return 0;
}

void *sbrk(intptr_t increment) {
  void *prev_ptr = heap_ptr;

  if (((char*)heap_ptr + increment) > __heap_end) {
    return (void *)-1;
  }

  heap_ptr = (char*)heap_ptr + increment;
  return prev_ptr;
}
