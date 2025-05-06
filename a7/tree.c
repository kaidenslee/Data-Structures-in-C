/**
 * -------------------------------------
 * @file  tree.c
 * -------------------------------------
 * @author Kaiden Lee, 169050073 leex5007@mylaurier.ca
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>



/* Compute and return the TPROPS value of a tree.
 * @param root - pointer to the root of a tree
 * @return - number of nodes and height in TPROPS type.
 */
TPROPS tree_property(TNODE *root){
	TPROPS props = {0, 0};

	if(root != NULL){
		TPROPS left_props = tree_property(root->left);
		TPROPS right_props = tree_property(root->right);

		props.order = 1 + left_props.order + right_props.order;
		props.height = 1 + (left_props.height > right_props.height ? left_props.height : right_props.height);

	}

	return props;
}

/* Display the node data of the tree in pre-order and format "%c ".
 *
 *  @param root - pointer to the root of a tree
 */
void preorder(TNODE *root){
	if(root != NULL){
		printf("%c ", root->data);
		preorder(root->left);
		preorder(root->right);

	}
}

/* Display the node data of the tree in in-order and format "%c".
 *
 *  @param root - pointer to the root of a tree
 */
void inorder(TNODE *root){
	if(root != NULL){
		inorder(root->left);
		printf("%c ", root->data);
		inorder(root->right);

	}
}

/* Display the node data of the tree in post-order and format "%c ".
 *
 *  @param root - pointer to the root of a tree
 */
void postorder(TNODE *root){
	if(root != NULL){
		postorder(root->left);
		postorder(root->right);
		printf("%c ", root->data);
	}
}

/* Display the node data of the tree in breadth-first-order and format "%c ".
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 */
void bforder(TNODE *root){
	if(root == NULL) return;

	QUEUE q = {NULL, NULL};
	enqueue(&q, root);

	while(q.front != NULL){
		TNODE *current = (TNODE *) dequeue(&q);
		printf("%c ", current->data);

		if(current->left != NULL){
			enqueue(&q, current->left);
		}
		if(current->right != NULL){
			enqueue(&q, current->right);
		}
	}
}

/* Search by key using breadth-first-search algorithm
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 *  @param key -  search key
 *
 *  @return  - the found node pointer if fount, otherwise NULL
 */
TNODE *bfs(TNODE *root, char key){

	if (root == NULL) return NULL;

	    QUEUE q = {NULL, NULL};
	    enqueue(&q, root);

	    while (q.front != NULL) {
	        TNODE *current = (TNODE *) dequeue(&q);

	        if (current->data == key) {
	            return current;
	        }

	        if (current->left != NULL) {
	            enqueue(&q, current->left);
	        }
	        if (current->right != NULL) {
	            enqueue(&q, current->right);
	        }
	    }

	    return NULL;
	}



/* Search by key using depth-first-search algorithm.
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 *  @param key -  search key
 *
 *  @return  - the found node pointer if fount, otherwise NULL
 */
TNODE *dfs(TNODE *root, char key){
	if (root == NULL) return NULL;

	    STACK s = {NULL};
	    push(&s, root);

	    while (s.top != NULL) {
	        TNODE *current = (TNODE *) pop(&s);

	        if (current->data == key) {
	            return current;
	        }

	        if (current->right != NULL) push(&s, current->right);
	        if (current->left != NULL) push(&s, current->left);
	    }

	    return NULL;
	}



// The following functions are given in a7 help.

/* Create a TNODE node and sets the data to value and returns the pointer.
 * Use malloc()
 */
TNODE *tree_node(char val){
	TNODE *newNode = (TNODE *)malloc(sizeof(TNODE));
	newNode->data = val;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

/* This function cleans a tree.
 * @param rootp - pointer of pointer to the tree root
 */
void clean_tree(TNODE **rootp){
	if (*rootp != NULL) {
	        clean_tree(&((*rootp)->left));
	        clean_tree(&((*rootp)->right));
	        free(*rootp);
	        *rootp = NULL;
	    }
	}


/* This function creates a new node of given value and inserts it into a tree
 * at the first available position in order of breadth-first and left to right.
 *
 * @param rootp - pointer of pointer to the tree node.
 * @param val - data for the new node.
 */
void insert_tree(TNODE **rootp, char val){
	TNODE *newNode = tree_node(val);
	    if (*rootp == NULL) {
	        *rootp = newNode;
	        return;
	    }

	    QUEUE q = {NULL, NULL};
	    enqueue(&q, *rootp);

	    while (q.front != NULL) {
	        TNODE *current = (TNODE *)dequeue(&q);

	        if (current->left == NULL) {
	            current->left = newNode;
	            break;
	        } else {
	            enqueue(&q, current->left);
	        }


	        if (current->right == NULL) {
	            current->right = newNode;
	            break;
	        } else {
	            enqueue(&q, current->right);
	        }
	    }
	}
