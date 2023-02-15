#include "12.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  int i, ts;
  char c;

  if ((i = parsetabstops(argc, argv)) != 0)
    return i;

  i = 1;
  while ((c = getchar()) != EOF) {
    switch (c) {
    case '\t':
      ts = nexttabstop(i);
      if (ts == 0)
        ts = i;
      while (i <= ts) {
        printf(" ");
        i++;
      }
      break;

    case '\n':
      printf("\n");
      i = 1;
      break;

    default:
      printf("%c", c);
      i++;
      break;
    }
  }
}
