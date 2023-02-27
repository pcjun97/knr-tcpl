#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define OPEN_MAX 20
#define PERMS 0666
#define EOF (-1)
#define BUFSIZ 1024

typedef struct _iobuf {
  int cnt;
  char *ptr;
  char *base;
  int flag;
  int fd;
} FILE;

FILE _iob[OPEN_MAX];

enum _flags {
  _READ = 01,
  _WRITE = 02,
  _UNBUF = 04,
  _EOF = 010,
  _ERR = 020,
};

int fseek(FILE *fp, long offset, int origin) {
  unsigned nc;

  if (fp->flag & _READ) {
    if (origin == 1)
      offset -= fp->cnt;

    if (lseek(fp->fd, offset, origin) != 0)
      return -1;

    fp->cnt = 0;
  } else if (fp->flag & _WRITE) {
    if ((nc = fp->ptr - fp->base) > 0)
      if (write(fp->fd, fp->base, nc) != nc)
        return -1;

    if (lseek(fp->fd, offset, origin) != 0)
      return -1;
  }

  return 0;
}
