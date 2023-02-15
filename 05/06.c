#include <ctype.h>
#include <stdio.h>
#define NUMBER '0'
#define MAXLINE 1000

int _getline(char *, int);
int atoi(char *);
void itoa(int, char *);
void reverse(char *);
int strindex(char *, char *);
int getop(char *);

int main() {
  char line[1000];
  int i;

  i = _getline(line, MAXLINE);
  printf("%d %s\n", i, line);

  printf("%d\n", atoi("-100"));

  itoa(1234, line);
  printf("%s\n", line);

  itoa(-398, line);
  printf("%s\n", line);

  reverse(line);
  printf("%s\n", line);

  printf("%d\n", strindex(line, "93"));

  i = getop(line);
  printf("%d %s\n", i, line);

  return 0;
}

/* _getline */

int _getline(char *s, int lim) {
  int c, i;
  for (i = 0; i < lim && (c = getchar()) != EOF && c != '\n'; i++)
    *s++ = c;
  if (c == '\n')
    *s = c;
  return i;
}

/* atoi */
int atoi(char *s) {
  int val, sign;

  while (isspace(*s))
    s++;

  sign = *s == '-' ? -1 : 1;

  if (*s == '+' || *s == '-')
    s++;

  val = 0;
  while (isdigit(*s))
    val = val * 10 + (*s++ - '0');

  val *= sign;
  return val;
}

/* itoa */
void itoa(int n, char *s) {
  char *cs = s;
  int sign = n;
  if (n < 0)
    n = -n;

  *cs = '0';
  while (n != 0) {
    *cs++ = (n % 10) + '0';
    n /= 10;
  }
  if (sign < 0)
    *cs = '-';
  *++cs = '\0';
  reverse(s);
}

/* reverse */
void reverse(char *s) {
  char *t, c;
  for (t = s; *t != '\0'; t++)
    ;
  t--;
  while (s < t) {
    c = *s;
    *s++ = *t;
    *t-- = c;
  }
}

/* strindex */
int strindex(char *s, char *t) {
  int i;
  char *cs, *ct;
  for (i = 0; *s != '\0'; s++, i++) {
    for (cs = s, ct = t; *ct != '\0' && *cs == *ct; cs++, ct++)
      ;
    if (ct > t && *ct == '\0')
      return i;
  }
  return -1;
}

int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char *s) {
  int i, c;

  while ((*s = c = getch()) == ' ' || c == '\t')
    ;

  *++s = '\0';

  if (!isdigit(c) && c != '.' && c != '-') {
    return c;
  }

  if (c == '-') {
    if (!isdigit(c = getch()) && c != '.') {
      ungetch(c);
      return '-';
    } else {
      *s++ = c;
    }
  }

  if (isdigit(c))
    while (isdigit(*s++ = c = getch()))
      ;

  if (c == '.')
    while (isdigit(*s++ = c = getch()))
      ;

  *--s = '\0';
  if (c != EOF)
    ungetch(c);

  return NUMBER;
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
