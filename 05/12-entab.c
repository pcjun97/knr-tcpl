#include "12.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  int i, nspace, ts;
  char c;

  if ((i = parsetabstops(argc, argv)) != 0)
    return i;

  ts = nexttabstop(0);
  i = nspace = 0;
  while (c != EOF) {
    c = getchar();

    if (c == ' ')
      nspace++;

    if (i == ts) {
      if (nspace > 1) {
        printf("\t");
        nspace = (c == ' ') ? 1 : 0;
      }

      ts = nexttabstop(i + 1);
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
      i = nspace = 0;
      ts = nexttabstop(0);
    } else
      i++;
  }

  return 0;
}
