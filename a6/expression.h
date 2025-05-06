/**
 * -------------------------------------
 * @file  expression.h
 * -------------------------------------
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/

#include "common.h"
#include "stack.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef SRC_EXPRESSION_H_
#define SRC_EXPRESSION_H_

/*
 * Convert infix expression string to postfix expression reprsented by queue data structure.
 * @param infixstr - string of infix expression.
 * @return - postfix expression in queue of QUEUE type.
*/
QUEUE infix_to_postfix(char *infixstr);

/*
 * Evaluate and return the value postfix expression passed by queue.
 * @parame queue - postfix expression in queue of QUEUE type.
 ^ @return - value of postfix expression
*/
int evaluate_postfix(QUEUE queue);

/*
 * Evaluate and return the value of infix expression passed by string infixstr,
 * using infix_to_postfix() and evaluate_postfix() functions.
 * @param infixstr - string of infix expression.
 * @return - value of the infix expression.
*/
int evaluate_infix(char *infixstr);
#endif /* SRC_EXPRESSION_H_ */
