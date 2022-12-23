#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getch(void);
void ungetch(int);
void ungets(char[]);

int main() {
  int c;
  ungets("This is a test\n");
  while ((c = getch()) != EOF)
    putchar(c);
  return 0;
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

/* ungets: push string back on input */
void ungets(char s[]) {
  int i = strlen(s);
  while (i > 0) {
    ungetch(s[--i]);
  }
}
