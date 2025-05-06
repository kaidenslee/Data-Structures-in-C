/**
 * -------------------------------------
 * @file  dllist.c
 * -------------------------------------
 * @author Kaiden Lee, 169050073 leex5007@mylaurier.ca
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/

 #include "dllist.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>


/*
 * Create and return a new node using malloc() with passed data value and returns pointer of the node.
*/
NODE *dll_node(char value){
	NODE *newNode = (NODE *)malloc(sizeof(NODE));

	newNode->data = value;
	newNode->prev = NULL;
	newNode->next = NULL;

	return newNode;
}

/*
 * Insert a given node at the beginning the of a doubly linked list.
 * @param DLL *dllp -  reference to input DLL variable
 * @param NODE *np  -  reference of a NODE node to be inserted
*/
void dll_insert_start(DLL *dllp, NODE *np){
	if (dllp == NULL || np == NULL) return;

	np->prev = NULL;
	np->next = dllp->start;

	if(dllp->start == NULL){
		dllp->start = np;
		dllp->end = np;
	}else{
		dllp->start->prev = np;
		dllp->start = np;
	}

	dllp->length++;
}

/*
 * Insert a node at the end of a doubly linked list.
 * @param DLL *dllp -  reference to input DLL variable
 * @param NODE *np  -  reference of a NODE node to be inserted
*/
void dll_insert_end(DLL *dllp, NODE *np){
	if (dllp == NULL || np == NULL) return;

		np->prev = dllp->end;
		np->next = NULL;

		if(dllp->start == NULL){
			dllp->start = np;
			dllp->end = np;
		}else{
			dllp->end->next = np;
			dllp->end = np;
		}

		dllp->length++;
	}


/*
 * This deletes the first node of a doubly linked list.
 * @param DLL *dllp -  reference to input DLL variable
*/
void dll_delete_start(DLL *dllp){
	if(dllp->start == NULL || dllp == NULL) return;
	NODE *temp = dllp->start;

	if(dllp->start->next == NULL){
		dllp->start = NULL;
		dllp->end = NULL;
	}else{
		dllp->start = dllp->start->next;
		dllp->start->prev = NULL;
	}
	free(temp);
	dllp->length--;



}

/*
 * Delete the end node of a doubly linked list.
 * @param DLL *dllp -  reference to input DLL variable
*/
void dll_delete_end(DLL *dllp){
if(dllp->start == NULL || dllp == NULL) return;
NODE *temp = dllp->end;

if(dllp->start->next == NULL){
	dllp->start = NULL;
	dllp->end = NULL;
}else{
	dllp->end = dllp->end->prev;
	dllp->end->next = NULL;
}
free(temp);
dllp->length--;



}


/*
 * Clean and free the nodes of a doubly linked list and reset start and length.
 * @param DLL *dllp -  reference to input DLL variable
*/
void dll_clean(DLL *dllp){
	if (dllp == NULL || dllp->start == NULL) return;

	    NODE *current = dllp->start;
	    NODE *temp;

	    while (current != NULL) {
	        temp = current->next;
	        free(current);
	        current = temp;
	    }

	    dllp->start = NULL;
	    dllp->end = NULL;
	    dllp->length = 0;
	}


