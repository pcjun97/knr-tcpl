#include <stdio.h>
#define swap(t, x, y)                                                          \
  {                                                                            \
    t tmp = x;                                                                 \
    x = y;                                                                     \
    y = tmp;                                                                   \
  }

int main() {
  int tmp, a, b;
  tmp = 12345;
  a = 678;
  b = 901;
  printf("tmp: %d\ta: %d\tb: %d\n", tmp, a, b);
  swap(int, a, b);
  printf("tmp: %d\ta: %d\tb: %d\n", tmp, a, b);
  return 0;
}
