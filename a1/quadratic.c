/**
 * -------------------------------------
 * @file  quadratic.c
 * -------------------------------------
 * @author Kaiden Lee, 169050073 leex5007@mylaurier.ca
 *
 * @version 2025-01-13
 *
 * -------------------------------------
 */

#include "quadratic.h"
#include <math.h>
#define EPSILON 1e-6

/**
 * Compute and return solution type of given quadratic equation ax*x + bx + c = 0
 *
 * @param a  - quadratic coefficient
 * @param b  - linear coefficient
 * @param c - constant coefficient
 * @return - 0 if not quadratic equation, i.e. a=0;
 *           1 for one unique real solution;
 *           2 for two distinct real solutions;
 *           3 for two complex solutiions
 */
int solution_type(float a, float b, float c){
	int t = -1;

	if(fabs(a) < EPSILON){
		t=0;
	}
	else{
		float disc = b * b - 4 * a * c;

		if(fabs(disc) < EPSILON){
			t=1;
		}
		else if(disc > 0){
			t = 2;
		}
		else{
			t = 3;
		}
	}

	return t;
}

/**
 * Compute and return unique or bigger real roots of given quadratic equation ax*x + bx + c = 0 of types 1 and 2.
 * @param a  - quadratic coefficient
 * @param b  - linear coefficient
 * @param c - constant coefficient
 * @return - the unique real root or the bigger real root if the quadratic equation has two distinct real roots
             Ohterwise, return 0.
 */
float real_root_big(float a, float b, float c){
	if(solution_type(a, b, c) == 1){
		return -b/(2*a);
	} else if (solution_type(a, b, c) == 2){
		float disc = b*b - 4*a*c;
		float root1 = (-b + sqrt(disc)) / (2*a);
		float root2 = (-b - sqrt(disc)) / (2*a);
		return (root1 > root2) ? root1 : root2;
	}
	else{
		return 0;
	}
}

/**
 * Compute and return unique or smaller real roots of given quadratic equation ax*x + bx + c = 0 of types 1 and 2.
 * @param a  - quadratic coefficient
 * @param b  - linear coefficient
 * @param c - constant coefficient
 * @return - 0 if not a == 0
             1 if having two complex solutions
             2 if            the unique real root or the smaller real root if the quadratic equation has two distinct real roots
             Ohterwise, return 0.
 */
float real_root_small(float a, float b, float c){
	if (solution_type(a, b, c) == 1) {
	        return -b / (2 * a);

	    } else if (solution_type(a, b, c) == 2) {
	        float disc = b * b - 4 * a * c;
	        float root1 = (-b + sqrt(disc)) / (2 * a);
	        float root2 = (-b - sqrt(disc)) / (2 * a);
	        return (root1 < root2) ? root1 : root2;
	    } else {
	        return 0;
	    }

}


