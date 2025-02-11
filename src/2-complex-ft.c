#include "2-complex-ft.h"
#include "common.h"

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

extern float pi;

// O(n^2)
void complex_ft(float complex *out, const float *in, const size_t n) {
  for (size_t freq = 0; freq <= n; ++freq) {
    out[freq] = 0;
    for (size_t i = 0; i <= n; ++i) {
      const float t = (float)i / n;
      out[freq] += in[i] * cexpf(2 * I * pi * freq * t);
    }
  }
}

void complex_ft_main(void) {
  START_EXAMPLE;

  const size_t n = 10;
  float in[n + 1];
  memset(in, 0, sizeof(*in) * (n + 1));

  /*
   * NOTE: Let's we will mix a lot of perfect sound waves of different
   * frequencies, so that we can unmix them later with the fourier transform
   */
  mixing_frequency(in, n, 1, sinf);
  mixing_frequency(in, n, 7, cosf);

  float complex out[n + 1];
  complex_ft(out, in, n);

  print_array(/*   */ "in:  ", in, n + 1);
  print_array_complex("out: ", out, n + 1);
  END_EXAMPLE;
}
