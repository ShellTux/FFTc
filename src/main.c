#include "1-simple-ft.h"
#include "2-complex-ft.h"

#include <math.h>

float pi;

int main(void) {
  pi = atan2f(1, 1) * 4;

  simple_ft_main();
  complex_ft_main();

  return 0;
}
