#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define OPEN_MAX 20
#define PERMS 0666
#define EOF (-1)
#define BUFSIZ 1024

typedef struct _iobuf {
  int cnt;
  unsigned read;
  unsigned write;
  unsigned unbuf;
  unsigned eof;
  unsigned err;
  char *ptr;
  char *base;
  int fd;
} FILE;

FILE _iob[OPEN_MAX];

FILE *_fopen(char *name, char *mode) {
  int fd;
  FILE *fp;

  if (*mode != 'r' && *mode != 'w' && *mode != 'a')
    return NULL;

  for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
    if (fp->read == 0 && fp->write == 0)
      break;

  if (fp >= _iob + OPEN_MAX)
    return NULL;

  if (*mode == 'w')
    fd = creat(name, PERMS);
  else if (*mode == 'a') {
    if ((fd = open(name, O_WRONLY, 0)) == -1)
      fd = creat(name, PERMS);
    lseek(fd, 0L, 2);
  } else
    fd = open(name, O_RDONLY, 0);

  if (fd == -1)
    return NULL;

  fp->fd = fd;
  fp->cnt = 0;
  fp->base = NULL;
  fp->unbuf = 0;
  fp->eof = 0;
  fp->err = 0;

  if (*mode == 'r') {
    fp->read = 1;
    fp->write = 0;
  } else {
    fp->read = 0;
    fp->write = 1;
  }

  return fp;
}

int _fillbuf(FILE *fp) {
  int bufsize;

  if (fp->err != 0 || fp->eof != 0 || fp->read != 1)
    return EOF;

  bufsize = fp->unbuf ? 1 : BUFSIZ;

  if (fp->base == NULL)
    if ((fp->base = (char *)malloc(bufsize)) == NULL)
      return EOF;

  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if (--fp->cnt > 0) {
    if (fp->cnt == -1)
      fp->eof = 1;
    else
      fp->err = 1;
    fp->cnt = 0;
    return EOF;
  }

  return (unsigned char)*fp->ptr++;
}
