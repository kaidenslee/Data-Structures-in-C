/**
 * -------------------------------------
 * @file  queue.c
 * -------------------------------------
 * @author Kaiden Lee, 169050073 leex5007@mylaurier.ca
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/

#include "queue.h"

/*
 * Enqueue a node into a queue
 * @param *qp - pointer to the queue
 * @param NODE *np - pointer to the node.
*/
void enqueue(QUEUE *qp, NODE *np){
	if(qp->length == 0){
		qp->front = np;
		qp->rear = np;
	}else{
		qp->rear->next = np;

		qp->rear = np;
	}

	np->next = NULL;

	qp->length++;


}

/*
 * Dequeue and return the pointer of the removed node.
 * @param *qp - pointer to the queue
 * @return - the reference of the removed node, and set it's next to NULL
*/
NODE *dequeue(QUEUE *qp){
	if(qp->length == 0){
		return NULL;
	}

	NODE *current = qp->front;

	qp->front = qp->front->next;
	if(qp->front == NULL){
		qp->rear = NULL;
	}

	current->next = NULL;

	qp->length--;
	return current;
}

/*
 * Clean the linked list queue
 * @param *qp - pointer to the queue
*/
void clean_queue(QUEUE *qp){

	NODE *current = qp->front;
	NODE *temp = current;

	while(current != NULL){
		temp = current->next;
		free(current);
		current = temp;
	}

	qp->length = 0;
	qp->rear = NULL;
	qp->front = NULL;
}

