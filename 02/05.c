#include <stdio.h>
#define MAXLINE 1000

int any(char s1[], char s2[]);
int getoneline(char line[], int maxline);

int main() {
  int i;
  char s1[MAXLINE], s2[MAXLINE];

  getoneline(s1, MAXLINE);
  getoneline(s2, MAXLINE);
  i = any(s1, s2);
  printf("%d\n", i);
  return 0;
}

/* any: return the index of the first location of any characters from s2 in s1,
 * or -1 if no characters from s2 is present in s1 */
int any(char s1[], char s2[]) {
  int i, j;

  for (i = 0; s1[i] != '\0'; i++)
    for (j = 0; s2[j] != '\0'; j++)
      if (s1[i] == s2[j])
        return i;

  return -1;
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
