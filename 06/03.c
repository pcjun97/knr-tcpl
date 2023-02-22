#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *noise[] = {"a", "an", "and", "the"};
#define NNOISE (sizeof noise / sizeof(noise[0]))

#define MAXWORD 100
#define MAXLINES 100

struct ll {
  int n;
  struct ll *next;
};

struct tnode {
  char *word;
  struct ll *lines;
  struct tnode *left;
  struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
int getword(char *, int);
int binsearch(char *, char **, int);

int main(int argc, char *argv[]) {
  struct tnode *root;
  char word[MAXWORD];
  int n = 1;

  root = NULL;
  while (getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0]) && binsearch(word, noise, NNOISE) < 0)
      root = addtree(root, word, n);
    if (word[0] == '\n')
      n++;
  }
  treeprint(root);

  return 0;
}

struct tnode *talloc(void);
char *_strdup(char *);
struct ll *addline(struct ll *, int);

struct tnode *addtree(struct tnode *p, char *w, int line) {
  int cond;

  if (p == NULL) {
    p = talloc();
    p->word = _strdup(w);
    p->lines = addline(NULL, line);
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0) {
    addline(p->lines, line);
  } else if (cond < 0)
    p->left = addtree(p->left, w, line);
  else if (cond > 0)
    p->right = addtree(p->right, w, line);

  return p;
}

void treeprint(struct tnode *p) {
  int i;
  struct ll *pline;

  if (p == NULL)
    return;

  treeprint(p->left);

  printf("%s", p->word);
  pline = p->lines;
  while (pline != NULL) {
    printf(" %d", pline->n);
    pline = pline->next;
  }
  printf("\n");

  treeprint(p->right);
}

struct tnode *talloc(void) {
  return (struct tnode *)malloc(sizeof(struct tnode));
}

struct ll *lalloc(void);

struct ll *addline(struct ll *p, int line) {
  int cond;

  if (p == NULL) {
    p = lalloc();
    p->n = line;
    p->next = NULL;
  } else if (p->n != line && p->next == NULL)
    p->next = addline(p->next, line);
  else if (p->n != line)
    addline(p->next, line);
  return p;
}

struct ll *lalloc(void) {
  return (struct ll *)malloc(sizeof(struct ll));
}

char *_strdup(char *s) {
  char *p;

  p = (char *)malloc(strlen(s) + 1);
  if (p != NULL)
    strcpy(p, s);
  return p;
}

int binsearch(char *word, char *w[], int n) {
  int cond;
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if ((cond = strcmp(word, w[mid])) < 0)
      high = mid - 1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

int getch(void);
void ungetch(int);

int getword(char *word, int lim) {
  int c;
  char *w = word;

  while (isspace(c = getch()) && c != '\n')
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
