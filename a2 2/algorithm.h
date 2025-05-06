/**
 * -------------------------------------
 * @file  algorithm.h
 * -------------------------------------
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/


#ifndef SRC_ALGORITHM_H_
#define SRC_ALGORITHM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edgelist.h"
#include "graph.h"
#define INFINITY 999999

/* Compute and return MST by Prim's algorithm using priority queue (min-heap)
 * @param g     - graph by reference
 * @param start - the root node of MST
 * @return      - pointer of edge list of shortest path tree
*/
EDGELIST *mst_prim(GRAPH *g, int start);

/*
 * Compute shortest path tree as edge list by Dijkstra's algorithm using priority queue (min-heap)
 * @param g     - graph by reference
 * @param start - the root node of shortest path tree
 * @return      - pointer of edge list of shortest path tree
*/
EDGELIST *spt_dijkstra(GRAPH *g, int start);

/*
 * Compute shortest path as edge list by Dijkstra's algorithm using priority queue (min-heap)
 * @param g     - graph by reference
 * @param start - the start node of shortest path
 * @param end   - the end node of shortest path
 * @return      - pointer of edge list of shortest path
*/
EDGELIST *sp_dijkstra(GRAPH *g, int start, int end);

#endif /* SRC_ALGORITHM_H_ */
