/**
 * -------------------------------------
 * @file  avl.c
 * -------------------------------------
 * @author Kaiden Lee, 169050073 leex5007@mylaurier.ca
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/

#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b) ((a) >(b) ? (a) : (b))

/* Insert a node of given record data into AVL tree.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param data  - record data for the new node.
 */
void avl_insert(AVLNODE **rootp, RECORD data){
	if(*rootp == NULL){
		*rootp = (AVLNODE*)malloc(sizeof(AVLNODE));
		        (*rootp)->data = data;
		        (*rootp)->left = NULL;
		        (*rootp)->right = NULL;
		        (*rootp)->height = 1;
		        return;
		    }

	if (strcmp(data.name, (*rootp)->data.name) < 0) {
	        avl_insert(&((*rootp)->left), data);
	    } else if (strcmp(data.name, (*rootp)->data.name) > 0) {
	        avl_insert(&((*rootp)->right), data);
	    } else {
	        return;
	    }

	(*rootp)->height = 1 + max(height((*rootp)->left), height((*rootp)->right));

	int balance = balance_factor(*rootp);

	if (balance > 1 && strcmp(data.name, (*rootp)->left->data.name) < 0) {
	        *rootp = rotate_right(*rootp);
	    } else if (balance < -1 && strcmp(data.name, (*rootp)->right->data.name) > 0) {
	        *rootp = rotate_left(*rootp);
	    } else if (balance > 1 && strcmp(data.name, (*rootp)->left->data.name) > 0) {
	        (*rootp)->left = rotate_left((*rootp)->left);
	        *rootp = rotate_right(*rootp);
	    } else if (balance < -1 && strcmp(data.name, (*rootp)->right->data.name) < 0) {
	        (*rootp)->right = rotate_right((*rootp)->right);
	        *rootp = rotate_left(*rootp);
	    }
	}



/* Delete a node of data.name matched with given key from AVL tree.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param key -   key to match with data.name for deletion.
 */
void avl_delete(AVLNODE **rootp, char *key){
	if (*rootp == NULL) return;

	    if (strcmp(key, (*rootp)->data.name) < 0) {
	        avl_delete(&((*rootp)->left), key);
	    } else if (strcmp(key, (*rootp)->data.name) > 0) {
	        avl_delete(&((*rootp)->right), key);
	    } else {
	        if ((*rootp)->left == NULL || (*rootp)->right == NULL) {
	            AVLNODE *temp = (*rootp)->left ? (*rootp)->left : (*rootp)->right;

	            if (temp == NULL) {
	                temp = *rootp;
	                *rootp = NULL;
	            } else {
	                **rootp = *temp;
	            }
	            free(temp);
	        } else {
	            AVLNODE *succ = (*rootp)->right;
	            while (succ->left != NULL) {
	                succ = succ->left;
	            }

	            (*rootp)->data = succ->data;

	            avl_delete(&((*rootp)->right), succ->data.name);
	        }
	    }

	    if (*rootp == NULL) return;


		(*rootp)->height = 1 + max(height((*rootp)->left), height((*rootp)->right));

		int balance = balance_factor(*rootp);

		if (balance > 1 && balance_factor((*rootp)->left) >= 0) {
		        *rootp = rotate_right(*rootp);
		    } else if (balance > 1 && balance_factor((*rootp)->left) < 0) {
		        (*rootp)->left = rotate_left((*rootp)->left);
		        *rootp = rotate_right(*rootp);
		    } else if (balance < -1 && balance_factor((*rootp)->right) <= 0) {
		        *rootp = rotate_left(*rootp);
		    } else if (balance < -1 && balance_factor((*rootp)->right) > 0) {
		        (*rootp)->right = rotate_right((*rootp)->right);
		        *rootp = rotate_left(*rootp);
		    }
		}



/* Search AVL tree by key of the name field
 * @param root - pointer to tree root.
 * @param key - key to match with data.name for search
 * @return - node pointer if found, otherwise NULL
 */
AVLNODE *avl_search(AVLNODE *root, char *key){
	if(root == NULL){
		return NULL;
	}

	int cmp = strcmp(root->data.name, key);

	if(cmp == 0){
		return root;
	}

	else if(cmp > 0){
		return avl_search(root->left, key);
	}
	else if(cmp < 0){
		return avl_search(root->right, key);
	}
}

/* This function clean AVL tree.
 * @param rootp - pointer of pointer of tree root.
 */
void avl_clean(AVLNODE **rootp){

	if(*rootp == NULL){
		return;
	}

	avl_clean(&((*rootp)->left));
	avl_clean(&((*rootp)->right));
	free(*rootp);
	*rootp = NULL;
}

/* Get the height of AVL tree
 * @param np - pointer to the root of tree
 * @return - the the height value at root.
 */
int height(AVLNODE *root){
	if(root == NULL){
		return 0;
	}
	int h = 1 + max(height(root->left), height(root->right));

	return h;
}

/* Return the balance factor at the given node
 * @param np - pointer to the node of tree
 * @return - the balance factor a the node
 */
int balance_factor(AVLNODE *np){
	if(np == NULL){
		return 0;
	}

	int left_height = (np->left) ? height(np->left) : 0;
	int right_height = (np->right) ? height(np->right) : 0;

	    return left_height - right_height;
	}

/* This function does the left rotation at a given node
 * @param np - pointer to the rotation node.
 * @return - the pointer to the replaced node.
 */
AVLNODE *rotate_left(AVLNODE *np){

	if(np == NULL || np->right == NULL){
		return NULL;
	}
		AVLNODE *new_root = np->right;
		np->right = new_root->left;
		new_root->left = np;

		np->height = 1 + max(height(np->left), height(np->right));
		new_root->height = 1 + max(height(new_root->left), height(new_root->right));

		return new_root;

	}


/* This function does the right rotation at a given node
 * @param np - pointer to the rotation node.
 * @return - the pointer to the replaced node.
 */
AVLNODE *rotate_right(AVLNODE *root){
	if(root == NULL || root->left == NULL){
			return NULL;
		}
			AVLNODE *new_root = root->left;
			root->left = new_root->right;
			new_root->right = root;

			root->height = 1 + max(height(root->left), height(root->right));
			new_root->height = 1 + max(height(new_root->left), height(new_root->right));

			return new_root;

		}
