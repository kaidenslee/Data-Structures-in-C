/**
 * -------------------------------------
 * @file  hash.c
 * -------------------------------------
 * @author Kaiden Lee, 169050073 leex5007@mylaurier.ca
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Hash function that hash key string to an integer of modular of hash table size
 * @param key - input key string
 * @param size - modular value
 * @return  - (sum of ASCII code value the key string modular) % size
 */
int hash(char *key, int size){
	unsigned int sum = 0;
	    while (*key) {
	        sum += *key;
	        key++;
	    }
	    return sum % size;
	}


/* Create dynamically a chained hash table of the given size
 * @param size  --  hash table size, i.e., the length of index array.
 * @return - pointer to dynamically allocated HASHTABLE object.
 */
HASHTABLE *new_hashtable(int size){
	HASHTABLE *ht = (HASHTABLE *)malloc(sizeof(HASHTABLE));
	    if (!ht) return NULL;

	    ht->size = size;
	    ht->count = 0;
	    ht->hna = (HNODE **)calloc(size, sizeof(HNODE *));
	    if (!ht->hna) {
	        free(ht);
	        return NULL;
	    }
	    return ht;
	}


/* Insert key value data into HASHTABLE.
 * @param ht - pointer to a HASHTABLE
 * @param data - data to insert
 * #return - when keyed data exists, update its value and return 0;
 *           otherwise insert into the hash table and return 1
 */
int hashtable_insert(HASHTABLE *ht, DATA data){
	if (!ht) return 0;

	    int index = hash(data.name, ht->size);
	    HNODE *current = ht->hna[index];
	    HNODE *prev = NULL;

	    while (current) {
	        if (strcmp(current->data.name, data.name) == 0) {
	            current->data.value = data.value;
	            return 0;
	        }
	        prev = current;
	        current = current->next;
	    }

	    HNODE *new_node = (HNODE *)malloc(sizeof(HNODE));
	    if (!new_node) return 0;

	    new_node->data = data;
	    new_node->next = ht->hna[index];
	    ht->hna[index] = new_node;
	    ht->count++;
	    return 1;
	}

/* Search the hash table and return the pointer of found hnode
 * @param ht - pointer to a HASHTABLE
 * @param name - key to search
 * @return - pointer to the found HNODE, otherwise NULL
 */
HNODE *hashtable_search(HASHTABLE *ht, char *name){
	if (!ht) return NULL;

	    int index = hash(name, ht->size);
	    HNODE *current = ht->hna[index];

	    while (current) {
	        if (strcmp(current->data.name, name) == 0) {
	            return current;
	        }
	        current = current->next;
	    }
	    return NULL;
	}


/* Delete hashnode by key.
 * @param ht - pointer to a HASHTABLE
 * @param name - name key for deletion
 * @return - if the named data exists, delete it and return 1; otherwise return 0.
 */
int hashtable_delete(HASHTABLE *ht, char *key){
	if (!ht) return 0;

	    int index = hash(key, ht->size);
	    HNODE *current = ht->hna[index];
	    HNODE *prev = NULL;

	    while (current) {
	        if (strcmp(current->data.name, key) == 0) {
	            if (prev) {
	                prev->next = current->next;
	            } else {
	                ht->hna[index] = current->next;
	            }
	            free(current);
	            ht->count--;
	            return 1;
	        }
	        prev = current;
	        current = current->next;
	    }
	    return 0;
	}

/* Clean all linked lists and reset the count to 0
 * @param ht - pointer to a HASHTABLE
 */
void hashtable_clean(HASHTABLE **ht){
	if (!ht || !*ht) return;

	    for (int i = 0; i < (*ht)->size; i++) {
	        HNODE *current = (*ht)->hna[i];
	        while (current) {
	            HNODE *temp = current;
	            current = current->next;
	            free(temp);
	        }
	        (*ht)->hna[i] = NULL;
	    }
	    free((*ht)->hna);
	    free(*ht);
	    *ht = NULL;
	}

