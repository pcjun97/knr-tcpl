#include <stdio.h>

int bitcount(unsigned x);

int main() {
  int i = bitcount(7);
  printf("%d\n", i);
  return 0;
}

/* bitcount: count 1 bits in x */
int bitcount(unsigned x) {
  int b;

  /* if the rightmost bit of x is 1, x - 1 flip the bit to 0
   * otherwise the rightmost 1-bit will be flipped to 0
   * and all remaining 0-bits will be flipped to 1
   * the & operation will flip the rightmost 1-bit,
   * while leaving the 0-bits untouched */
  for (b = 0; x != 0; x &= (x - 1))
    b++;

  return b;
}
