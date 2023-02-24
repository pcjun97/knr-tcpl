#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int _getline(char *, int max, FILE *);

int main(int argc, char *argv[]) {
  FILE *fp;
  char line[MAXLINE];
  long lineno = 0;
  int c, except = 0, number = 0, found = 0;

  while (--argc > 0 && (*++argv)[0] == '-')
    while ((c = *++argv[0]))
      switch (c) {
      case 'x':
        except = 1;
        break;

      case 'n':
        number = 1;
        break;

      default:
        printf("find: illegal option %c\n", c);
        return -1;
      }

  if (argc < 1 || argc > 2) {
    printf("usage: %s -x -n pattern file\n", argv[0]);
    return -1;
  }

  if (argc == 1)
    fp = stdin;
  else
    fp = fopen(argv[1], "r");

  while (_getline(line, MAXLINE, fp) > 0)
    if ((strstr(line, argv[0]) != NULL) != except) {
      if (number)
        printf("%ld: ", lineno);
      printf("%s", line);
      found++;
    }

  if (argc == 2)
    fclose(fp);

  return found;
}

int _getline(char *line, int max, FILE *fp) {
  if (fgets(line, max, fp) == NULL)
    return 0;
  else
    return strlen(line);
}
