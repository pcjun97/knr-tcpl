#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

int getoneline(char line[], int maxline);
void copy(char to[], char from[]);

/* print the longest input line */
int main() {
  int n, len, max;
  char tmp[MAXLINE], line[MAXLINE], longest[MAXLINE];

  max = 0;
  while ((n = getoneline(line, MAXLINE)) > 0) {
    len = n;
    copy(tmp, line);

    while (n == MAXLINE - 1 && tmp[MAXLINE - 2] != '\n') {
      n = getoneline(tmp, MAXLINE);
      len = len + n;
    }

    if (len > max) {
      max = len;
      copy(longest, line);
    }
  }

  if (max > 0) { /* there was a line */
    printf("%s", longest);
    if (max > MAXLINE - 1 && longest[MAXLINE - 2] != '\n')
      putchar('\n');
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

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[]) {
  int i;

  i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}
