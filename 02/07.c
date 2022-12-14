#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main() {
  int i = invert(0xff, 3, 4);
  printf("%d\n", i);
  return 0;
}

/* invert: invert n bits from position p */
unsigned invert(unsigned x, int p, int n) {
  return x ^ (~(~0 << n) << (p + 1 - n));
}
