#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

void itoa(int, char[]);

int main() {
  char line[MAXLINE];
  itoa(566, line);
  printf("%s\n", line);
  itoa(-123, line);
  printf("%s\n", line);
  return 0;
}

void itoa(int n, char s[]) {
  int i, sign;

  if ((sign = n) < 0)
    n = -n;

  if (n < 10) {
    i = 0;
    if (sign < 0)
      s[i++] = '-';
    s[i++] = n + '0';
  } else {
    itoa(sign / 10, s);
    i = strlen(s);
    s[i++] = (n % 10) + '0';
  }
  s[i] = '\0';
}
