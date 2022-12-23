#include <stdio.h>
#include <string.h>

void reverse(char[]);

int main() {
  char line[] = "this is a test";
  printf("%s\n", line);
  reverse(line);
  printf("%s\n", line);
  return 0;
}

void rreverse(char s[], int i, int j) {
  char c;

  if (i >= j) {
    return;
  }

  c = s[i];
  s[i] = s[j];
  s[j] = c;

  rreverse(s, i + 1, j - 1);
}

void reverse(char s[]) {
  rreverse(s, 0, strlen(s) - 1);
}
