#include <ctype.h>
#include <stdio.h>

int main() {
  int c;

  while ((c = getchar()) != EOF) {
    if (isgraph(c) || isspace(c))
      putchar(c);
    else
      printf("\\%03o", c);
  }

  return 0;
}
