#include "1-simple-dft.h"
#include "common.h"

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern float pi;

// O(n^2)
void simple_dft(float *out_sin, float *out_cos, const float *in,
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

void simple_dft_main(void) {
  START_EXAMPLE;
  /*
   * When we record an analog sound wave, what computers do
   * is record the amplitude as a sample. They do this many times a second, so
   * what we end up is something like this:
   *
   * [1 1 1 1 0 0 0 0]
   *
   * You might recognise this as a square wave.
   * We know that the input signal has 8 samples. But we don't have any
   * information about the duration of time or the period of the signal.
   *
   * Going forward we will work with buffer such that the last sample
   * corresponds to a period of 1.
   *
   * Let's start with a n = 10 samples input signal
   * The reason we allocate a buffer of n + 1 size, is because arrays in c are 0
   * index based, and we would like to iterate until <= n so we can have a
   * period = 1 in our input signal buffer.
   */
  const size_t n = 10;
  float in[n + 1];
  memset(in, 0, sizeof(*in) * (n + 1));

  /*
   * Now to simulate we have a lot of different frequency sound waves in our
   * input signal, we will mix known sin and cos waves of different frequencies.
   * Let's start simple by mixing a 1Hz sin wave and a 7Hz cos wave.
   *
   * Check the mixing_frequency function to check how the math works behind
   * mixing a given frequency wave.
   */
  mixing_frequency(in, n, 1, sinf);
  mixing_frequency(in, n, 7, cosf);
  print_array("in:      ", in, n + 1);
  /*
   * The result input signal will be:
   * [1  0.28  0.14  1.76  0.90 -1  -0.28  -0.14  -1.76 -0.90  1]
   *
   *     ^        *
   * .98 |        *                    *
   * .84 |        *  *                 *
   * .70 |        *  *                 *
   * .56 |        *  *                 *
   * .42 |        *  *                 *
   * .28 |  *     *  *                 *
   * .14 |  *  *  *  *                 *
   *     o--1--2--3--4--5--6--7--8--9--10->
   *-.14 |              *  *  *  *  *
   *-.28 |              *  *     *  *
   *-.42 |              *        *  *
   *-.56 |              *        *  *
   *-.70 |              *        *  *
   *-.84 |              *        *  *
   *-.98 |              *        *  *
         |                       *
         |                       *
   */

  /*
   * The Fourier Transform:
   * The goal is to multiply our input analog wave with a known sin wave of a
   * given frequency, for example:
   *
   * sin wave 1Hz sin(2 * pi * 1 * t):
   * [0  0.59  0.95  0.95  0.59  0  -0.59  -0.95  -0.95  -0.59  0]
   *     ^
   * .95 |     *  *
   *     |     *  *
   * .59 |  *  *  *  *
   *     |  *  *  *  *
   *     o--1--2--3--4--5--6--7--8--9--10->
   *     |                 *  *  *  *
   *-.59 |                 *  *  *  *
   *     |                    *  *
   *-.95 |                    *  *
   *
   *
   * The result of in .* sin(2 * pi * freq * t):
   * [0   0.16   0.14   1.67   0.53  0   0.16   0.14   1.67 0.53  0]
   */
  float out_sin[n + 1];
  float out_cos[n + 1];
  simple_dft(out_sin, out_cos, in, n);

  print_array("out_sin: ", out_sin, n + 1);
  print_array("out_cos: ", out_cos, n + 1);
  END_EXAMPLE;
}
