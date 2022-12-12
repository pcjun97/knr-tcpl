#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */

int getoneline(char line[], int maxline);
void copy(char to[], char from[]);
int trim(char line[]);

/* print the longest input line */
int main() {
  int n, len;
  char tmp[MAXLINE], line[MAXLINE];

  while ((len = getoneline(line, MAXLINE)) > 0) {
    copy(tmp, line);

    while (len == MAXLINE - 1 && tmp[MAXLINE - 2] != '\n') {
      len = getoneline(tmp, MAXLINE);
    }

    len = trim(line);

    if (len > 0) {
      printf("%s\n", line);
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

/* trim: remove trailing blanks, tabs and newlines */
int trim(char s[]) {
  int i, k;

  k = -1;
  for (i = 0; s[i] != '\0'; ++i) {
    if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n') {
      if (k < 0)
        k = i;
    } else
      k = -1;
  }

  if (k >= 0) {
    s[k] = '\0';
    i = k;
  }

  return i;
}
