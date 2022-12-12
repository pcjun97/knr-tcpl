#include <stdio.h>

#define MAX_LENGTH 10

int main() {
  int c, i, j, n;
  int length[MAX_LENGTH + 1];

  for (i = 0; i < MAX_LENGTH + 1; ++i)
    length[i] = 0;

  c = n = 0;
  while (c != EOF) {
    c = getchar();
    if (c == ' ' || c == '\t' || c == '\n' || c == EOF) {
      if (n > MAX_LENGTH) {
        ++length[MAX_LENGTH];
      } else if (n > 0) {
        ++length[n - 1];
      }
      n = 0;
    } else {
      ++n;
    }
  }

  /* horizontal histogram */
  for (i = 0; i < MAX_LENGTH; ++i) {
    printf("%4d |", i + 1);
    for (j = 0; j < length[i]; j++) {
      printf("*");
    }
    printf("\n");
  }

  printf(" >10 |");
  for (j = 0; j < length[MAX_LENGTH]; j++) {
    printf("*");
  }
  printf("\n");

  printf("\n");

  /* vertical histogram */
  j = 0;
  for (i = 0; i < MAX_LENGTH + 1; ++i) {
    if (length[i] > j)
      j = length[i];
  }

  while (j > 0) {
    printf("%4d |", j);
    for (i = 0; i < MAX_LENGTH + 1; ++i)
      if (length[i] >= j)
        printf(" * ");
      else
        printf("   ");
    printf("\n");
    --j;
  }

  printf("     +");
  for (i = 0; i < MAX_LENGTH + 1; ++i)
    printf("---");
  printf("\n");

  printf("     ");
  for (i = 0; i < MAX_LENGTH; ++i)
    printf("%3d", i + 1);
  printf(" >10\n");

  return 0;
}
