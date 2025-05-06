/**
 * -------------------------------------
 * @file  polynomial.c
 * -------------------------------------
 *
 * @version 2025-01-22
 *
 * -------------------------------------
 */


#include "polynomial.h"
/**
 * Cmpute and return the value of the (n-1)-th degree polynomial
 * p(x) = p[0]*x^{n-1} +  p[1]*x^{n-2} +...+ p[n-2]*x^1 + p[n-1]*x^0
 * using Horner's algorithm (https://en.wikipedia.org/wiki/Horner%27s_method)
 *
 * @param *p - pointer to float number array
 * @param n  - the number of coefficients
 * @return - the value of the above polynomial
 */
float horner(float *p, int n, float x){

	if(n <= 0){
		return 0.0;
	}

	float result = p[0];

	for(int i = 1; i < n; i++){
		result = result * x + p[i];
	}

	return result;


}

/**
 * Cmpute the derivative of input (n-1)-th degree polynomial
 * p(x) = p[0]*x^{n-1} +  p[1]*x^{n-2} +...+ p[n-2]*x^1 + p[n-1]*x^0
 * output the coefficients of the derivative polynomial in an array.
 * The derivative of the above polynomial p(x) is as follows.
 * p'(x) = (n-1)* p[0]*x^{n-2} +  (n-2)*p[1]*x^{n-3} +...+ p[n-2]*x^0
 *
 * @param *p - pointer to coefficient array of input polynomial.
 * @param *d - pointer to coefficient array of output polynomial.
 * @param n  - the number of coefficients of the input polynomial
 */
void derivative(float *p, float *d, int n){

	if (n <= 1){
		return;
	}

	for(int i = 0; i < (n-1);i++){
		d[i] = (n-1-i)*p[i];
	}

	return;
}



/**
 * Compute approximate real root x of polynomial p(x) using Newton's
 * method(https://en.wikipedia.org/wiki/Newton%27s_method).
 * Use fault tolerant 1e-6 (or 0.000001) and maximum 100 iterations.
 *
 * @param *p - pointer to coefficient array of input polynomial.
 * @param n  - the number of coefficients of the input polynomial
 * @param x0 - start point for Newton method
 * @return -  the root if found, otherwise x0.
 */
float newton(float *p, int n, float x0){
	float tol = 1e-6;
	int max_iter = 100;
	float d[n-1];

	derivative(p, d, n);
	for (int iter = 0; iter < max_iter; iter++){
		float fx = horner(p, n, x0);
		float fpx = horner(d, n-1, x0);

		if (fpx == 0){
			return x0;
		}

		float x_new = x0 - fx / fpx;

		if(x_new - x0 < tol && x_new - x0 > - tol){
			return x_new;
		}

		x0 = x_new;
	}

	return x0;


}








