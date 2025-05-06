/**
 * -------------------------------------
 * @file  expression_symbol.c
 * -------------------------------------
 * @author Kaiden Lee, 169050073 leex5007@mylaurier.ca
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/
#include "expression_symbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Convert symbolic infix expression string to postfix expression in QUEUE type
 * @param ht - pointer to a HASHTABLE
 * @param infixstr - pointer to string of infix expression
 * @return - postfix exprssion in QUEUE type
 */
QUEUE infix_to_postfix_symbol(HASHTABLE *ht, char *infixstr){
	QUEUE queue = {0, NULL, NULL};
	    STACK stack = {0, NULL};
	    int i = 0;
	    while (infixstr[i]) {
	        if (isspace(infixstr[i])) {
	            i++;
	            continue;
	        }

	        if (isalpha(infixstr[i])) {
	            char symbol[20] = {0};
	            int j = 0;
	            while (isalpha(infixstr[i])) {
	                symbol[j++] = infixstr[i++];
	            }
	            symbol[j] = '\0';
	            HNODE *hn = hashtable_search(ht, symbol);
	            if (hn) {
	                enqueue(&queue, new_node(hn->data.value, 0));
	            } else {
	                enqueue(&queue, new_node(0, 0));
	            }
	        } else if (isdigit(infixstr[i])) {
	            char num[20] = {0};
	            int j = 0;
	            while (isdigit(infixstr[i])) {
	                num[j++] = infixstr[i++];
	            }
	            enqueue(&queue, new_node(atoi(num), 0));
	        } else if (infixstr[i] == '(') {
	            push(&stack, new_node('(', 2));
	            i++;
	        } else if (infixstr[i] == ')') {
	            while (stack.top && stack.top->data != '(') {
	                enqueue(&queue, pop(&stack));
	            }
	            NODE *lp = pop(&stack);
	            if (lp) free(lp);
	            i++;
	        } else {
	            while (stack.top && stack.top->type == 1 && priority(stack.top->data) >= priority(infixstr[i])) {
	                enqueue(&queue, pop(&stack));
	            }
	            push(&stack, new_node(infixstr[i], 1));
	            i++;
	        }
	    }

	    while (stack.top) {
	        enqueue(&queue, pop(&stack));
	    }

	    return queue;
	}

/* Evaluate symbolic infix expression string.
 * @param ht - pointer to a HASHTABLE
 * @param infixstr - pointer to string of infix expression
 * @return  - the value of the infix expression.
 */
int evaluate_infix_symbol(HASHTABLE *ht, char *infixstr){
	if (!infixstr || strlen(infixstr) == 0) return 0;
	    char *temp = strdup(infixstr);
	    if (!temp) return 0;
	    QUEUE queue = infix_to_postfix_symbol(ht, temp);
	    int result = evaluate_postfix(queue);
	    clean_queue(&queue);
	    free(temp);
	    return result;
	}

/* Evaluate postfix expression.
 * @param queue - postfix queue
 * @return  - the value of the postfix exprssion.
 */
int evaluate_postfix(QUEUE queue){
	STACK stack = { 0 };
	    int type = 0;
	    NODE *p = queue.front;
	    while (p) {
	        type = p->type;

	        if (type == 0) {    // operant
	            push(&stack, new_node(p->data, 0));
	        } else if (type == 1) {  // operator
	            int operator = p->data;
	            NODE *oprand2 = pop(&stack);

	            if (operator == '+')
	                stack.top->data = stack.top->data + oprand2->data;
	            else if (operator == '-')
	                stack.top->data = stack.top->data - oprand2->data;
	            else if (operator == '*')
	                stack.top->data = stack.top->data * oprand2->data;
	            else if (operator == '/')
	                stack.top->data = stack.top->data / oprand2->data;

	            free(oprand2);
	        }
	        p = p->next;
	    }
	    int result = stack.top->data;
	    clean_stack(&stack);
	    return result;
	}


/* Evaluate statement like b = (a+3)*2;
 * @param ht - pointer to a HASHTABLE to resolve the value of symbols on the right side.
 * @return  - symbol on the left side and its value in DATA type.
 */
DATA evaluate_statement(HASHTABLE *ht, char* statement){
	DATA hd = { 0 };
	    char line[80] = { 0 };
	    strcpy(line, statement);
	    char *p = line, *dp = line;
	    while (*p) {
	        if (*p != ' ') {
	            *dp = *p;
	            dp++;
	        }
	        p++;
	    }
	    *dp = '\0';
	    char name[20] = { 0 };
	    char *eqp = strstr(line, "=");
	    if (eqp) {
	        *eqp = '\0';
	        strcpy(name, line);
	        if ((name[0] >= 'a' && name[0] <= 'z')
	                || (name[0] >= 'A' && name[0] <= 'Z')) {
	            int value = evaluate_infix_symbol(ht, eqp + 1);
	            DATA data = {0};
	            strcpy(data.name, name);
	            data.value = value;
	            hashtable_insert(ht, data);
	            strcpy(hd.name, name);
	            hd.value = value;
	        }
	    } else {
	        strcpy(name, line);
	        if ((name[0] >= 'a' && name[0] <= 'z')
	                || (name[0] >= 'A' && name[0] <= 'Z')) {
	            HNODE *hnp = hashtable_search(ht, name);
	            if (hnp) {
	                strcpy(hd.name, name);
	                hd.value = hnp->data.value;
	            }
	        }
	    }
	    return hd;
	}

