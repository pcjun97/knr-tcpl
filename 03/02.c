#include <stdio.h>
#define MAXLINE 1000

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main() {
  char line[MAXLINE];

  escape(line, "this is 	 a tab and some slashes \\\\\n");
  printf("%s\n", line);

  unescape(line, line);
  printf("%s\n", line);

  return 0;
}

/* convert escape characters into visible escape sequences */
void escape(char s[], char t[]) {
  int i, j;
  for (i = j = 0; t[i] != '\0'; i++) {
    switch (t[i]) {
    case '\n':
      s[j++] = '\\';
      s[j++] = 'n';
      break;
    case '\t':
      s[j++] = '\\';
      s[j++] = 't';
      break;
    case '\\':
      s[j++] = '\\';
      s[j++] = '\\';
      break;
    default:
      s[j++] = t[i];
      break;
    }
  }
}

/* convert visible escape sequences into escape characters */
void unescape(char s[], char t[]) {
  int i, j;
  for (i = j = 0; t[j] != '\0'; i++) {
    if (t[j] == '\\') {
      switch (t[j + 1]) {
      case 'n':
        s[i] = '\n';
        j += 2;
        break;
      case 't':
        s[i] = '\t';
        j += 2;
        break;
      case '\\':
        s[i] = '\\';
        j += 2;
        break;
      default:
        s[i] = t[j++];
        break;
      }
    } else {
      s[i] = t[j++];
    }
  }
}
