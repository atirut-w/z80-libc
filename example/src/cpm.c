#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char iqueue[128];
int ihead = 0;
int itail = 0;

int queue_empty(void) {
  return ihead == itail;
}

int queue_full(void) {
  return (ihead + 1) % sizeof(iqueue) == itail;
}

void enqueue(char ch) {
  if (!queue_full()) {
    iqueue[ihead] = ch;
    ihead = (ihead + 1) % sizeof(iqueue);
  }
}

char dequeue(void) {
  char ch = iqueue[itail];
  itail = (itail + 1) % sizeof(iqueue);
  return ch;
}

FILE cpm_in;
FILE cpm_out;

__attribute__((naked)) int bdos(int func, int de) {
  __asm__(
    "push ix\n"
    "ld ix, 0\n"
    "add ix, sp\n"

    "ld c, (ix + 4)\n"
    "ld e, (ix + 6)\n"
    "ld d, (ix + 7)\n"
    "call 5\n"

    "ld sp, ix\n"
    "pop ix\n"
    "ret\n"
  );
}

int __read(int fd, void *buf, unsigned int count) {
  if (fd == 0) {
    int i = 0;
    char ch;

    while (!queue_empty() && i < count) {
      ch = dequeue();
      ((char *)buf)[i++] = ch;
    }

    if (i == count) {
      return i;
    }

    do {
      ch = bdos(1, 0);
      if (ch == '\r') {
        ch = '\n';
        bdos(2, ch);
      }

      if (i < count) {
        ((char *)buf)[i++] = ch;
      } else if (!queue_full()) {
        enqueue(ch);
      }
    } while (ch != '\n');

    return i;
  } else if (fd != 1 && fd != 2) {
    return -1; /* TODO: Implement file I/O */
  }

  return -1;
}

int __write(int fd, const void *buf, unsigned int count) {
  if (fd == 1 || fd == 2) {
    int i;

    for (i = 0; i < count; i++) {
      bdos(2, ((const char *)buf)[i]);
    }

    return i;
  } else if (fd != 0) {
    return -1; /* TODO: Implement file I/O */
  }

  return -1;
}

void __exit(int status) {
  bdos(0, 0);
}

extern char __data_start[];
extern char __data_end[];
extern char __data_load[];
extern char __bss_start[];
extern char __bss_end[];

int main(int argc, char **argv);
char *argv[] = {0};

__attribute__((section(".header"))) void start(void) {
  memcpy(__data_start, __data_load, __data_end - __data_start);
  memset(__bss_start, 0, __bss_end - __bss_start);

  exit(main(0, argv));
}
