#include "12.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int m = 0, n = 0;
int tabstops[MAXTABSTOPS];

int parsetabstops(int argc, char *argv[]) {
  int i;
  char c;
  char *prog = argv[0];

  while (--argc > 0 && ((c = (*++argv)[0]) == '-' || c == '+')) {
    switch (c) {
    case '-':
      if (m > 0) {
        printf("%s: '-' specifier only allowed once\n", prog);
        return 1;
      }
      if (!_isdigit(*argv + 1)) {
        printf("%s: tab stop contains invalid character(s): '%s'\n", prog, *argv);
        return 1;
      }
      m = atoi(*argv + 1);
      if (m <= 0) {
        printf("%s: tab stop contains invalid character(s): '%s'\n", prog, *argv);
        return 1;
      }
      break;
    case '+':
      if (n > 0) {
        printf("%s: '+' specifier only allowed once\n", prog);
        return 1;
      }
      if (!_isdigit(*argv + 1)) {
        printf("%s: tab stop contains invalid character(s): '%s'\n", prog, *argv);
        return 1;
      }
      n = atoi(*argv + 1);
      if (n <= 0) {
        printf("%s: tab stop contains invalid character(s): '%s'\n", prog, *argv);
        return 1;
      }
      break;
    }
  }

  for (i = 0; argc-- > 0; argv++, i++) {
    if (!_isdigit(*argv)) {
      printf("%s: tab stop contains invalid character(s): '%s'\n", prog, *argv);
      return 1;
    }

    tabstops[i] = atoi(*argv);

    if (tabstops[i] <= 0) {
      printf("%s: tab stop contains invalid character(s): '%s'\n", prog, *argv);
      return 1;
    }

    if (i > 0 && tabstops[i] <= tabstops[i - 1]) {
      printf("%s: tab stops must be ascending\n", prog);
      return 1;
    }
  }
  tabstops[i] = 0;

  if (n == 0 && (m > 0 || tabstops[0] == 0))
    n = DEFAULT_TABSTOP;

  return 0;
}

int nexttabstop(int i) {
  int ts;
  int j = 0;

  while (tabstops[j] > 0 && tabstops[j] < i)
    j++;

  if (n <= 0)
    return tabstops[j];

  if (i > m) {
    if (i % n == 0)
      ts = i;
    else
      ts = i + (n - (i % n));
  } else if (m % n == 0)
    ts = m;
  else
    ts = m + (n - (m % n));

  if (tabstops[j] > 0 && tabstops[j] < ts)
    ts = tabstops[j];

  return ts;
}

int _isdigit(char *s) {
  while (*s != '\0') {
    if (!isdigit(*s))
      return 0;
    s++;
  }
  return 1;
}
