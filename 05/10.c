#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER '0'

int getop(char *);
void push(double);
double pop(void);

int main(int argc, char *argv[]) {
  double op2;
  while (--argc > 0) {
    switch (getop(*++argv)) {
    case NUMBER:
      push(atof(*argv));
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
    default:
      printf("error: unknown command %s\n", *argv);
      break;
    }
  }
  printf("%g\n", pop());
  return 0;
}

int getop(char *s) {
  if (*s == '*' || *s == '/') {
    return *s;
  }

  if (*s == '-' || *s == '+' || *s == '.') {
    if (isdigit(*(s + 1)))
      return NUMBER;
    else
      return *s;
  }

  if (isdigit(*s))
    return NUMBER;

  return 0;
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
