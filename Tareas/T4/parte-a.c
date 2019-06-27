#include "integral.h"

double integral(Funcion f, void *ptr, double xi, double xf, int n) {
  	double nd = (double) n;
	double h = (xf - xi)/nd;
	double t = (f(ptr, xi) + f(ptr,xf))/2.0;
	double sum = 0.0;
	for (int k = 1; k < n; k++) {
		sum += f(ptr, xi + k*h);
	}
	double result = h*(t + sum);
	return result;
}
