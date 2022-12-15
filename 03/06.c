#include <limits.h>
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

void itoa(int n, char s[], int w);
void reverse(char line[]);

int main() {
  char line[1000];
  itoa(INT_MIN, line, 20);
  printf("%d\n", INT_MIN);
  printf("%s\n", line);

  itoa(INT_MAX, line, 15);
  printf("%d\n", INT_MAX);
  printf("%s\n", line);
  return 0;
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[], int w) {
  int i, sign;
  sign = n < 0 ? -1 : 1;

  i = 0;
  do {
    s[i++] = (n % 10) * sign + '0';
  } while ((n /= 10) != 0);

  while (i < w - 1) {
    s[i++] = '0';
  }

  if (sign < 0)
    s[i++] = '-';
  else
    s[i++] = '0';

  s[i] = '\0';
  reverse(s);
}

/* reverse: reverse string s in place */
void reverse(char s[]) {
  int c, i, j;

  for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    c = s[i], s[i] = s[j], s[j] = c;
}
