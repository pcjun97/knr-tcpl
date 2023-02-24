#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int c;
  int (*fn)(int);

  if (strcmp(*argv, "./lower") == 0)
    fn = &tolower;
  else if (strcmp(*argv, "./upper") == 0)
    fn = &toupper;
  else {
    printf("invalid command: %s\n", *argv);
    return 1;
  }

  while ((c = getchar()) != EOF)
    putchar((*fn)(c));

  return 0;
}
