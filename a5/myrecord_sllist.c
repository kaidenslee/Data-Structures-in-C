/**
 * -------------------------------------
 * @file  myrecord_sllist.c
 * -------------------------------------
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *//*
 * myrecord_sllist.h
 *
 *  Created on: Feb. 13, 2025
 *      Author: kaidenlee
 */

#include "myrecord_sllist.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

/**
 * Search singly linked list by the key name.
 *
 * @param SLL *sllp - provides the address of a singly linked list structure.
 * @param char *name - key to search
 * @return Pointer to found node if found; otherwise NULL
 */
NODE *sll_search(SLL *sllp, char *name){

	NODE *current = sllp->start;
	while(current != NULL){
		if (strcmp(current->data.name, name) == 0){
			return current;
		}
		current = current->next;


	}
	return NULL;

}

/**
 * Insert a new record to linked list at the position sorted by record name field.
 *
 * @param SLL *sllp - provides the address of a singly linked list structure.
 * @param char *name - name field of the new record.
 * @param float score - the score data of the new record.
 */
void sll_insert(SLL *sllp, char *name, float score){

	NODE *newNode = (NODE *)malloc(sizeof(NODE));
	strcpy(newNode->data.name, name);
	newNode->data.score = score;
	newNode->next = NULL;

	if(sllp->start == NULL || strcmp(name, sllp->start->data.name)<0){
		newNode->next = sllp->start;
		sllp->start = newNode;
	}else{
		NODE *current = sllp->start;
		while(current->next != NULL && strcmp(name, current->next->data.name)> 0){
			current = current->next;
		}

		newNode->next = current->next;
		current->next = newNode;
	}


	sllp->length++;
	}



/**
 * Delete a node of record matched by the name key from linked list.
 *
 * @param SLL *sllp provides the address of a singly linked list structure.
 * @param name - key used to find the node for deletion.
 * @return 1 if deleted a matched node, 0 otherwise.
 */
int sll_delete(SLL *sllp,  char *name){

	if(sllp->start == NULL){
		return 0;
	}

	NODE *current = sllp->start;
	NODE *prev = NULL;


	while(current != NULL && strcmp(current->data.name, name) != 0){
		prev = current;
		current = current->next;

	}

	if(current == NULL){
		return 0;
	}
	if(prev == NULL){
		sllp->start = current->next;
	}else{
		prev->next = current->next;

	}
	free(current);
	sllp->length--;

	return 1;
}

/**
 * Clean singly linked list, delete all nodes.
 * @param @param SLL *sllp provides the address of a singly linked list structure.
 */
void sll_clean(SLL *sllp){

NODE *current = sllp->start;
NODE *temp;

while(current != NULL){
	temp = current->next;
	free(current);
	current = temp;

}

sllp->start = NULL;
sllp->length = 0;
}


