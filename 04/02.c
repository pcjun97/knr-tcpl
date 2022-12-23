#include <ctype.h>
#include <stdio.h>

#define MAXLINE 1000

double atof(char s[]);
int getoneline(char line[], int max);

int main() {
  double sum;
  char line[MAXLINE];

  sum = 0;
  while (getoneline(line, MAXLINE) > 0)
    printf("\t%g\n", sum += atof(line));
  return 0;
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

/* atof: convert string s to double */
double atof(char s[]) {
  double val, power;
  int i, e, sign;

  for (i = 0; isspace(s[i]); i++)
    ;

  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;

  for (val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');

  if (s[i] == '.')
    i++;

  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10;
  }

  val = sign * (val / power);

  if (s[i] == 'e' || s[i] == 'E') {
    sign = (s[++i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
      i++;
    for (e = 0; isdigit(s[i]); i++)
      e = 10 * e + (s[i] - '0');
    while (e-- > 0)
      val = (sign > 0) ? val * 10 : val / 10;
  }

  return val;
}
