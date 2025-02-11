#ifndef INCLUDE_INCLUDE_1_SIMPLE_DFT_H_
#define INCLUDE_INCLUDE_1_SIMPLE_DFT_H_

#include <stddef.h>

void simple_dft_main(void);

void simple_dft(float *out_sin, float *out_cos, const float *in,
                const size_t n);

#endif // INCLUDE_INCLUDE_1-SIMPLE-FT_H_
