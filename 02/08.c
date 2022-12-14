#include <stdio.h>

unsigned rightrot(unsigned x, int n);

int main() {
  int i = rightrot(0x0F, 4);
  printf("%u\n", i);
  return 0;
}

/* rightrot: rotate to the right by n positions */
unsigned rightrot(unsigned x, int n) {
  while (n-- > 0)
    if ((x & 1) == 1)
      x = ~(~x >> 1);
    else
      x = x >> 1;
  return x;
}
