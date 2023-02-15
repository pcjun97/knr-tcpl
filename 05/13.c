#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULTLINES 10
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int maxlines);

#define MAXLINES 1000
char *lineptr[MAXLINES];

int main(int argc, char *argv[]) {
  char *prog = argv[0];
  int nlines, maxlines;
  int c, n = 0;

  while (--argc > 0 && (*++argv)[0] == '-')
    while ((c = *++argv[0]))
      switch (c) {
      case 'n':
        n = 1;
        break;
      default:
        printf("%s: illegal option '%c'\n", prog, c);
        break;
      }

  if ((n && argc != 1) || (!n && argc != 0)) {
    printf("usage: %s [-n nlines]\n", prog);
    return 1;
  }

  if (n)
    maxlines = atoi(*argv);
  else
    maxlines = DEFAULTLINES;

  if (maxlines == 0)
    return 0;

  nlines = readlines(lineptr, maxlines);
  writelines(lineptr, maxlines);

  return 0;
}

#define MAXLEN 1000
int _getline(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines) {
  int i, j, len, nlines;
  char *p, line[MAXLEN];
  char *clineptr[MAXLINES];

  i = nlines = 0;
  while ((len = _getline(line, MAXLEN)) > 0) {
    if ((p = alloc(len + 1)) == NULL)
      return -1;
    strcpy(p, line);
    clineptr[i] = p;
    i = (i + 1) % maxlines;
    if (nlines < maxlines)
      nlines++;
  }
  for (j = 0; j < nlines; j++)
    lineptr[j] = clineptr[(i + j) % nlines];
  return nlines;
}

void writelines(char *lineptr[], int maxlines) {
  while (maxlines-- > 0)
    printf("%s", *lineptr++);
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

#define ALLOCSIZE (MAXLINES + 1) * (MAXLEN + 1)
char allocbuf[ALLOCSIZE];
char *allocp = allocbuf;

char *alloc(int n) {
  if (n > MAXLEN + 1)
    return NULL;

  if (allocbuf + ALLOCSIZE - allocp < n)
    allocp = allocbuf;

  allocp += n;
  return allocp - n;
}
