#include <ctype.h>
#include <stdio.h>

int getint(int *);

int main() {
  int n, r;
  r = getint(&n);
  printf("n: %d\tr: %d\n", n, r);
  return 0;
}

int getch(void);
void ungetch(int);

/* getint: get next integer from input into *pn */
int getint(int *pn) {
  int c, sign;

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

  *pn *= sign;
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
