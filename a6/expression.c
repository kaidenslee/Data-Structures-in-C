/**
 * -------------------------------------
 * @file  expression.c
 * -------------------------------------
 * @author Kaiden Lee, 169050073 leex5007@mylaurier.ca
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/
#include "expression.h"

/*
 * Convert infix expression string to postfix expression reprsented by queue data structure.
 * @param infixstr - string of infix expression.
 * @return - postfix expression in queue of QUEUE type.
*/
QUEUE infix_to_postfix(char *infixstr){
	QUEUE *q = malloc(sizeof(QUEUE));
	    q->length = 0;
	    q->front = NULL;
	    q->rear = NULL;

	    STACK *s = malloc(sizeof(STACK));
	    s->top = NULL;
	    s->length = 0;

	    for (int i = 0; infixstr[i] != '\0';) {
	        int type = mytype(infixstr[i]);

	        if (type == 0) {
	            int number = 0;
	            while (infixstr[i] >= '0' && infixstr[i] <= '9') {
	                number = number * 10 + (infixstr[i] - '0');
	                i++;
	            }
	            enqueue(q, new_node(number, 0));
	            continue;
	        }
	        else if (type == 2) {
	            push(s, new_node(infixstr[i++], 2));
	        }
	        else if (type == 3) {
	            while (s->top != NULL && s->top->type != 2) {
	                enqueue(q, pop(s));
	            }
	            pop(s);
	            i++;
	        }
	        else if (type == 1) {
	            while (s->top != NULL && priority(s->top->data) >= priority(infixstr[i])) {
	                enqueue(q, pop(s));
	            }
	            push(s, new_node(infixstr[i++], 1));
	        }
	        else {
	            i++;
	        }
	    }

	    while (s->top != NULL) {
	        enqueue(q, pop(s));
	    }

	    free(s);
	    return *q;
	}


/*
 * Evaluate and return the value postfix expression passed by queue.
 * @parame queue - postfix expression in queue of QUEUE type.
 ^ @return - value of postfix expression
*/
int evaluate_postfix(QUEUE queue){

	STACK *s = malloc(sizeof(STACK));
	    s->top = NULL;
	    s->length = 0;

	    NODE *current = queue.front;

	    while (current != NULL) {
	        if (current->type == 0) {
	            push(s, new_node(current->data, 0));
	        }
	        else if (current->type == 1) {
	            NODE *right = pop(s);
	            NODE *left = pop(s);

	            int result = 0;
	            switch (current->data) {
	                case '+': result = left->data + right->data; break;
	                case '-': result = left->data - right->data; break;
	                case '*': result = left->data * right->data; break;
	                case '/': result = left->data / right->data; break;
	            }

	            push(s, new_node(result, 0));

	            free(left);
	            free(right);
	        }
	        current = current->next;
	    }

	    int final_result = pop(s)->data;
	    free(s);
	    return final_result;
	}



/*
 * Evaluate and return the value of infix expression passed by string infixstr,
 * using infix_to_postfix() and evaluate_postfix() functions.
 * @param infixstr - string of infix expression.
 * @return - value of the infix expression.
*/
int evaluate_infix(char *infixstr){
	QUEUE postfix = infix_to_postfix(infixstr);
	    return evaluate_postfix(postfix);
	}

