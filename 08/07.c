#include <limits.h>
#include <stdio.h>

void *_malloc(unsigned);
void _free(void *);

typedef long Align;

union header {
  struct {
    union header *ptr;
    unsigned size;
  } s;

  Align x;
};

typedef union header Header;

int main() {
  char *p1, *p2;

  if (_malloc(0) != NULL)
    fprintf(stderr, "error: malloc should not alloc 0 bytes\n");
  if (_malloc(UINT_MAX - sizeof(long) + 1) != NULL)
    fprintf(stderr, "error: malloc should not alloc too many bytes\n");

  if ((p1 = _malloc(sizeof(char) * 1000)) == NULL)
    fprintf(stderr, "error: failed to allocate space for p1\n");

  if ((p2 = _malloc(sizeof(char) * 1000)) == NULL)
    fprintf(stderr, "error: failed to allocate space for p2\n");

  if (p1 == p2) {
    fprintf(stderr, "error: p1 and p2 have the same address\n");
    _free(p1);
    return 1;
  }

  _free(NULL);
  _free(p1);
  _free(p2);

  printf("%d\n", ((Header *)p1 - 1)->s.size);
  printf("%d\n", ((Header *)p2 - 1)->s.size);

  return 0;
}

static Header base;
static Header *freep = NULL;
static Header *_morecore(unsigned);

void *_malloc(unsigned nbytes) {
  Header *p, *prevp;
  unsigned nunits;

  if (nbytes == 0 || nbytes > UINT_MAX - sizeof(Header))
    return NULL;

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

  if (ap == NULL)
    return;

  bp = (Header *)ap - 1;
  if (bp->s.size == 0)
    return;

  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break;

  if (bp + bp->s.size == p->s.ptr && bp->s.size < UINT_MAX - p->s.ptr->s.size) {
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else
    bp->s.ptr = p->s.ptr;

  if (p + p->s.size == bp && p->s.size < UINT_MAX - bp->s.size) {
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else
    p->s.ptr = bp;

  freep = p;
}
