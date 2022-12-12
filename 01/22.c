#include <stdio.h>
#define MAXLINE 1000

int getoneline(char line[], int maxline);

int main() {
  int len, i, j, n, c, fold;
  char line[MAXLINE];

  fold = 10;
  n = j = 0;
  while ((len = getoneline(line, MAXLINE)) > 0) {
    j = 0;
    for (i = 0; i < len; i++) {
      c = line[i];

      if (c == '\n' || c == ' ' || c == '\t' || i - j == fold)
        while (j < i) {
          putchar(line[j]);
          ++j;
        }

      if (n == fold || c == '\n') {
        putchar('\n');
        n = i - j;
      }

      if (c == ' ') {
        putchar(' ');
        ++n;
        ++j;
      } else if (c == '\t') {
        if (n > fold - 8) {
          putchar('\n');
          n = 0;
        }
        putchar('\t');
        n = n + 8;
        ++j;
      } else {
        ++n;
      }
    }
  }

  return 0;
}

/* getoneline: read a line into s, return length */
int getoneline(char s[], int lim) {
  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;

  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';

  return i;
}
