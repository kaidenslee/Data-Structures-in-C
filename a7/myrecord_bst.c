/**
 * -------------------------------------
 * @file  myrecord_bst.c
 * -------------------------------------
 * @author Kaiden Lee, 169050073 leex5007@mylaurier.ca
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/

#include "myrecord_bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Add a record data into the BSTDS and update its statistic fields
 * using incremental/online algorithm.
 * @parame ds - pointer to the BSTDS.
 * @parama record - RECORD data to be added.
 */
void add_record(BSTDS *ds, RECORD record){
	if (ds == NULL) return;

	    bst_insert(&(ds->root), record);

	    ds->count++;

	    float old_mean = ds->mean;
	    float old_stddev = ds->stddev;
	    ds->mean = old_mean + (record.score - old_mean) / ds->count;

	    if (ds->count > 1) {
	        float delta = record.score - old_mean;
	        float delta2 = record.score - ds->mean;
	        ds->stddev = sqrt(((old_stddev * old_stddev * (ds->count - 1)) + delta * delta2) / ds->count);
	    } else {
	        ds->stddev = 0;
	    }
	}

/* Delete a node from BSTDA with data.name matching with the given name
 * and stats fields using incremental/online algorithm.
 * @parame ds - pointer to the BSTDS.
 * @parama name - node data.name to be removed.
 */
void remove_record(BSTDS *ds, char *name){
	if (ds == NULL || ds->root == NULL || ds->count == 0) return;

	    BSTNODE *node = bst_search(ds->root, name);
	    if (node == NULL) return;

	    float deleted_value = node->data.score;

	    bst_delete(&(ds->root), name);
	    if (ds->count == 1) {
	        ds->count = 0;
	        ds->mean = 0.0;
	        ds->stddev = 0.0;
	        return;
	    }
	    ds->count--;

	    float old_mean = ds->mean;
	    float old_stddev = ds->stddev;
	    ds->mean = (old_mean * (ds->count + 1) - deleted_value) / ds->count;

	    if (ds->count > 1) {
	        float delta = deleted_value - old_mean;
	        float delta2 = deleted_value - ds->mean;
	        ds->stddev = sqrt(((old_stddev * old_stddev * (ds->count + 1)) - delta * delta2) / ds->count);
	    } else {
	        ds->stddev = 0.0;
	    }
	}

/* Clean the BSTDS and reset count, mean, stddev
 * @parame ds - pointer to the BSTDS.
 */
void bstds_clean(BSTDS *ds){
	if (ds == NULL) return;

	    bst_clean(&(ds->root));
	    ds->count = 0;
	    ds->mean = 0;
	    ds->stddev = 0;
	}
