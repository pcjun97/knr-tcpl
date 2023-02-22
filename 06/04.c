#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100

struct tnode {
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
struct tnode *sorttree(struct tnode *, struct tnode *);
void treeprint(struct tnode *);
int getword(char *, int);

int main(int argc, char *argv[]) {
  struct tnode *root, *sortroot;
  char word[MAXWORD];

  root = sortroot = NULL;
  while (getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0]))
      root = addtree(root, word);
  }
  sortroot = sorttree(sortroot, root);
  treeprint(sortroot);

  return 0;
}

struct tnode *addtosorttree(struct tnode *s, struct tnode *p);

struct tnode *sorttree(struct tnode *s, struct tnode *p) {
  if (p == NULL)
    return s;

  s = addtosorttree(s, p);
  s = sorttree(s, p->left);
  s = sorttree(s, p->right);
  return s;
}

struct tnode *talloc(void);

struct tnode *addtosorttree(struct tnode *s, struct tnode *p) {
  int cond;

  if (p == NULL)
    return s;

  if (s == NULL) {
    s = talloc();
    s->word = p->word;
    s->count = p->count;
    s->left = s->right = NULL;
    return s;
  }

  cond = p->count - s->count;
  if (cond == 0)
    cond = strcmp(s->word, p->word);

  if (cond < 0)
    s->right = addtosorttree(s->right, p);
  else if (cond > 0)
    s->left = addtosorttree(s->left, p);

  return s;
}

char *_strdup(char *);

struct tnode *addtree(struct tnode *p, char *w) {
  int cond;

  if (p == NULL) {
    p = talloc();
    p->word = _strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0) {
    p->count++;
  } else if (cond < 0)
    p->left = addtree(p->left, w);
  else
    p->right = addtree(p->right, w);

  return p;
}

void treeprint(struct tnode *p) {
  int i;

  if (p == NULL)
    return;

  treeprint(p->left);
  printf("%4d %s\n", p->count, p->word);
  treeprint(p->right);
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

int getch(void);
void ungetch(int);

int getword(char *word, int lim) {
  int c;
  char *w = word;

  while (isspace(c = getch()))
    ;

  if (c == EOF)
    return c;

  *w++ = c;

  if (isalpha(c))
    for (; --lim > 0; w++)
      if (!isalpha(*w = getch())) {
        ungetch(*w);
        break;
      }

  *w = '\0';
  return word[0];
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
