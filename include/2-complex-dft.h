#ifndef include_include_2_COMPLEX_DFT_H_
#define include_include_2_COMPLEX_DFT_H_

#include <complex.h>
#include <stddef.h>

void complex_dft_main(void);

void complex_dft(float complex *out, const float *in, const size_t n);

#endif // INCLUDE_INCLUDE_2-COMPLEX-FT_H_
