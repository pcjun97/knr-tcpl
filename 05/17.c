#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXARGS 100
char *lineptr[MAXLINES];
int defaultreverse = 0;
int (*defaultcomp)(void *, void *) = &strcmp;

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

int parsemodifiers(char *arg, int (**comp)(void *, void *), int *reverse);
int parsearg(char *arg, int (**comp)(void *, void *), int *nfields, int *reverse);
void _qsort(void *lineptr[], int left, int right, int (*comp[])(void *, void *), int reverse[], int fields[], int n);
int numcmp(char *, char *);
int strfcmp(char *, char *);
int dircmp(char *, char *);
int dirfcmp(char *, char *);

int main(int argc, char *argv[]) {
  int i, e;
  int nlines;

  int nfields[MAXARGS];
  int reverse[MAXARGS];
  int (*comp[MAXARGS])(void *, void *);

  if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
    printf("input too big to sort\n");
    return 1;
  }

  argc--;
  argv++;

  if (argc > 0 && (*argv)[0] == '-') {
    if ((e = parsemodifiers(argv[0] + 1, &defaultcomp, &defaultreverse)) != 0)
      return e;
    argc--;
    argv++;
  }

  for (i = 0; i < argc; i++)
    if ((e = parsearg(*argv++, &comp[i], &nfields[i], &reverse[i])) != 0)
      return e;

  _qsort((void **)lineptr, 0, nlines - 1, comp, reverse, nfields, i);

  writelines(lineptr, nlines);

  return 0;
}

int parsemodifiers(char *arg, int (**comp)(void *, void *), int *reverse) {
  int numeric = 0;
  int fold = 0;
  int dir = 0;
  char c;

  *reverse = 0;
  while ((c = *arg++))
    switch (c) {
    case 'n':
      numeric = 1;
      break;
    case 'r':
      *reverse = 1;
      break;
    case 'f':
      fold = 1;
      break;
    case 'd':
      dir = 1;
      break;
    default:
      printf("sort: illegal option %c\n", c);
      return 1;
    }

  if (numeric)
    *comp = &numcmp;
  else if (dir && fold)
    *comp = &dirfcmp;
  else if (dir)
    *comp = &dircmp;
  else if (fold)
    *comp = &strfcmp;
  else
    *comp = defaultcomp;

  return 0;
}

int parsearg(char *arg, int (**comp)(void *, void *), int *nfields, int *reverse) {
  if (!isdigit(*arg)) {
    printf("sort: illegal argument %s\n", arg);
    return 1;
  }

  *nfields = atoi(arg);
  while (isdigit(*arg))
    arg++;

  return parsemodifiers(arg, comp, reverse);
}

#define MAXLEN 1000
void getfield(char *field, char *line, int n);

void _qsort(void *v[], int left, int right, int (*comp[])(void *, void *), int reverse[], int nfields[], int n) {
  int i, j, last, c;
  char s1[MAXLEN], s2[MAXLEN];

  void swap(void *v[], int, int);

  if (left > right)
    return;

  swap(v, left, (left + right) / 2);
  last = left;

  for (i = left + 1; i <= right; i++) {
    for (j = 0; j < n; j++) {
      getfield(s2, v[left], nfields[j]);
      getfield(s1, v[i], nfields[j]);
      c = (*comp[j])(s1, s2);
      if (reverse[j])
        c *= -1;
      if (c != 0)
        break;
    }
    if (c < 0)
      swap(v, ++last, i);
  }

  swap(v, left, last);
  _qsort(v, left, last - 1, comp, reverse, nfields, n);
  _qsort(v, last + 1, right, comp, reverse, nfields, n);
}

void getfield(char *field, char *line, int n) {
  int i;
  char *start;

  if (n == 0) {
    strcpy(field, line);
    return;
  }

  while (--n > 0 && *line != '\0') {
    while (!isspace(*line) && *line != '\0')
      line++;

    while (isspace(*line))
      line++;
  }

  start = line;
  for (i = 0; !isspace(*line) && *line != '\0'; i++, line++)
    ;

  strncpy(field, start, i);
  field[i] = '\0';
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

int dircmp(char *s, char *t) {
  do {
    for (; *s == *t; s++, t++)
      if (*s == '\0')
        return 0;

    while (!isalnum(*s) && *s != '\0')
      s++;
    while (!isalnum(*t) && *t != '\0')
      t++;
  } while (*s == *t);

  return *s - *t;
}

int dirfcmp(char *s, char *t) {
  do {
    for (; tolower(*s) == tolower(*t); s++, t++)
      if (*s == '\0')
        return 0;

    while (!isalnum(*s) && *s != '\0')
      s++;
    while (!isalnum(*t) && *t != '\0')
      t++;
  } while (tolower(*s) == tolower(*t));

  return tolower(*s) - tolower(*t);
}

void swap(void *v[], int i, int j) {
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

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
