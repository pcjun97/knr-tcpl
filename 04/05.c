#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define COMMAND '1'

int getop(char[]);
void push(double);
double pop(void);
void command(char[]);

int main() {
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case COMMAND:
      command(s);
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
        printf("error: zero divisor\n");
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }

  return 0;
}

/* command: parse and execute user command */
void command(char s[]) {
  double op2;

  if (strcmp(s, "sin") == 0) {
    push(sin(pop()));
  } else if (strcmp(s, "cos") == 0) {
    push(cos(pop()));
  } else if (strcmp(s, "tan") == 0) {
    push(tan(pop()));
  } else if (strcmp(s, "asin") == 0) {
    push(asin(pop()));
  } else if (strcmp(s, "acos") == 0) {
    push(acos(pop()));
  } else if (strcmp(s, "atan") == 0) {
    push(atan(pop()));
  } else if (strcmp(s, "atan2") == 0) {
    op2 = pop();
    push(atan2(pop(), op2));
  } else if (strcmp(s, "sinh") == 0) {
    push(sinh(pop()));
  } else if (strcmp(s, "cosh") == 0) {
    push(cosh(pop()));
  } else if (strcmp(s, "tanh") == 0) {
    push(tanh(pop()));
  } else if (strcmp(s, "exp") == 0) {
    push(exp(pop()));
  } else if (strcmp(s, "log") == 0) {
    push(log(pop()));
  } else if (strcmp(s, "log10") == 0) {
    push(log10(pop()));
  } else if (strcmp(s, "pow") == 0) {
    op2 = pop();
    push(pow(pop(), op2));
  } else if (strcmp(s, "sqrt") == 0) {
    push(sqrt(pop()));
  } else if (strcmp(s, "ceil") == 0) {
    push(ceil(pop()));
  } else if (strcmp(s, "floor") == 0) {
    push(floor(pop()));
  } else if (strcmp(s, "fabs") == 0) {
    push(fabs(pop()));
  } else if (strcmp(s, "ldexp") == 0) {
    op2 = pop();
    push(ldexp(pop(), op2));
  } else if (strcmp(s, "fmod") == 0) {
    op2 = pop();
    push(fmod(pop(), op2));
  } else {
    printf("error: unknown command %s\n", s);
  }
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

/* push: push f onto value stack */
void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand or string command */
int getop(char s[]) {
  int i, c;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;

  s[1] = '\0';

  if (!isalnum(c) && c != '.') {
    return c;
  }

  i = 0;
  if (isalpha(c)) {
    while (isalnum(s[++i] = c = getch()))
      ;
  } else {
    if (isdigit(c))
      while (isdigit(s[++i] = c = getch()))
        ;

    if (c == '.')
      while (isdigit(s[++i] = c = getch()))
        ;
  }

  s[i] = '\0';
  if (c != EOF)
    ungetch(c);

  return isalpha(s[0]) ? COMMAND : NUMBER;
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
