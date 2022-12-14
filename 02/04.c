#include <stdio.h>
#define MAXLINE 1000

void squeeze(char s1[], char s2[]);
int getoneline(char line[], int maxline);

int main() {
  char s1[MAXLINE], s2[MAXLINE];

  getoneline(s1, MAXLINE);
  getoneline(s2, MAXLINE);
  squeeze(s1, s2);
  printf("%s", s1);

  return 0;
}

/* squeeze: delete any charater in s2 from s1 */
void squeeze(char s1[], char s2[]) {
  int i, j, k, f;

  for (i = j = 0; s1[i] != '\0'; i++) {
    f = 0;
    for (k = 0; s2[k] != '\0'; k++)
      if (s1[i] == s2[k])
        f = 1;
    if (f == 0)
      s1[j++] = s1[i];
  }

  s1[j] = '\0';
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
