#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getoneline(char line[], int max);
int strindex(char source[], char searchfor[]);

int main() {
  int i;
  int found = 0;

  char line[MAXLINE];
  char pattern[] = "ould";

  while (getoneline(line, MAXLINE) > 0) {
    i = strindex(line, pattern);
    if (i >= 0) {
      printf("found at %d\n", i);
      printf("%s", line);
      found++;
    }
  }

  return found;
}

/* getoneline: get line into s, return length */
int getoneline(char s[], int lim) {
  int c, i;

  i = 0;
  while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
    s[i++] = c;
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';
  return i;
}

/* strindex: return index of rightmost occurrence of t in s, -1 if none */
int strindex(char s[], char t[]) {
  int i, j, k, o;

  for (i = strlen(s) - strlen(t) - 1; i >= 0; i--) {
    for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
      ;
    if (k > 0 && t[k] == '\0')
      return i;
  }

  return -1;
}
