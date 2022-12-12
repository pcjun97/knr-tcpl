#include <stdio.h>

int main() {
  int instring, inconstant, incomment, delay;
  char window[2];

  window[0] = window[1] = '\0';
  incomment = instring = inconstant = 0;
  delay = 2;
  while (window[0] != EOF) {
    window[1] = window[0];
    window[0] = getchar();

    if (instring == 1) {
      if (window[1] != '\\' && window[0] == '"')
        instring = 0;
    } else if (inconstant == 1) {
      if (window[1] != '\\' && window[0] == '\'')
        inconstant = 0;
    } else if (incomment == 1) {
      if (window[1] == '*' && window[0] == '/') {
        incomment = 0;
        delay = 2;
      }
    } else if (window[1] == '/' && window[0] == '*') {
      incomment = 1;
    } else if (window[0] == '"') {
      instring = 1;
    } else if (window[0] == '\'') {
      inconstant = 1;
    }

    if (incomment == 0 && delay == 0)
      putchar(window[1]);
    else if (delay > 0)
      --delay;
  }

  return 0;
}
