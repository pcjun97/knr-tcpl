#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct key {
  char *word;
  int count;
} keytab[] = {
    {"auto", 0},     {"break", 0},  {"case", 0},     {"char", 0},   {"const", 0},    {"continue", 0}, {"default", 0},
    {"do", 0},       {"double", 0}, {"else", 0},     {"enum", 0},   {"extern", 0},   {"float", 0},    {"for", 0},
    {"goto", 0},     {"if", 0},     {"int", 0},      {"long", 0},   {"register", 0}, {"return", 0},   {"short", 0},
    {"signed", 0},   {"sizeof", 0}, {"static", 0},   {"struct", 0}, {"switch", 0},   {"typedef", 0},  {"union", 0},
    {"unsigned", 0}, {"void", 0},   {"volatile", 0}, {"while", 0},
};
#define NKEYS (sizeof keytab / sizeof(keytab[0]))

#define MAXWORD 100

struct tnode {
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *, int);
int getword(char *, int);
int binsearch(char *, struct key *, int);

int main(int argc, char *argv[]) {
  int n;
  struct tnode *root;
  char word[MAXWORD];

  if (argc > 2) {
    printf("too many arguments");
    return 1;
  }

  n = 6;
  if (argc == 2) {
    if (!isnumber(argv[1][0])) {
      printf("not a number: %s\n", argv[1]);
      return 1;
    }
    n = atoi(argv[1]);
  }

  root = NULL;
  while (getword(word, MAXWORD) != EOF)
    if (word[0] == '_' || (isalpha(word[0]) && binsearch(word, keytab, NKEYS) < 0))
      root = addtree(root, word);
  treeprint(root, n);

  return 0;
}

struct tnode *talloc(void);
char *_strdup(char *);

struct tnode *addtree(struct tnode *p, char *w) {
  int cond;

  if (p == NULL) {
    p = talloc();
    p->word = _strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0)
    p->count++;
  else if (cond < 0)
    p->left = addtree(p->left, w);
  else
    p->right = addtree(p->right, w);

  return p;
}

char *_treeprint(struct tnode *, int, char *, int *);

void treeprint(struct tnode *p, int sim) {
  char *w;
  int found = 0;
  if ((w = _treeprint(p, sim, NULL, &found)) != NULL && found)
    printf("%s\n", w);
}

char *_treeprint(struct tnode *p, int sim, char *last, int *found) {
  if (p != NULL) {
    last = _treeprint(p->left, sim, last, found);

    if (last != NULL) {
      if (strncmp(last, p->word, sim) == 0) {
        printf("%s\n", last);
        *found = 1;
      } else if (*found) {
        printf("%s\n\n", last);
        *found = 0;
      }
    }
    last = p->word;

    return _treeprint(p->right, sim, last, found);
  }
  return last;
}

struct tnode *talloc(void) {
  return (struct tnode *)malloc(sizeof(struct tnode));
}

char *_strdup(char *s) {
  char *p;

  p = (char *)malloc(strlen(s) + 1);
  if (p != NULL)
    strcpy(p, s);
  return p;
}

int binsearch(char *word, struct key tab[], int n) {
  int cond;
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if ((cond = strcmp(word, tab[mid].word)) < 0)
      high = mid - 1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

int skipstring(int);
int skipcomment();
int getch(void);
void ungetch(int);

int getword(char *word, int lim) {
  int c;
  char *w = word;

  do {
    while (isspace(c = getch()))
      ;

    if (c == '"' || c == '\'')
      c = skipstring(c);

    if (c == '/') {
      if ((c = getch()) == '/') {
        while ((c = getch()) != '\n')
          ;
      } else if (c == '*') {
        c = skipcomment();
      } else {
        ungetch(c);
        c = '/';
      }
    }
  } while (isspace(c));

  if (c == EOF)
    return c;

  *w++ = c;

  if (isalpha(c) || c == '_' || c == '#')
    for (; --lim > 0; w++)
      if (!isalnum(*w = getch()) && *w != '_') {
        ungetch(*w);
        break;
      }

  *w = '\0';
  return word[0];
}

int skipstring(int q) {
  int c;
  do {
    if ((c = getch()) == '\\') {
      getch();
      c = getch();
    }
  } while (c != q && c != EOF);

  if (c == q)
    c = getch();

  return c;
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