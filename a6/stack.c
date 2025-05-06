/**
 * -------------------------------------
 * @file  stack.c
 * -------------------------------------
 * @author Kaiden Lee, 169050073 leex5007@mylaurier.ca
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/

#include "stack.h"

/*
 * Push a node into a linked list stack
 * @param STACK *sp - pointer to the stack
 * @param NODE *np - pointer to the node.
*/
void push(STACK *sp, NODE *np){
	if(sp->top == NULL){
		np->next = NULL;
	}else{
		np->next = sp->top;
	}
	sp->top = np;
	sp->length++;

}

/*
 * Pop and return the pointer of the removed top node
 * @param STACK *sp - pointer to the stack
 * @return - the reference of the removed node and set it's next to NULL
*/
NODE *pop(STACK *sp){
	if(sp->top == NULL){
		return NULL;
	}
	NODE *hold = sp->top;

	if(sp->top->next == NULL){
		sp->top = NULL;
	}else{
		sp->top = sp->top->next;
	}

	sp->length--;

	return hold;
}

/*
 * clean the linked list stack
 */
void clean_stack(STACK *sp){
	NODE *current = sp->top;
	NODE *temp = current;

	while(current != NULL){
		temp = current->next;
		free(current);
		current = temp;
	}

	sp->length = 0;
	sp->top = NULL;

}
