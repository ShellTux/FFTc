#ifndef INCLUDE_INCLUDE_COMMON_H_
#define INCLUDE_INCLUDE_COMMON_H_

#include <complex.h>
#include <stddef.h>

#define START_EXAMPLE printf("\n---Start: %s------\n\n", __FUNCTION__)
#define END_EXAMPLE printf("\n---End: %s------\n\n", __FUNCTION__)

void print_array(const char *message, const float *in, const size_t n);
void print_array_complex(const char *message, const float complex *in,
                         const size_t n);
void mixing_frequency(float *in, const size_t n, const float frequency,
                      float (*trig_func)(float));

#endif // INCLUDE_INCLUDE_COMMON_H_
