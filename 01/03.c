#include <stdio.h>

/* print Fahrenheit-Celcius table
    for fahr = 0, 20 ..., 300; floating-point version */
int main() {
  float fahr, celcius;
  float lower, upper, step;

  lower = 0;   /* lower limit of temperature scale */
  upper = 300; /* upper limit */
  step = 20;   /* step size */

  printf("fahr\tcelcius\n");

  fahr = lower;
  while (fahr <= upper) {
    celcius = (5.0 / 9.0) * (fahr - 32);
    printf("%4.0f\t%7.1f\n", fahr, celcius);
    fahr = fahr + step;
  }

  return 0;
}
