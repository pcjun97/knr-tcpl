#include <limits.h>

int isuppercache[UCHAR_MAX + 1];
int isuppercacheinit = 0;

/* saves space */
int sisupper(int c) {
  return c >= 'A' && c <= 'Z';
}

/* saves time */
int tisupper(int c) {
  int i;
  if (!isuppercacheinit) {
    for (i = 0; i <= UCHAR_MAX; i++)
      isuppercache[i] = sisupper(i);
    isuppercacheinit = 1;
  }

  return isuppercache[c];
}
