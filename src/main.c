#include "1-simple-dft.h"
#include "2-complex-dft.h"

#include <math.h>

float pi;

int main(void) {
  pi = atan2f(1, 1) * 4;

  /*
   * NOTE: The fourier transform tries to solve a problem in Computer Science
   * and other fields about returning the frequencies inside a analog input.
   *
   * For example: Imagine you have an input signal composed of multiple sound
   * frequencies, how would you go about and discover if a given frequency is
   * present in the input analog signal?
   *
   * We know it's very simple to mix different frequencies into a sound.
   * But the reverse seems impossible at first glance.
   *
   * This repo tries to explain what and how a Fourier Transform (ft) works. We
   * will first dive into a DFT (Direct Fourier Transform) and after that a FFT
   * (Fast Fourier Transform). And why the necessity for both algorithms.
   *
   * For convenience the c source files are numbered in order for you to follow:
   * 1 - src/1-simple-dft.c
   * 2 - src/2-complex-dft.c
   * ...
   *
   * So when ready feel free, to move on.
   */

  simple_dft_main();
  complex_dft_main();

  return 0;
}
