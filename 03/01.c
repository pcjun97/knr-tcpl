#include <stdio.h>

int binsearch(int x, int v[], int n);

int main() {
  int i;
  int test_data[10];

  for (i = 0; i < 10; i++) {
    test_data[i] = i * 3;
  }

  i = binsearch(15, test_data, 6);
  printf("%d\n", i);

  return 0;
}

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n) {
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low < high) {
    mid = (low + high) / 2;
    if (x <= v[mid])
      high = mid;
    else
      low = mid + 1;
  }

  return (v[high] == x) ? high : -1;
}
