#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define BUFSIZE 10000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines, char *buf, int bufsize);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

int main() {
  int nlines;
  char buf[BUFSIZE];

  if ((nlines = readlines(lineptr, MAXLINES, buf, BUFSIZE)) >= 0) {
    qsort(lineptr, 0, nlines - 1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to be sort\n");
    return -1;
  }
}

#define MAXLEN 1000
int _getline(char *, int);

int readlines(char *lineptr[], int maxlines, char *buf, int bufsize) {
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  p = buf;
  while ((len = _getline(line, MAXLEN)) > 0) {
    if (nlines > MAXLINES || buf + bufsize - p < len)
      return -1;
    line[len - 1] = '\0';
    strcpy(p, line);
    lineptr[nlines++] = p;
    p += len;
  }
  return nlines;
}

void writelines(char *lineptr[], int nlines) {
  int i;
  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}

void swap(char *v[], int i, int j);

void qsort(char *v[], int left, int right) {
  int i, last;

  if (left >= right)
    return;
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if (strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last - 1);
  qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j) {
  char *tmp = v[i];
  v[i] = v[j];
  v[j] = tmp;
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
