#include <stdio.h>

int htoi(char s[]);

int main() {
  int i;

  i = htoi("0x11");
  printf("%d\n", i);

  i = htoi("0xA");
  printf("%d\n", i);

  i = htoi("0X1F");
  printf("%d\n", i);

  return 0;
}

int htoi(char s[]) {
  int i, val;

  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
    i = 2;
  } else {
    i = 0;
  }

  val = 0;
  while ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'A' && s[i] <= 'F')) {
    val = val * 16;
    if (s[i] >= '0' && s[i] <= '9') {
      val = val + (s[i] - '0');
    } else {
      val = val + (s[i] - 'A' + 10);
    }
    ++i;
  }

  return val;
}
