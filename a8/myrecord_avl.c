/**
 * -------------------------------------
 * @file  myrecord_avl.c
 * -------------------------------------
 * @author Kaiden Lee, 169050073 leex5007@mylaurier.ca
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/

#include "myrecord_avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/*  Merge source AVL tree into destination AVL tree. No change to source tree.
 *  @parame rootp_dest   - pointer to pointer of root of destination tree
 *  @parame rootp_source - pointer to pointer of root of source tree
 */
void avl_merge(AVLNODE **rootp_dest, AVLNODE **rootp_source){
	if (*rootp_source == NULL) {
	        return;
	    }

	    avl_insert(rootp_dest, (*rootp_source)->data);
	    avl_merge(rootp_dest, &((*rootp_source)->left));
	    avl_merge(rootp_dest, &((*rootp_source)->right));
	}


/*  Merge source AVLDS to destination AVLDS, use aggregation algorithm to
 *  compute the stats info, can clean source AVLDS.
 *  @parame source - pointer to the source AVLDS
 *  @parame dest - pointer to the destination AVLDS
 */
void avlds_merge(AVLDS *dest, AVLDS *source){
	if (source == NULL || source->root == NULL) {
	        return;
	    }

	    avl_merge(&(dest->root), &(source->root));

	    int new_count = dest->count + source->count;
	    if (new_count == 0) return;

	    float new_mean = (dest->mean * dest->count + source->mean * source->count) / new_count;
	    float new_stddev = sqrt(
	        ((dest->stddev * dest->stddev + dest->mean * dest->mean) * dest->count +
	         (source->stddev * source->stddev + source->mean * source->mean) * source->count) / new_count
	        - new_mean * new_mean
	    );

	    dest->count = new_count;
	    dest->mean = new_mean;
	    dest->stddev = new_stddev;

	    avlds_clean(source);
	}


/*  Clean its AVL tree and set count=0, mean=0, stddev=0
 *  @parame ds - pointer to the AVLDS
 */
void avlds_clean(AVLDS *ds){
	avl_clean(&ds->root);
	    ds->count = 0;
	    ds->mean = 0;
	    ds->stddev = 0;
	}


void add_record(AVLDS *ds, RECORD data){
	if (avl_search(ds->root, data.name) == NULL) {
	        avl_insert(&(ds->root), data);

	        int count = ds->count;
	        float mean = ds->mean;
	        float stddev = ds->stddev;

	        ds->count = count + 1;
	        ds->mean = (mean * count + data.score) / (count + 1.0);

	        if (count > 0) {
	            ds->stddev = sqrt(
	                (data.score * data.score / (count + 1.0)) +
	                ((stddev * stddev + mean * mean) * (count / (count + 1.0))) -
	                (ds->mean * ds->mean)
	            );
	        } else {
	            ds->stddev = 0;
	        }
	    } else {
	        printf("Record exists\n");
	    }
	}

void remove_record(AVLDS *ds, char *name){
	AVLNODE *np = avl_search(ds->root, name);

	    if (np != NULL) {
	        float score = np->data.score;
	        avl_delete(&(ds->root), name);

	        int count = ds->count;
	        float mean = ds->mean;
	        float stddev = ds->stddev;

	        ds->count = count - 1;

	        if (count >= 3) {
	            ds->mean = (mean * count - score) / (count - 1.0);
	            ds->stddev = sqrt(
	                ((stddev * stddev + mean * mean) * (count / (count - 1.0))) -
	                (score * score / (count - 1.0)) - (ds->mean * ds->mean)
	            );
	        } else if (count == 2) {
	            ds->mean = (mean * count - score);
	            ds->stddev = 0;
	        } else {
	            ds->mean = 0;
	            ds->stddev = 0;
	        }
	    } else {
	        printf("Record does not exist\n");
	    }
	}

