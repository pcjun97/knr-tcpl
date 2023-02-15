#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };
enum { OK, ERR };

int dcl(void);
int dirdcl(void);
int getch(void);
void ungetch(int);

int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int main() {
  int c;

  while (gettoken() != EOF) {
    strcpy(datatype, token);
    out[0] = '\0';
    if (dcl() == OK && tokentype == '\n') {
      printf("%s: %s %s\n", name, out, datatype);
    } else {
      if (tokentype != '\n')
        printf("syntax error\n");
      while ((c = getch()) != '\n' && c != EOF)
        ;
      if (c == EOF)
        ungetch(c);
    }
  }
  return 0;
}

/* dcl: parse a declarator */
int dcl(void) {
  int ns;

  for (ns = 0; gettoken() == '*';)
    ns++;
  if (dirdcl() == ERR)
    return ERR;
  while (ns-- > 0)
    strcat(out, " pointer to");

  return OK;
}

/* dirdcl: parse a direct declarator */
int dirdcl(void) {
  int type;

  if (tokentype == '(') { /* ( dcl ) */
    if (dcl() == ERR)
      return ERR;
    if (tokentype != ')') {
      printf("error: missing )\n");
      return ERR;
    }
  } else if (tokentype == NAME) { /* variable name */
    strcpy(name, token);
  } else {
    printf("error: expected name or (dcl)\n");
    return ERR;
  }

  while ((type = gettoken()) == PARENS || type == BRACKETS)
    if (type == PARENS) {
      strcat(out, " function returning");
    } else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }

  return OK;
}

int gettoken(void) {
  int c;
  char *p = token;

  while ((c = getch()) == ' ' || c == '\t')
    ;

  if (c == '(') {
    if ((c = getch()) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetch(c);
      return tokentype = '(';
    }
  } else if (c == '[') {
    for (*p++ = c; (*p++ = getch()) != ']';)
      ;
    *p = '\0';
    return tokentype = BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getch());)
      *p++ = c;
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  } else {
    return tokentype = c;
  }
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
