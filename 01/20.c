#include <stdio.h>

int main() {
  int c, p, i, tabstop;

  p = 0;
  tabstop = 8;
  while ((c = getchar()) != EOF) {
    if (c == '\t')
      for (i = tabstop - p; i > 0; --i)
        putchar(' ');
    else
      putchar(c);

    if (c == '\n' || p >= tabstop - 1)
      p = 0;
    else
      ++p;
  }

  return 0;
}
