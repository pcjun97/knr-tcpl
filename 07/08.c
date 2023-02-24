#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *fp;
  char *prog = argv[0];
  char c;
  int pageno = 1;

  while (--argc > 0) {
    if ((fp = fopen(*++argv, "r")) == NULL) {
      fprintf(stderr, "%s: can't open %s\n", prog, *argv);
      exit(1);
    }

    if (pageno > 1)
      printf("\n\n");
    printf("p%d - %s\n", pageno++, *argv);

    while ((c = getc(fp)) != EOF)
      putc(c, stdout);
  }
}
