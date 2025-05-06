/**
 * -------------------------------------
 * @file  bigint.c
 * -------------------------------------
 * @author Kaiden Lee, 169050073 leex5007@mylaurier.ca
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/

#include "bigint.h"
#include "dllist.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Creates and returns BIGINT object by converting the digit string.
 */
BIGINT bigint(char *digitstr){
	BIGINT bigint = {0, NULL, NULL};

	    if (digitstr == NULL || *digitstr == '\0') {
	        return bigint;
	    }

	    for (int i = 0; digitstr[i] != '\0'; i++) {
	        if (digitstr[i] < '0' || digitstr[i] > '9') {
	            printf("Error: Invalid digit in input.\n");
	            exit(1);
	        }

	        NODE *newNode = dll_node(digitstr[i] - '0');
	        dll_insert_end(&bigint, newNode);
	    }

	    return bigint;
	}


/*
 * Add two BIGINT operants and returns the sum in BIGINT type.
 * @param oprand1  - first operand of BIGINT type.
 * @param oprand2  - second operand of BIGINT type.
 * @return - the sum of oprand1 and oprand2 in BIGINT type.
 */
BIGINT bigint_add(BIGINT oprand1, BIGINT oprand2){
	BIGINT result = {0, NULL, NULL};

	    NODE *ptr1 = oprand1.end;
	    NODE *ptr2 = oprand2.end;
	    int carry = 0;

	    while (ptr1 != NULL || ptr2 != NULL || carry > 0) {
	        int digit1 = (ptr1 != NULL) ? ptr1->data : 0;
	        int digit2 = (ptr2 != NULL) ? ptr2->data : 0;
	        int sum = digit1 + digit2 + carry;
	        carry = sum / 10;
	        int digit = sum % 10;

	        NODE *newNode = dll_node(digit);
	        dll_insert_start(&result, newNode);

	        if (ptr1 != NULL) ptr1 = ptr1->prev;
	        if (ptr2 != NULL) ptr2 = ptr2->prev;
	    }

	    return result;
	}


/*
 * Compute and return Fibonacci(n)
 * @param n - input positive integer
 * @return  - Fibonacci(n) in BIGINT type
 */
BIGINT bigint_fibonacci(int n){
	if (n == 0) return bigint("0");
	    if (n == 1) return bigint("1");

	    BIGINT a = bigint("0");
	    BIGINT b = bigint("1");
	    BIGINT temp;

	    for (int i = 2; i <= n; i++) {
	        temp = bigint_add(a, b);
	        dll_clean(&a);
	        a = b;
	        b = temp;
	    }

	    dll_clean(&a);
	    return b;
	}

