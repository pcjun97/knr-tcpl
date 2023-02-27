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

int _flushbuf(int c, FILE *fp) {
  unsigned nc;
  int bufsize;

  if (fp < _iob || fp >= _iob + OPEN_MAX)
    return EOF;

  if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
    return EOF;

  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

  if (fp->base == NULL) {
    if ((fp->base = (char *)malloc(bufsize)) == NULL) {
      fp->flag |= _ERR;
      return EOF;
    }
  } else {
    nc = fp->ptr - fp->base;
    if (write(fp->fd, fp->base, nc) != nc) {
      fp->flag |= _ERR;
      return EOF;
    }
  }

  fp->ptr = fp->base;
  *fp->ptr++ = (char)c;
  fp->cnt = bufsize - 1;

  return 0;
}

int fflush(FILE *fp) {
  int rc = 0;

  if (fp == NULL) {
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
      if (fp->flag & _WRITE)
        rc |= fflush(fp);
    return rc;
  }

  if (fp < _iob || fp >= _iob + OPEN_MAX)
    return EOF;

  if ((fp->flag & _READ)) {
    fp->cnt = 0;
    fp->ptr = fp->base;
    return 0;
  }

  if (fp->flag & _WRITE)
    rc = _flushbuf(0, fp);

  fp->ptr = fp->base;
  fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

  return rc;
}

int fclose(FILE *fp) {
  if (fflush(fp) != 0 || close(fp->fd) != 0)
    return EOF;

  free(fp->base);
  fp->ptr = fp->base = NULL;
  fp->cnt = 0;
  fp->flag = 0;
  fp->fd = -1;

  return 0;
}
