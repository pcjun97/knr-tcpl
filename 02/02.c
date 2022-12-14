#include <stdio.h>
#define MAXLINE 1000

int getoneline(char line[], int lim);

int main() {
  char line[MAXLINE];
  getoneline(line, MAXLINE);
  printf("%s", line);
  return 0;
}

/* getoneline: read a line into s, return length */
int getoneline(char s[], int lim) {
  int c, i;

  c = 0;
  for (i = 0; (i < lim - 1) + (c != EOF) + (c != '\n') == 3; ++i) {
    c = getchar();
    s[i] = c;
  }

  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';

  return i;
}
