#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TABSTOP 8
#define MAXTABSTOPS 100

int main(int argc, char *argv[]) {
  int i, j, nspace, ts, tabstops[MAXTABSTOPS];
  char c;

  ts = DEFAULT_TABSTOP;
  if (argc > 1) {
    for (i = 0; i < argc - 1; i++) {
      tabstops[i] = atoi(*++argv);

      if (tabstops[i] <= 0) {
        printf("entab: tab stops cannot be smaller than 1");
        return 1;
      }

      if (i > 0 && tabstops[i] <= tabstops[i - 1]) {
        printf("entab: tab stops must be ascending");
        return 1;
      }
    }

    tabstops[argc - 1] = 0;
    ts = tabstops[0];
  }

  i = j = nspace = 0;
  while (c != EOF) {
    c = getchar();

    if (c == ' ')
      nspace++;

    if (i == ts) {
      if (nspace > 1) {
        printf("\t");
        nspace = (c == ' ') ? 1 : 0;
      }

      if (argc == 1)
        ts = i + (DEFAULT_TABSTOP - (i % DEFAULT_TABSTOP));
      else if (tabstops[j] > 0)
        ts = tabstops[++j];
    }

    if (c != ' ') {
      while (nspace > 0) {
        printf(" ");
        nspace--;
      }
      if (c != EOF)
        printf("%c", c);
    }

    if (c == '\n') {
      i = j = nspace = 0;
      ts = (argc > 1) ? tabstops[0] : DEFAULT_TABSTOP;
    } else {
      i++;
    }
  }

  return 0;
}
