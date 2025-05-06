/**
 * -------------------------------------
 * @file  set_avl.c
 * -------------------------------------
 * @author Kaiden Lee, 169050073 leex5007@mylaurier.ca
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/

#include "set_avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int count_nodes(AVLNODE *root){
	if(root == NULL){
		return 0;
	}

	return 1 + count_nodes(root->left) + count_nodes(root->right);
}
/**
 * returns the number of elements in the set
 */
int set_size(SET *s){
	if(s == NULL) return 0;
	return count_nodes(s->root);
}
/**
 * Returns 1 it set s contains element e; otherwise 0.
*/
int set_contain(SET *s, char *e){
	if(s == NULL || s->root == NULL) return 0;
	AVLNODE *ans = avl_search(s->root, e);

	if (ans == NULL){
		return 0;
	}

	return 1;
}

/**
 * Add element e into set s.
*/
void set_add(SET *s, char *e){
	RECORD new_record;
	strcpy(new_record.name, e);
	new_record.score = 0.0;
	avl_insert(&(s->root), new_record);
}

/**
 * Remove  element e into set s
 */
void set_remove(SET *s, char *e){
	avl_delete(&(s->root), e);
}

/**
 * Clear the set, clearing the underlying AVL tree, and reset fields of s.
 */
void set_clean(SET *s){
	avl_clean(&(s->root));
	s->root = NULL;
}

