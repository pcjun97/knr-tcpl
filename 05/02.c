#include <ctype.h>
#include <stdio.h>

int getfloat(double *);

int main() {
  double n;
  int r;
  r = getfloat(&n);
  printf("n: %g\tr: %d\n", n, r);
  return 0;
  return 0;
}

int getch(void);
void ungetch(int);

/* getfloat: get next double from input into *pn */
int getfloat(double *pn) {
  int c, sign, power;

  while (isspace(c = getch()))
    ;

  if (!isdigit(c) && c != EOF && c != '-' && c != '+') {
    ungetch(c);
    return 0;
  }

  sign = (c == '-') ? -1 : 1;
  if ((c == '+' || c == '-') && !isdigit(c = getch())) {
    ungetch(c);
    return 0;
  }

  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');

  if (c == '.')
    c = getch();

  for (power = 1; isdigit(c); c = getch()) {
    *pn = 10 * *pn + (c - '0');
    power *= 10;
  }

  *pn = sign * ((*pn) / power);
  if (c != EOF)
    ungetch(c);

  return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

/* getch: get a (possibly pushed-back) character */
int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
