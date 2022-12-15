#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

void itob(int n, char s[], int b);
void reverse(char line[]);

int main() {
  int i;
  char line[1000];

  i = 1234;

  /* base16 */
  itob(i, line, 16);
  printf("%x\n", i);
  printf("%s\n", line);

  /* base2 */
  itob(i, line, 2);
  printf("%s\n", line);

  /* base8 */
  itob(i, line, 8);
  printf("%s\n", line);

  /* base36 */
  itob(i, line, 36);
  printf("%s\n", line);

  return 0;
}

/* itob: convert n to characters in s */
void itob(int n, char s[], int b) {
  if (b < 2 || b > 36) {
    return;
  }

  int i, j, sign;
  sign = n < 0 ? -1 : 1;

  i = 0;
  do {
    j = (n % b) * sign;
    s[i++] = j >= 10 ? j - 10 + 'a' : j + '0';
  } while ((n /= b) != 0);

  if (sign < 0)
    s[i++] = '-';

  s[i] = '\0';
  reverse(s);
}

/* reverse: reverse string s in place */
void reverse(char s[]) {
  int c, i, j;

  for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    c = s[i], s[i] = s[j], s[j] = c;
}
