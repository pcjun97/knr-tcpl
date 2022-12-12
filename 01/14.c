#include <stdio.h>

#define FIRST_CHAR '!'
#define LAST_CHAR '~'

int main() {
  int count[LAST_CHAR - FIRST_CHAR + 1];
  int n, c, i, j, max;

  n = LAST_CHAR - FIRST_CHAR + 1;
  for (i = 0; i < n; ++i)
    count[i] = 0;

  while ((c = getchar()) != EOF) {
    if (c >= FIRST_CHAR || c <= LAST_CHAR) {
      ++count[c - FIRST_CHAR];
    }
  }

  max = 0;
  for (i = 0; i < n; ++i) {
    if (count[i] > max)
      max = count[i];
  }

  /* horizontal histogram */
  for (i = 0; i < n; ++i)
    if (count[i] > 0) {
      printf(" ");
      putchar(i + FIRST_CHAR);
      printf(" |");
      for (j = 0; j < count[i]; j++) {
        printf("*");
      }
      printf("\n");
    }

  printf("   +");
  for (i = 0; i < max || i - max > 10; i = i + 10)
    for (j = 0; j < 10; ++j)
      printf("-");
  printf("\n");

  printf("   0");
  for (i = 0; i < max || i - max > 10; i = i + 10)
    printf("%10d", i + 10);
  printf("\n");

  printf("\n");

  /* vertical histogram */
  for (j = max; j > 0; --j) {
    printf("%4d |", j);
    for (i = 0; i < n; ++i)
      if (count[i] >= j)
        printf("*");
      else if (count[i] > 0)
        printf(" ");
    printf("\n");
  }

  printf("     +");
  for (i = 0; i < n; ++i)
    if (count[i] > 0)
      printf("-");
  printf("\n");

  printf("      ");
  for (i = 0; i < n; ++i)
    if (count[i] > 0) {
      putchar(i + FIRST_CHAR);
    }
  printf("\n");

  return 0;
}
