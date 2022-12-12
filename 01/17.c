#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */
#define THRESHOLD 80

int getoneline(char line[], int maxline);
void copy(char to[], char from[]);

/* print the longest input line */
int main() {
  int n, len;
  char tmp[MAXLINE], line[MAXLINE];

  while ((n = getoneline(line, MAXLINE)) > 0) {
    len = n;
    copy(tmp, line);

    while (n == MAXLINE - 1 && tmp[MAXLINE - 2] != '\n') {
      n = getoneline(tmp, MAXLINE);
      len = len + n;
    }

    if (len > THRESHOLD) {
      printf("%s", line);
      if (len > MAXLINE - 1 && line[MAXLINE - 2] != '\n')
        putchar('\n');
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

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[]) {
  int i;

  i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}
