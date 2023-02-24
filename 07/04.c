#include <stdarg.h>
#include <stdio.h>

void minscanf(char *, ...);

int main() {
  int i;
  char word[100];
  float f;

  minscanf("%d %s %f", &i, word, &f);
  printf("%d %s %f\n", i, word, f);
}

void minscanf(char *fmt, ...) {
  va_list ap;
  char *p, *sval;
  int *ival;
  float *fval;
  char format[] = {'%', '\0', '\0'};

  va_start(ap, fmt);
  for (p = fmt; *p; p++) {
    if (*p != '%')
      continue;

    switch (*++p) {
    case 'd':
    case 'i':
    case 'o':
    case 'x':
    case 'c':
      ival = va_arg(ap, int *);
      format[1] = *p;
      scanf(format, ival);
      break;

    case 's':
      sval = va_arg(ap, char *);
      scanf("%s", sval);
      break;

    case 'f':
      fval = va_arg(ap, float *);
      scanf("%f", fval);
      break;

    default:
      break;
    }
  }
  va_end(ap);
}
