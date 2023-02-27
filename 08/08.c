#include <stdio.h>

void *_malloc(unsigned);
void _free(void *);
void bfree(char *, unsigned);

typedef long Align;

union header {
  struct {
    union header *ptr;
    unsigned size;
  } s;

  Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;
static Header *_morecore(unsigned);

static char *a = NULL;
static char b[sizeof(Header)];
static char c[sizeof(Header) * 2];
static char d[sizeof(Header) * 3];

int main() {
  char *e;

  printf("a:%p b:%p, c:%p d:%p\n", a, b, c, d);

  bfree(a, sizeof(a));
  bfree(b, sizeof(b));
  bfree(c, sizeof(c));
  bfree(d, sizeof(d));

  e = _malloc(sizeof(Header));
  printf("e:%p\n", e);
  _free(e);

  e = _malloc(sizeof(Header));
  printf("e:%p\n", e);
  _free(e);

  return 0;
}

void *_malloc(unsigned nbytes) {
  Header *p, *prevp;
  unsigned nunits;

  nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
  if ((prevp = freep) == NULL) {
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }

  for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
    if (p->s.size >= nunits) {
      if (p->s.size == nunits)
        prevp->s.ptr = p->s.ptr;
      else {
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      freep = prevp;
      return (void *)(p + 1);
    }

    if (p == freep)
      if ((p = _morecore(nunits)) == NULL)
        return NULL;
  }
}

#define NALLOC 1024

static Header *_morecore(unsigned nu) {
  char *cp, *sbrk(int);
  Header *up;

  if (nu < NALLOC)
    nu = NALLOC;

  cp = sbrk(nu * sizeof(Header));
  if (cp == (char *)-1)
    return NULL;

  up = (Header *)cp;
  up->s.size = nu;
  _free((void *)(up + 1));

  return freep;
}

void _free(void *ap) {
  Header *bp, *p;

  bp = (Header *)ap - 1;
  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break;

  if (bp + bp->s.size == p->s.ptr) {
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else
    bp->s.ptr = p->s.ptr;

  if (p + p->s.size == bp) {
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else
    p->s.ptr = bp;

  freep = p;
}

void bfree(char *p, unsigned n) {
  Header *bp;

  if (p == NULL || n < sizeof(Header) * 2)
    return;

  if (freep == NULL) {
    base.s.ptr = freep = &base;
    base.s.size = 0;
  }

  bp = (Header *)p;
  bp->s.size = n / sizeof(Header) - 1;
  _free((void *)(bp + 1));

  return;
}
