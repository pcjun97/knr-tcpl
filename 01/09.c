#include <stdio.h>

int main() {
  int c, l;
  l = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ')
      if (c != l)
        putchar(c);

    if (c != ' ')
      putchar(c);

    l = c;
  }

  return 0;
}
