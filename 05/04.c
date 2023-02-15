#include <stdio.h>

int strend(char *, char *);

int main() {
  char line[] = "hello world!";
  int b;
  b = strend(line, "world!");
  printf("%d\n", b);
  b = strend(line, "test");
  printf("%d\n", b);
  return 0;
}

int strend(char *s, char *t) {
  int i, j;

  for (i = 0; *s != '\0'; i++, s++)
    ;
  for (j = 0; *t != '\0'; j++, t++)
    ;

  if (j > i) {
    return 0;
  }

  while (j-- >= 0)
    if (*s-- != *t--)
      return 0;

  return 1;
}
