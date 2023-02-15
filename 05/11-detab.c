#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TABSTOP 8
#define MAXTABSTOPS 100

int main(int argc, char *argv[]) {
  int i, j, ts, tabstops[MAXTABSTOPS];
  char c;

  if (argc > 1) {
    for (i = 0; i < argc - 1; i++) {
      tabstops[i] = atoi(*++argv);

      if (tabstops[i] <= 0) {
        printf("detab: tab stops cannot be smaller than 1");
        return 1;
      }

      if (i > 0 && tabstops[i] <= tabstops[i - 1]) {
        printf("detab: tab stops must be ascending");
        return 1;
      }
    }
    tabstops[argc - 1] = 0;
  }

  i = 1;
  j = 0;
  while ((c = getchar()) != EOF) {
    switch (c) {
    case '\t':
      while (tabstops[j] > 0 && tabstops[j] < i)
        j++;

      if (argc == 1)
        ts = i + (DEFAULT_TABSTOP - (i % DEFAULT_TABSTOP));
      else if (tabstops[j] == 0)
        ts = i;
      else
        ts = tabstops[j];

      while (i <= ts) {
        printf(" ");
        i++;
      }
      break;

    case '\n':
      printf("\n");
      j = 0;
      i = 1;
      break;

    default:
      printf("%c", c);
      i++;
      break;
    }
  }

  return 0;
}
