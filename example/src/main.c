#include <stdio.h>
#include <stddef.h>

void puthex(unsigned int n) {
  char *hex = "0123456789abcdef";
  
  if (n >= 16) {
    puthex(n / 16);
  }
  putchar(hex[n % 16]);
}

int main(void) {
  char buf[64];
  
  fputs("Type something: ", stdout);
  fgets(buf, sizeof(buf), stdin);
  fputs("You typed: ", stdout);
  fputs(buf, stdout);
  fputs("\n", stdout);

  return 0;
}
