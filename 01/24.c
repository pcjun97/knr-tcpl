#include <stdio.h>
#define MAXSTACKCAP 1000

int main() {
  int i, j, nline, instring, inconstant, incomment;
  char c[2], stack[MAXSTACKCAP];

  nline = 1;
  i = stack[0] = c[0] = c[1] = instring = inconstant = incomment = 0;
  while (c[0] != EOF && i < MAXSTACKCAP) {
    c[1] = c[0];
    c[0] = getchar();

    if (instring == 1 || inconstant == 1) {
      if (c[1] == '\\' && c[0] == '\\') {
        c[0] = c[1] = 0;
      }
    }

    if (instring == 1) {
      if (c[1] != '\\' && c[0] == '"')
        instring = 0;
    } else if (inconstant == 1) {
      if (c[1] != '\\' && c[0] == '\'')
        inconstant = 0;
    } else if (incomment == 1) {
      if (c[1] == '*' && c[0] == '/') {
        incomment = 0;
      }
    } else if (c[1] == '/' && c[0] == '*') {
      incomment = 1;
    } else if (c[0] == '"') {
      instring = 1;
    } else if (c[0] == '\'') {
      inconstant = 1;
    }

    if (c[0] == '\n') {
      ++nline;
    } else if (instring == 1 || inconstant == 1 || incomment == 1) {
      /* do nothing */
    } else if (c[0] == '{' || c[0] == '[' || c[0] == '(') {
      if (i == MAXSTACKCAP) {
        printf("Error: stack overflow\n");
        return 1;
      }
      stack[i] = c[0];
      ++i;
    } else if (c[0] == '}') {
      if (i > 0 && stack[i - 1] == '{')
        --i;
      else {
        printf("Error: line %d: closing unopened braces\n", nline);
        return 1;
      }
    } else if (c[0] == ']') {
      if (i > 0 && stack[i - 1] == '[')
        --i;
      else {
        printf("Error: line %d: closing unopened brackets\n", nline);
        return 1;
      }
    } else if (c[0] == ')') {
      if (i > 0 && stack[i - 1] == '(')
        --i;
      else {
        printf("Error: line %d: closing unopened parantheses\n", nline);
        return 1;
      }
    }
  }

  if (i > 0) {
    printf("Error: unclosed ");
    putchar(stack[i - 1]);
    putchar('\n');
    return 1;
  }

  printf("I believe your code is perfectly bug-free!\n");
  return 0;
}
