#include <stdio.h>

int main() {
  int c, p, nspace, tabstop;

  p = 0;
  tabstop = 2;
  while ((c = getchar()) != EOF) {
    if (c == ' ')
      ++nspace;
    else {
      while (nspace > 0) {
        putchar(' ');
        --nspace;
      }
      putchar(c);
    }

    if (p == tabstop - 1 || c == '\n') {
      if (nspace > 1)
        putchar('\t');
      else if (nspace == 1)
        putchar(' ');
      p = 0;
      nspace = 0;
    } else
      ++p;
  }

  return 0;
}
