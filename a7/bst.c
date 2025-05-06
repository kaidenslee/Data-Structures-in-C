/**
 * -------------------------------------
 * @file  bst.c
 * -------------------------------------
 * @author Kaiden Lee, 169050073 leex5007@mylaurier.ca
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/

#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* This function creates BSTNODE node with given RECORD data
 * using malloc() and return the new node pointer.
 */
BSTNODE *bst_node(RECORD data){
	BSTNODE *newNode = (BSTNODE *)malloc(sizeof(BSTNODE));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

/* Search the BST by search key matching with data.name
 *
 * @param root - pointer to tree root.
 * @param key - string of search key
 *
 * @return - pointer to matched node if found, otherwise NULL
 */
BSTNODE *bst_search(BSTNODE *root, char *key){
	if (root == NULL) return NULL;

	    int cmp = strcmp(key, root->data.name);

	    if (cmp == 0) {
	        return root;
	    } else if (cmp < 0) {
	        return bst_search(root->left, key);
	    } else {
	        return bst_search(root->right, key);
	    }
	}


/* Insert a node of given record data into BST.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param data  -  record data for the new node.
 *
 */
void bst_insert(BSTNODE **rootp, RECORD data){
	if (*rootp == NULL) {
	        *rootp = bst_node(data);
	        return;
	    }

	    int cmp = strcmp(data.name, (*rootp)->data.name);

	    if (cmp < 0) {
	        bst_insert(&((*rootp)->left), data);
	    } else if (cmp > 0) {
	        bst_insert(&((*rootp)->right), data);
	    }
	}


/* Delete a node of data.name matched with given key.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param key -   key to match with data.name for deletion.
 */
void bst_delete(BSTNODE **rootp, char *key){
	if (*rootp == NULL) return;

	    int cmp = strcmp(key, (*rootp)->data.name);

	    if (cmp < 0) {
	        bst_delete(&((*rootp)->left), key);
	    } else if (cmp > 0) {
	        bst_delete(&((*rootp)->right), key);
	    } else {
	        if ((*rootp)->left == NULL) {
	            BSTNODE *temp = *rootp;
	            *rootp = (*rootp)->right;
	            free(temp);
	        } else if ((*rootp)->right == NULL) {
	            BSTNODE *temp = *rootp;
	            *rootp = (*rootp)->left;
	            free(temp);
	        } else {
	            BSTNODE *smallest = extract_smallest_node(&((*rootp)->right));
	            if (smallest) {
	                (*rootp)->data = smallest->data;
	                free(smallest);
	            }
	    }
	}
}



/* This function cleans the BST passed by pointer of root pointer.
 * @param rootp - pointer to pointer of a tree node.
 */
void bst_clean(BSTNODE **rootp){
	if (*rootp != NULL) {
	        bst_clean(&((*rootp)->left));
	        bst_clean(&((*rootp)->right));
	        free(*rootp);
	        *rootp = NULL;
	    }
	}



/* Get and return and remove the smallest data.name node from the BST.
 *
 * @param rootp - pointer of pointer to BST root.
 * @return - node pointer of the extracted smallest node with NULL childern.
 */
BSTNODE *extract_smallest_node(BSTNODE **rootp){
	if (*rootp == NULL) return NULL;

	    if ((*rootp)->left == NULL) {
	        BSTNODE *smallest = *rootp;
	        *rootp = (*rootp)->right;
	        return smallest;
	    }

	    return extract_smallest_node(&((*rootp)->left));
	}
