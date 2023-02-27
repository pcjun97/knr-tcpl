#include <stdio.h>

void *_calloc(unsigned, unsigned);
void *_malloc(unsigned);
void _free(void *);

int main() {
  int i;
  int *n = _calloc(100, sizeof(int));
  for (i = 0; i < 100; i++) {
    if (n[i] != 0) {
      fprintf(stderr, "storage allocated at %d is not 0\n", i);
      _free(n);
      return -1;
    }
    n[i] = i;
  }

  for (i = 0; i < 100; i++) {
    if (n[i] != i) {
      fprintf(stderr, "value assigned to %d is not valid\n", i);
      _free(n);
      return -1;
    }
  }

  _free(n);

  return 0;
}

void *_calloc(unsigned n, unsigned size) {
  unsigned i, nb;
  char *p, *q;

  nb = n * size;
  if ((p = _malloc(nb)) != NULL)
    for (q = p, i = 0; ++i < nb; *q++ = 0)
      ;

  return p;
}

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
