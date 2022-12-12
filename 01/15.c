#include <stdio.h>

float fahrtocelcius(float fahr);

int main() {
  float fahr, celcius;
  float lower, upper, step;

  lower = 0;   /* lower limit of temperature scale */
  upper = 300; /* upper limit */
  step = 20;   /* step size */

  printf("fahr\tcelcius\n");

  fahr = lower;
  while (fahr <= upper) {
    celcius = fahrtocelcius(fahr);
    printf("%4.0f\t%7.1f\n", fahr, celcius);
    fahr = fahr + step;
  }

  return 0;
}

float fahrtocelcius(float fahr) {
  float celcius;
  celcius = (5.0 / 9.0) * (fahr - 32);
  return celcius;
}
