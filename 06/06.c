#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};

int gettoken(char *token, int lim);
char *_strdup(char *);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void undef(char *name);
void ungetch(int);

int main() {
  int c;
  struct nlist *np;
  char token[MAXLINE];
  char name[MAXLINE];
  char defn[MAXLINE];
  char *defnptr;

  while (gettoken(token, MAXLINE) != EOF) {
    if (strcmp(token, "#define") == 0) {
      if (!isspace(gettoken(token, MAXLINE))) {
        printf("invalid syntax: %s", token);
        return 1;
      }

      if (!isalpha(gettoken(name, MAXLINE))) {
        printf("invalid name: %s", name);
        return 1;
      }

      if (!isspace(gettoken(token, MAXLINE))) {
        printf("invalid syntax: %s", token);
        return 1;
      }

      defnptr = defn;
      while (gettoken(token, MAXLINE) != EOF && token[0] != '\n') {
        strcpy(defnptr, token);
        defnptr += strlen(token);
      }
      if (token[0] == '\0')
        return 0;

      install(name, defn);
      continue;
    }

    while (token[0] != '\n') {
      if ((np = lookup(token)) != NULL)
        printf("%s", np->defn);
      else
        printf("%s", token);

      if (gettoken(token, MAXLINE) == EOF)
        return 0;
    }

    if (token[0] == '\n')
      printf("\n");
  }

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

int skipstring(int);
int skipcomment();
int getch(void);

int gettoken(char *token, int lim) {
  int c;
  char *w = token;
  *w = '\0';

  if (isspace(c = getch()) && c != '\n') {
    *w++ = c;
    while (isspace(*w = getch()) && *w != '\n')
      w++;
    ungetch(*w);
    *w = '\0';
    return token[0];
  }

  while (c == '/') {
    if ((c = getch()) == '/') {
      while ((c = getch()) != '\n')
        ;
    } else if (c == '*') {
      c = skipcomment();
    } else {
      ungetch(c);
      c = '/';
      break;
    }
  }

  if (c == '"') {
    *w++ = c;
    while ((*w = getch()) != '"') {
      if (*w == '\\')
        *++w = getch();
      w++;
    }
    *++w = '\0';
    return token[0];
  }

  if (c == '\'') {
    *w++ = c;
    if ((*w++ = getch()) == '\\')
      *w++ = getch();
    *w++ = getch();
    *w = '\0';
    return token[0];
  }

  if (c == EOF)
    return c;

  *w++ = c;

  if (isalnum(c) || c == '_' || c == '#')
    for (; --lim > 0; w++)
      if (!isalnum(*w = getch()) && *w != '_') {
        ungetch(*w);
        break;
      }

  *w = '\0';
  return token[0];
}

int skipcomment() {
  int c;
  do {
    if ((c = getch()) == '*') {
      if ((c = getch()) == '/')
        break;
      else
        ungetch(c);
    }
  } while (c != EOF);

  if (c != EOF)
    c = getch();
  return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

/* getch: get a (possibly pushed-back) character */
int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
