#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void _qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *), int reverse);
int numcmp(char *, char *);
int strfcmp(char *, char *);

int main(int argc, char *argv[]) {
  int nlines;
  int numeric = 0;
  int reverse = 0;
  int fold = 0;
  char c;

  while (--argc > 0 && (*++argv)[0] == '-')
    while ((c = *++argv[0])) {
      switch (c) {
      case 'n':
        numeric = 1;
        break;
      case 'r':
        reverse = 1;
        break;
      case 'f':
        fold = 1;
        break;
      default:
        printf("sort: illegal option %c\n", c);
        return 1;
      }
    }

  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    _qsort((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))(numeric ? numcmp : (fold ? strfcmp : strcmp)),
           reverse);
    writelines(lineptr, nlines);
  } else {
    printf("input too big to sort\n");
    return 1;
  }

  return 0;
}

void _qsort(void *v[], int left, int right, int (*comp)(void *, void *), int reverse) {
  int i, last, c;

  void swap(void *v[], int, int);

  if (left > right)
    return;

  swap(v, left, (left + right) / 2);
  last = left;

  for (i = left + 1; i <= right; i++) {
    c = (*comp)(v[i], v[left]);
    if (reverse)
      c *= -1;
    if (c < 0)
      swap(v, ++last, i);
  }
  swap(v, left, last);
  _qsort(v, left, last - 1, comp, reverse);
  _qsort(v, last + 1, right, comp, reverse);
}

int numcmp(char *s1, char *s2) {
  double v1, v2;

  v1 = atof(s1);
  v2 = atof(s2);

  if (v1 < v2)
    return -1;
  if (v1 > v2)
    return 1;
  return 0;
}

int strfcmp(char *s, char *t) {
  for (; tolower(*s) == tolower(*t); s++, t++)
    if (*s == '\0')
      return 0;

  return tolower(*s) - tolower(*t);
}

void swap(void *v[], int i, int j) {
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

#define MAXLEN 1000
int _getline(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines) {
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = _getline(line, MAXLEN)) > 0) {
    if (nlines > MAXLINES || (p = alloc(len)) == NULL)
      return -1;
    line[len - 1] = '\0';
    strcpy(p, line);
    lineptr[nlines++] = p;
  }
  return nlines;
}

void writelines(char *lineptr[], int nlines) {
  int i;
  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}

int _getline(char s[], int lim) {
  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;

  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';

  return i;
}

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    allocp += n;
    return allocp - n;
  } else
    return 0;
}
