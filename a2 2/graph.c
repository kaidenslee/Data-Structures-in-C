/**
 * -------------------------------------
 * @file  graph.c
 * -------------------------------------
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/
#include "graph.h"
#include "queue_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* create and return a new adjacent list graph of order n */
GRAPH *new_graph(int n){
	GRAPH *gp = malloc(sizeof(GRAPH));
	  gp->nodes = malloc(n * sizeof(GNODE*));

	  int i;
	  for (i = 0; i < n; i++) {
	    gp->nodes[i] = malloc(sizeof(GNODE));
	    gp->nodes[i]->nid = i;
	    strcpy(gp->nodes[i]->name, "null");
	    gp->nodes[i]->neighbor = NULL;
	  }

	  gp->order = n;
	  gp->size = 0;

	  return gp;
	}

/* Add edge (from, to, weight) to a graph. If edge (from, to) exists, update its weight by the new weight,
 * This indicates that if (from, to) does not exist, the new edge will be added to the end of the linked list.
*/
void insert_edge_graph(GRAPH *g, int from, int to, int weight){
	if(!g || from < 0 || to < 0 || from >= g->order || to >= g->order){
		return;
	}

	ADJNODE *ptr = g->nodes[from]->neighbor;

	while(ptr != NULL){
		if(ptr->nid == to){
			ptr->weight = weight;
			return;
		}
		ptr = ptr->next;
	}

	ADJNODE *new_node = malloc(sizeof(ADJNODE));
	new_node->nid = to;
	new_node->weight = weight;
	new_node->next = NULL;

	ADJNODE *current = g->nodes[from]->neighbor;
	if(current == NULL){
		g->nodes[from]->neighbor = new_node;
	}else{
		while(current->next != NULL){
			current = current->next;
		}
		current->next = new_node;
	}
	g->size++;
}

/* Delete edge (from, to)*/
void delete_edge_graph(GRAPH *g, int from, int to){
	if(!g || from < 0 || to < 0 || from >= g->order || to >= g->order){
			return;
		}
	ADJNODE *current = g->nodes[from]->neighbor;
	ADJNODE *prev = NULL;
	while(current != NULL){
		if(current->nid == to){
		if(prev == NULL){
			g->nodes[from]->neighbor = current->next;
		}else{
			prev->next = current->next;
		}
		free(current);
		g->size--;
		return;

	}
	prev = current;
	current = current->next;

}
}

/* Get and return the weight of edge (from, to) if exists, otherwise return INFINITY*/
int get_edge_weight(GRAPH *g, int from, int to){
	ADJNODE *current = g->nodes[from]->neighbor;

	while(current != NULL){
		if(current->nid == to){
			return current->weight;
		}
		current = current->next;
	}

	return INFINITY;
}

/* Travere graph nodes in breadth-first-order using auxiliary queue */
void traverse_bforder(GRAPH *g, int start){
	if (!g || start < 0 || start >= g->order) {
	        return;
	    }
	int visited[g->order];
	    for (int i = 0; i < g->order; i++) {
	        visited[i] = 0;
	    }

	    QUEUE q = {NULL, NULL};

	    enqueue(&q, g->nodes[start]);
	    visited[start] = 1;

	    while (q.front != NULL) {
	        GNODE *current = (GNODE *)dequeue(&q);
	        printf("(%d %s) ", current->nid, current->name);

	        ADJNODE *neighbor = current->neighbor;
	        while (neighbor != NULL) {
	            int nid = neighbor->nid;
	            if (!visited[nid]) {
	                enqueue(&q, g->nodes[nid]);
	                visited[nid] = 1;
	            }
	            neighbor = neighbor->next;
	        }
	    }

	    clean_queue(&q);
	}

void dfs_recursive(GRAPH *g, int current, int visited[]) {
	visited[current] = 1;
	    printf("(%d %s) ", current, g->nodes[current]->name);

	    int count = 0;
	    ADJNODE *temp = g->nodes[current]->neighbor;
	    while (temp != NULL) {
	        count++;
	        temp = temp->next;
	    }
	    ADJNODE *neighbors[count];
	    temp = g->nodes[current]->neighbor;
	    for (int i = 0; i < count; i++) {
	        neighbors[i] = temp;
	        temp = temp->next;
	    }
	    for (int i = count - 1; i >= 0; i--) {
	        int nid = neighbors[i]->nid;
	        if (!visited[nid]) {
	            dfs_recursive(g, nid, visited);
	        }
	    }
	}

/* Traverse graph in depth-first-order using auxiliary stack */
void traverse_dforder(GRAPH *g, int start){
	if (!g || start < 0 || start >= g->order) {
	        return;
	    }

	    int visited[g->order];
	    for (int i = 0; i < g->order; i++) {
	        visited[i] = 0;
	    }

	    dfs_recursive(g, start, visited);
	}


/* Display the graph*/
void display_graph(GRAPH *g){
	 if (g ) {
	  printf("order %d ", g->order);
	  printf("size %d ", g->size);
	  printf("(from to weight) ");
	  int i;
	  ADJNODE *ptr;
	  for (i = 0; i < g->order; i++) {
	    //printf("\n%d:", g->nodes[i]->nid);
	    ptr = g->nodes[i]->neighbor;
	    while (ptr != NULL) {
	      printf("(%d %d %d) ", i,  ptr->nid, ptr->weight);
	      ptr = ptr->next;
	    }
	  }
	  }
	}


/* Clean the graph by free all dynamically allocated memory*/
void clean_graph(GRAPH **gp){
	int i;
	  GRAPH *g = *gp;
	  ADJNODE *temp, *ptr;
	  for (i = 0; i < g->order; i++) {
	    ptr = g->nodes[i]->neighbor;
	    while (ptr != NULL) {
	      temp = ptr;
	      ptr = ptr->next;
	      free(temp);
	    }
	    free(g->nodes[i]);
	  }
	  free(g->nodes);
	  free(g);
	  *gp = NULL;
	}
