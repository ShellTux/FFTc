#include "common.h"
#include "complex.h"

#include <complex.h>
#include <stdio.h>

extern float pi;

void print_array(const char *message, const float *in, const size_t n) {
  printf("%s[", message);
  for (size_t i = 0; i < n; ++i) {
    if (i > 0) {
      printf(", ");
    }
    printf("%.2f", in[i]);
  }

  printf("]\n");
}

void print_array_complex(const char *message, const float complex *in,
                         const size_t n) {
#if 1
  if (message != NULL) {
    printf("%s", message);
  }
  for (size_t i = 0; i < n; ++i) {
    printf("%02zu: %5.2f + i %5.2f\n", i, crealf(in[i]), cimagf(in[i]));
  }
#else
  float in_cos[n + 1];
  float in_sin[n + 1];

  for (size_t i = 0; i <= n; ++i) {
    in_cos[i] = crealf(in[i]);
    in_sin[i] = cimagf(in[i]);
  }

  print_array(message, in_cos, n);
  print_array(message, in_sin, n);
#endif
}

void mixing_frequency(float *in, const size_t n, const float frequency,
                      float (*trig_func)(float)) {
  for (size_t i = 0; i <= n; ++i) {
    const float t = (float)i / n;
    in[i] += trig_func(2 * pi * t * frequency);
  }
}
