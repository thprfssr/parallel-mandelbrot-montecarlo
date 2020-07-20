#include <complex.h>
#include <stdio.h>

/* Returns the number of iterations needed until the magnitude of z exceeds 2.
 * If this doesn't happen after the threshold, then the function returns 0. */
int mandelbrot(double complex c, int threshold)
{
	double complex z = 0;
	for (int i = 1; i <= threshold; i++) {
		z = cpow(z, 2) + c;
		if (cabs(z) > 2)
			return i;
	}
	return 0;
}

int main()
{
	return 0;
}