#include <stdio.h>

__attribute__((weak)) int fputc(int ch, FILE *stream) {
  return EOF;
}
