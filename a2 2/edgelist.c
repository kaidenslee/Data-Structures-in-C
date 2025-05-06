/**
 * -------------------------------------
 * @file  edgelist.c
 * -------------------------------------
 * @author Kaiden Lee, 169050073 leex5007@mylaurier.ca
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/
#include "edgelist.h"
#include <stdio.h>
#include <stdlib.h>


/* Create and return a new edge list graph*/
EDGELIST *new_edgelist(){
	EDGELIST *tp = malloc(sizeof(EDGELIST));
	    tp->size = 0;
	    tp->start = NULL;
	    tp->end = NULL;
	    return tp;
	}


/* Add a new edge at the start of the linked list of edges*/
void insert_edge_start(EDGELIST *g, int from, int to, int weight){
	EDGENODE *new_edge = (EDGENODE *)malloc(sizeof(EDGENODE));
	new_edge->from = from;
	new_edge->to = to;
	new_edge->weight = weight;

	new_edge->next = g->start;
	g->start = new_edge;

	if(g->end == NULL){
		g->end = new_edge;
	}
	g->size++;
}

/* Add an new edge at the end of the linked list of edges */
void insert_edge_end(EDGELIST *g, int from, int to, int weight){
	EDGENODE *new_edge = (EDGENODE *)malloc(sizeof(EDGENODE));
		new_edge->from = from;
		new_edge->to = to;
		new_edge->weight = weight;
		new_edge->next = NULL;

		if(g->start == NULL){
			g->start = new_edge;
			g->end = new_edge;
		}else{
			g->end->next = new_edge;
			g->end = new_edge;
		}

		g->size++;

}

/* Delete edge (from to) from the edgelist */
void delete_edge(EDGELIST *g, int from, int to){
	EDGENODE *current = g->start;
	    EDGENODE *prev = NULL;

	    while (current != NULL) {
	        if (current->from == from && current->to == to) {
	            if (prev == NULL) {
	                g->start = current->next;
	            } else {
	                prev->next = current->next;
	            }

	            if (current == g->end) {
	                g->end = prev;
	            }

	            free(current);
	            g->size--;
	            return;
	        }

	        prev = current;
	        current = current->next;
	    }
	}
/* Get the weight of the graph */
int weight_edgelist(EDGELIST *g){
	int total = 0;
	    EDGENODE *current = g->start;

	    while (current != NULL) {
	        total += current->weight;
	        current = current->next;
	    }

	    return total;
	}


/* clean the graph by free all dynamically allocated memory*/
void clean_edgelist(EDGELIST **gp){
	EDGELIST *g = *gp;
	    EDGENODE *temp, *p = g->start;
	    while (p) {
	        temp = p;
	        p = p->next;
	        free(temp);
	    }
	    free(g);
	    *gp = NULL;
	}


/* Display edge list graph*/
void display_edgelist(EDGELIST *g){
	if (g == NULL)
	        return;
	    printf("size %d ", g->size);
	    printf("(from to weight) ");
	    EDGENODE *p = g->start;
	    while (p) {
	        printf("(%d %d %d) ", p->from, p->to, p->weight);
	        p = p->next;
	    }
	}
