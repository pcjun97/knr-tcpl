#include <ctype.h>
#include <stdio.h>

#define MAXLINE 1000

void expand(char s1[], char s2[]);

int main() {
  char line[MAXLINE];
  expand("a-z A-Z 0-9 a-z0-9 t-h 7-2 a-b-c -z-w- 0-i", line);
  printf("%s\n", line);
  return 0;
}

/* expand: expands shorthand notations
 * a-z to abc...xyz
 * A-Z to ABC...XYZ
 * 0-9 to 012...789 */
void expand(char s1[], char s2[]) {
  int i, j, c, step, shorthand;

  for (i = j = 0; s1[i] != '\0'; i++) {
    shorthand = i != 0 && s1[i] == '-' &&
                ((islower(s1[i - 1]) && islower(s1[i + 1])) ||
                 (isupper(s1[i - 1]) && isupper(s1[i + 1])) ||
                 (isdigit(s1[i - 1]) && isdigit(s1[i + 1])));
    if (shorthand) {
      step = s1[i - 1] < s1[i + 1] ? 1 : -1;
      for (c = s1[i - 1] + step; c != s1[i + 1]; c += step)
        s2[j++] = c;
    } else {
      s2[j++] = s1[i];
    }
  }
}
