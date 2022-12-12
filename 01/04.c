#include <stdio.h>

/* print Fahrenheit-Celcius table
    for fahr = 0, 20 ..., 300; floating-point version */
int main() {
  float fahr, celcius;
  float lower, upper, step;

  lower = 0;   /* lower limit of temperature scale */
  upper = 300; /* upper limit */
  step = 20;   /* step size */

  printf("celcius\tfahr\n");

  celcius = lower;
  while (celcius <= upper) {
    fahr = (9.0 / 5.0) * celcius + 32;
    printf("%7.0f\t%4.0f\n", celcius, fahr);
    celcius = celcius + step;
  }

  return 0;
}
