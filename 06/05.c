#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};

struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void undef(char *name);

int main() {
  struct nlist *np;

  install("foo", "bar");
  np = lookup("foo");
  printf("%s: %s\n", np->name, np->defn);

  install("foo2", "bar2");
  np = lookup("foo2");
  printf("%s: %s\n", np->name, np->defn);

  install("foo", "baz");
  np = lookup("foo");
  printf("%s: %s\n", np->name, np->defn);

  undef("foo");
  np = lookup("foo");
  printf("foo is null: %s\n", np == NULL ? "yes" : "no");
  np = lookup("foo2");
  printf("foo2 is null: %s\n", np == NULL ? "yes" : "no");

  undef("foo2");
  np = lookup("foo");
  printf("foo is null: %s\n", np == NULL ? "yes" : "no");
  np = lookup("foo2");
  printf("foo2 is null: %s\n", np == NULL ? "yes" : "no");

  return 0;
}

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s) {
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;

  return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
  struct nlist *np;

  for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    if (strcmp(s, np->name) == 0)
      return np;

  return NULL;
}

char *_strdup(char *);

struct nlist *install(char *name, char *defn) {
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(name)) == NULL) {
    np = (struct nlist *)malloc(sizeof(*np));
    if (np == NULL || (np->name = _strdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else
    free((void *)np->defn);

  if ((np->defn = _strdup(defn)) == NULL)
    return NULL;

  return np;
}

void undef(char *name) {
  struct nlist *np, *prev;
  unsigned hashval;

  hashval = hash(name);
  prev = NULL;
  for (np = hashtab[hashval]; np != NULL; np = np->next) {
    if (strcmp(name, np->name) == 0)
      break;
    prev = np;
  }

  if (np == NULL)
    return;

  if (prev == NULL)
    hashtab[hashval] = np->next;
  else
    prev->next = np->next;

  free((void *)np->name);
  free((void *)np->defn);
  free((void *)np);
}

char *_strdup(char *s) {
  char *p;

  p = (char *)malloc(strlen(s) + 1);
  if (p != NULL)
    strcpy(p, s);
  return p;
}
