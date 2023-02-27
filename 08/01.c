#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

void filecopy(int, int);

/* cat: concatenate files */
int main(int argc, char *argv[]) {
  int n, fd;
  char buf[BUFSIZ];
  char *prog = argv[0];

  if (argc == 1) {
    while ((n = read(STDIN, buf, BUFSIZ)) > 0)
      write(STDOUT, buf, n);
  } else
    while (--argc > 0)
      if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
        fprintf(stderr, "%s: can't open %s\n", prog, *argv);
        return 1;
      } else {
        while ((n = read(fd, buf, BUFSIZ)) > 0)
          write(STDOUT, buf, n);
        close(fd);
      }

  return 0;
}
