/**
 * -------------------------------------
 * @file  algorithm.c
 * ------------------------------------- 
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/
#include "algorithm.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

void reverse_edgelist(EDGELIST *list) {
	if (!list || !list->start) return;

	    EDGENODE *prev = NULL;
	    EDGENODE *current = list->start;
	    EDGENODE *next = NULL;

	    list->end = list->start;

	    while (current != NULL) {
	        next = current->next;
	        current->next = prev;
	        prev = current;
	        current = next;
	    }

	    list->start = prev;
	}
/* Compute and return MST by Prim's algorithm using priority queue (min-heap)
 * @param g     - graph by reference
 * @param start - the root node of MST
 * @return      - pointer of edge list of shortest path tree
*/
EDGELIST *mst_prim(GRAPH *g, int start){
	if (!g || start < 0 || start >= g->order) return NULL;

	    int n = g->order;
	    int in_mst[n], cost[n], parent[n];
	    for (int i = 0; i < n; i++) {
	        in_mst[i] = 0;
	        cost[i] = INFINITY;
	        parent[i] = -1;
	    }
	    cost[start] = 0;

	    HEAP *heap = new_heap(n);
	    for (int i = 0; i < n; i++) {
	        HEAPDATA hd = {cost[i], i};
	        heap_insert(heap, hd);
	    }

	    EDGELIST *mst = new_edgelist();

	    while (heap->size > 0) {
	        HEAPDATA min = heap_extract_min(heap);
	        int u = min.value;
	        in_mst[u] = 1;

	        if (parent[u] != -1) {
	            int w = get_edge_weight(g, parent[u], u);
	            insert_edge_end(mst, parent[u], u, w);
	        }

	        ADJNODE *neighbor = g->nodes[u]->neighbor;
	        while (neighbor) {
	            int v = neighbor->nid;
	            int w = neighbor->weight;
	            if (!in_mst[v] && w < cost[v]) {
	                cost[v] = w;
	                parent[v] = u;
	                int idx = heap_search_value(heap, v);
	                if (idx != -1) heap_change_key(heap, idx, w);
	            }
	            neighbor = neighbor->next;
	        }
	    }

	    heap_clean(&heap);
	    return mst;
	}


/*
 * Compute shortest path tree as edge list by Dijkstra's algorithm using priority queue (min-heap)
 * @param g     - graph by reference
 * @param start - the root node of shortest path tree
 * @return      - pointer of edge list of shortest path tree
*/
EDGELIST *spt_dijkstra(GRAPH *g, int start){
	if (!g || start < 0 || start >= g->order) return NULL;

	    int n = g->order;
	    int visited[n], dist[n], parent[n];
	    for (int i = 0; i < n; i++) {
	        visited[i] = 0;
	        dist[i] = INFINITY;
	        parent[i] = -1;
	    }
	    dist[start] = 0;

	    HEAP *heap = new_heap(n);
	    for (int i = 0; i < n; i++) {
	        HEAPDATA hd = {dist[i], i};
	        heap_insert(heap, hd);
	    }

	    EDGELIST *tree = new_edgelist();

	    while (heap->size > 0) {
	        HEAPDATA min = heap_extract_min(heap);
	        int u = min.value;
	        visited[u] = 1;

	        if (parent[u] != -1) {
	            int w = get_edge_weight(g, parent[u], u);
	            insert_edge_end(tree, parent[u], u, w);
	        }

	        ADJNODE *neighbor = g->nodes[u]->neighbor;
	        while (neighbor) {
	            int v = neighbor->nid;
	            int w = neighbor->weight;
	            if (!visited[v] && dist[u] + w < dist[v]) {
	                dist[v] = dist[u] + w;
	                parent[v] = u;
	                int idx = heap_search_value(heap, v);
	                if (idx != -1) heap_change_key(heap, idx, dist[v]);
	            }
	            neighbor = neighbor->next;
	        }
	    }

	    heap_clean(&heap);
	    return tree;
	}

/*
 * Compute shortest path as edge list by Dijkstra's algorithm using priority queue (min-heap)
 * @param g     - graph by reference
 * @param start - the start node of shortest path
 * @param end   - the end node of shortest path
 * @return      - pointer of edge list of shortest path
*/
EDGELIST *sp_dijkstra(GRAPH *g, int start, int end){
	if (!g || start < 0 || end < 0 || start >= g->order || end >= g->order)
	        return NULL;

	    int n = g->order;
	    int visited[n], dist[n], parent[n];
	    for (int i = 0; i < n; i++) {
	        visited[i] = 0;
	        dist[i] = INFINITY;
	        parent[i] = -1;
	    }
	    dist[start] = 0;

	    HEAP *heap = new_heap(n);
	    for (int i = 0; i < n; i++) {
	        HEAPDATA hd = {dist[i], i};
	        heap_insert(heap, hd);
	    }

	    while (heap->size > 0) {
	        HEAPDATA min = heap_extract_min(heap);
	        int u = min.value;
	        visited[u] = 1;
	        if (u == end) break;

	        ADJNODE *neighbor = g->nodes[u]->neighbor;
	        while (neighbor) {
	            int v = neighbor->nid;
	            int w = neighbor->weight;
	            if (!visited[v] && dist[u] + w < dist[v]) {
	                dist[v] = dist[u] + w;
	                parent[v] = u;
	                int idx = heap_search_value(heap, v);
	                if (idx != -1) heap_change_key(heap, idx, dist[v]);
	            }
	            neighbor = neighbor->next;
	        }
	    }

	    EDGELIST *path = new_edgelist();
	    if (dist[end] == INFINITY) return path;

	    int curr = end;
	    while (parent[curr] != -1) {
	        int from = parent[curr];
	        int weight = get_edge_weight(g, from, curr);
	        insert_edge_end(path, from, curr, weight);
	        curr = from;
	    }

	    reverse_edgelist(path);
	    heap_clean(&heap);
	    return path;
	}

