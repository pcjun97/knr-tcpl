#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int _getline(char *, int, FILE *);

int main(int argc, char *argv[]) {
  FILE *fp1, *fp2;
  char line1[MAXLINE], line2[MAXLINE];
  int len1, len2;

  if (argc != 3) {
    printf("usage: %s file file\n", argv[0]);
    return 1;
  }

  if ((fp1 = fopen(argv[1], "r")) == NULL) {
    printf("%s: cannot open %s\n", argv[0], argv[1]);
    return 1;
  }

  if ((fp2 = fopen(argv[2], "r")) == NULL) {
    printf("%s: cannot open %s\n", argv[0], argv[2]);
    return 1;
  }

  do {
    len1 = _getline(line1, MAXLINE, fp1);
    len2 = _getline(line2, MAXLINE, fp2);
  } while (len1 > 0 && len2 > 0 && strcmp(line1, line2) == 0);

  fclose(fp1);
  fclose(fp2);

  if (len1 > 0)
    printf("%s", line1);

  if (len2 > 0)
    printf("%s", line2);

  return 0;
}

int _getline(char *line, int max, FILE *fp) {
  if (fgets(line, max, fp) == NULL)
    return 0;
  else
    return strlen(line);
}
