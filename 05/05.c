#include <stdio.h>
#define MAXLINE 1000

char *strncpy(char *, char *, int);
char *strncat(char *, char *, int);
int strncmp(char *, char *, int);

int main() {
  char line[MAXLINE];
  strncpy(line, "hel", 6);
  printf("%s\n", line);
  strncpy(line, "hello world", 6);
  printf("%s\n", line);
  strncat(line, "world! this should not get copied", 7);
  printf("%s\n", line);
  printf("%d\n", strncmp(line, "hello c!!", 5));
  printf("%d\n", strncmp(line, "world hello", 10));
  printf("%d\n", strncmp(line, "hallo world", 3));
  return 0;
}

/* strncpy: copy at most n characters of string ct to s; return s
 * pad with '\0' if ct has fewer than n characters */
char *strncpy(char *s, char *ct, int n) {
  int i;
  char *cs = s;

  for (i = 0; i < n && *ct != '\0'; i++)
    *cs++ = *ct++;

  while (i++ < n)
    *cs++ = '\0';

  return s;
}

/* strncat: concatenate at most n characters of string ct to string s
 * terminate s with '\0'; return s */
char *strncat(char *s, char *ct, int n) {
  int i;
  char *cs = s;

  while (*cs != '\0')
    cs++;

  for (i = 0; i < n && *ct != '\0'; i++)
    *cs++ = *ct++;

  *cs = '\0';
  return s;
}

/* strncmp: compare at most n characters of string cs to string ct
 * return <0 if cs<ct, 0 if cs==ct, or >0 if cs>ct */
int strncmp(char *cs, char *ct, int n) {
  while (n-- > 0 && *cs != '\0' && *cs == *ct) {
    cs++;
    ct++;
  }
  return *cs - *ct;
}
