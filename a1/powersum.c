/**
 * -------------------------------------
 * @file  powersum.c
 * -------------------------------------
 * @author Kaiden Lee, 169050073 leex5007@mylaurier.ca
 *
 * @version 2025-01-13
 *
 * -------------------------------------
 */
#include "powersum.h"

/**
 * Depect if overflow in power computing of b to power of n
 *
 * @param b - the base
 * @param n - the exponent
 * @return - 1 if overflow happens, 0 otherwise
 */
int power_overflow(int b, int n){
	const int MAX_INT = 2147483647;
	if (n == 0 || b == 0 || b == 1 || b == -1){
		return 0;
	}
	else if (n < 0){
		return 1;
	}

	int result = 1;
	for(int i = 0; i < n; i++){
		if(result > MAX_INT/ b){
			return 1;
		}

		result *= b;
	}

	return 0;
}

/**
 * Compute and return b to power of n.
 *
 * @param b - the base
 * @param n - the exponent
 * @return - b to the power of n if no overflow happens, 0 otherwise
 */
int mypower(int b, int n){
	if(power_overflow(b, n) == 0){
		int result = 1;
		for (int i = 0; i < n; i++){
			result *= b;
		}
		return result;
	}
	else{
		return 0;
	}
}


/**
 * Compute and return the sum of powers.
 *
 * @param b - the base
 * @param n - the exponent
 * @return -  the sum of powers if no overflow happens, 0 otherwise
 */
int powersum(int b, int n){
	if(power_overflow(b, n) == 0){
		if(b == 1){
			return n +1;
		}
		if(b == 0){
			return 1;
		}
		int sum = 0;
		int power = 1;
		for(int i = 0; i <= n; i++){
			sum += power;
			power *= b;

		}
		return sum;
	}
	else{
		return 0;
	}
}
