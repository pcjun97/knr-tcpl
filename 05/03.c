#include <stdio.h>
#define MAXLINE 1000

void strcat(char *, char *);

int main() {
  char line[MAXLINE];
  line[0] = '\0';
  strcat(line, "hello ");
  strcat(line, "world! ");
  printf("%s\n", line);
  return 0;
}

void strcat(char *s, char *t) {
  while (*s != '\0')
    s++;
  while ((*s++ = *t++))
    ;
}
