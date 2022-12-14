#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main() {
  int i;
  i = setbits(0xFF, 5, 4, 0xF0);
  printf("%d\n", i);
  return 0;
}

/* setbits: set n bits from poition p of x to the rightmost n bits of y */
unsigned setbits(unsigned x, int p, int n, unsigned y) {
  int mask = ~(~0 << n);
  int shift = p + 1 - n;
  y = (y & mask) << shift;

  mask = ~(mask << shift);
  return (x & mask) | y;
}
