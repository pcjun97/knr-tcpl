#include <limits.h>
#include <stdio.h>

int main() {
  printf("bits in a char: %d\n", CHAR_BIT);
  printf("maximum value of char: %d\n", CHAR_MAX);
  printf("minimum value of char: %d\n", CHAR_MIN);
  printf("maximum value of int: %d\n", INT_MAX);
  printf("minimum value of int: %d\n", INT_MIN);
  printf("maximum value of long: %ld\n", LONG_MAX);
  printf("minimum value of long: %ld\n", LONG_MIN);
  printf("maximum value of signed char: %d\n", SCHAR_MAX);
  printf("minimum value of signed char: %d\n", SCHAR_MIN);
  printf("maximum value of short: %d\n", SHRT_MAX);
  printf("minimum value of short: %d\n", SHRT_MIN);
  printf("maximum value of unsigned char: %u\n", UCHAR_MAX);
  printf("maximum value of unsigned int: %u\n", UINT_MAX);
  printf("maximum value of unsigned long: %lu\n", ULONG_MAX);
  printf("maximum value of unsigned short: %u\n", USHRT_MAX);
  return 0;
}
