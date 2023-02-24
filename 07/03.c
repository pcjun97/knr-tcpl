#include <stdarg.h>
#include <stdio.h>

void minprintf(char *, ...);

int main() {
  minprintf("%d %i %o %x %X %u\n", 91, 92, 93, 94, 95, -96);
  minprintf("%c %s\n", 'a', "bcd");
  minprintf("%f %p %% %z\n", 0.123, NULL);
  return 0;
}

void minprintf(char *fmt, ...) {
  va_list ap;
  char *p, *sval;
  int ival;
  double dval;
  void *pval;
  char format[] = {'%', '\0', '\0'};

  va_start(ap, fmt);
  for (p = fmt; *p; p++) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }

    switch (*++p) {
    case 'd':
    case 'i':
    case 'o':
    case 'x':
    case 'X':
    case 'u':
      ival = va_arg(ap, int);
      format[1] = *p;
      printf(format, ival);
      break;

    case 'c':
      ival = va_arg(ap, int);
      putchar(ival);
      break;

    case 's':
      for (sval = va_arg(ap, char *); *sval; sval++)
        putchar(*sval);
      break;

    case 'f':
      dval = va_arg(ap, double);
      printf("%f", dval);
      break;

    case 'p':
      pval = va_arg(ap, void *);
      printf("%p", pval);
      break;

    case '%':
      putchar(*p);
      break;

    default:
      putchar('%');
      putchar(*p);
      break;
    }
  }
  va_end(ap);
}
