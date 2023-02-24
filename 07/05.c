#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char[]);
void push(double);
double pop(void);

int main() {
  int type;
  double op2, n;
  char s[MAXOP], space;

  while (scanf("%s%c", s, &space) == 2) {
    if (sscanf(s, "%lf", &n) > 0)
      push(n);
    else if (strlen(s) > 1) {
      printf("error: unknown operator %s\n", s);
      continue;
    } else
      switch (*s) {
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
        if (op2 != 0.0) {
          push(pop() / op2);
          break;
        } else {
          printf("error: zero divisor\n");
          continue;
        }

      case '%':
        op2 = pop();
        if (op2 != 0.0) {
          push((int)pop() % (int)op2);
          break;
        } else {
          printf("error: zero divisor\n");
          continue;
        }

      default:
        printf("error: unknown operator %s\n", s);
        continue;
      }

    if (space == '\n')
      printf("\t%.8g\n", pop());
  }

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
