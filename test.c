#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool PRNG_INITIALIZED = false;

/* Returns a random number between a and b. */
double uniform(double a, double b)
{
	if (!PRNG_INITIALIZED) {
		srand(time(NULL));
		PRNG_INITIALIZED = true;
	}

	/* Get a number between 0 and 1. */
	double r = (double) rand() / (double) RAND_MAX;

	/* Adjust it to be within the desired interval. */
	double s = (b - a) * r + a;

	return s;
}

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

/* Generate n complex numbers and apply mandelbrot() to them. */
void run(int n, int threshold, double x_min, double x_max, double y_min, double y_max)
{

	int q = 0;
	#pragma omp parallel for reduction(+:q)
	for (int i = 0; i < n; i++) {
		double x = uniform(x_min, x_max);
		double y = uniform(y_min, y_max);
		double complex z = x + I*y;
		int k = mandelbrot(z, threshold);

		if (k == 0)
			q++;

		//printf("%f\t%f\t%d\t%d\n", x, y, k, threshold);
	}
	double m = (double) q / (double) n;
	double s = sqrt(1/(double)n * ( (double)(n-q)*m*m + (double)q*(1-m)*(1-m)));

	double A = (x_max - x_min) * (y_max - y_min);
	double r = A * m;
	double u = A * s / sqrt((double) n);
	printf("k\t= %d\nN\t= %d\nA\t= %f\nu(A)\t= %f\n", q, n, r, u);
}

int main()
{
	int n		= 1000000;
	int threshold	= 1000;
	run(n, threshold, -2, 2, -2, 2);



	return 0;
}
