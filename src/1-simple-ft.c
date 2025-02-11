#include "1-simple-ft.h"
#include "common.h"

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern float pi;

// O(n^2)
void simple_ft(float *out_sin, float *out_cos, const float *in,
               const size_t n) {
  for (size_t freq = 0; freq <= n; ++freq) {
    out_sin[freq] = 0;
    out_cos[freq] = 0;
    for (size_t i = 0; i <= n; ++i) {
      const float t = (float)i / n;
      out_sin[freq] += in[i] * sinf(2 * pi * freq * t);
      out_cos[freq] += in[i] * cosf(2 * pi * freq * t);
    }
  }
}

void simple_ft_main(void) {
  START_EXAMPLE;
  /*
   * NOTE: Let's imagine our input audio has 10 samples
   */
  const size_t n = 10;
  float in[n + 1];
  memset(in, 0, sizeof(*in) * (n + 1));

  /*
   * NOTE: Let's we will mix a lot of perfect sound waves of different
   * frequencies, so that we can unmix them later with the fourier transform
   */
  mixing_frequency(in, n, 1, sinf);
  mixing_frequency(in, n, 8, sinf);
  mixing_frequency(in, n, 3, cosf);
  mixing_frequency(in, n, 7, cosf);

  float out_sin[n + 1];
  float out_cos[n + 1];
  simple_ft(out_sin, out_cos, in, n);

  print_array("in:      ", in, n + 1);
  print_array("out_sin: ", out_sin, n + 1);
  print_array("out_cos: ", out_cos, n + 1);
  END_EXAMPLE;
}
