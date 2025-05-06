/**
 * -------------------------------------
 * @file  heap.c
 * -------------------------------------
 * @author Kaiden Lee, 169050073 leex5007@mylaurier.ca
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 *
**/
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int cmp(KEYTYPE a, KEYTYPE b) {
  int r = 0;
  if (a < b) r = -1;
  else if (a > b) r = 1;
  return r;
}

void swap(HEAPDATA *a, HEAPDATA *b) {
    HEAPDATA temp = *a;
    *a = *b;
    *b = temp;
}


int heapify_up(HEAPDATA *hda, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (cmp(hda[index].key, hda[parent].key) < 0) {
            swap(&hda[index], &hda[parent]);
            index = parent;
        } else break;
    }
    return index;
}

int heapify_down(HEAPDATA *hda, int n, int index) {
    int left, right, smallest;
    while (1) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        smallest = index;

        if (left < n && cmp(hda[left].key, hda[smallest].key) < 0) {
            smallest = left;
        }
        if (right < n && cmp(hda[right].key, hda[smallest].key) < 0) {
            smallest = right;
        }
        if (smallest != index) {
            swap(&hda[index], &hda[smallest]);
            index = smallest;
        } else break;
    }
    return index;
}



/* Use malloc to create HEAP type object, set its size 0, capacity 4,
 * then create an array of HEAPDATA elements of length equal to the capacity
 * and let hda point to the array. Return the pointer of the HEAP object.
 * @param capacity - the capacity of the binary heap, i.e. the length of the heap array.
 * @return - pointer to the HEAP object.
*/
HEAP *new_heap(int capacity){
	  HEAP *hp = (HEAP*) malloc(sizeof(HEAP));
	  if (hp == NULL) return NULL;
	  hp->hda = (HEAPDATA *) malloc(sizeof(HEAPDATA) * capacity);
	  if ( hp->hda == NULL) { free(hp); return NULL; };
	  hp->capacity = capacity;
	  hp->size = 0;
	  return hp;
	}


/* Insert the given HEAPDADA data into a heap. When the heap size is equal to the capacity,
 * expand data array by doubling its length and copy the data of old array to the new array in case of need,
 * then insert the data into the heap array.
 * @param heap - pointer to the heap.
 * @param data - data to be inserted.
 */
void heap_insert(HEAP *heap, HEAPDATA data){
	if (heap->size >= heap->capacity) {
	        heap->capacity *= 2;
	        heap->hda = realloc(heap->hda, heap->capacity * sizeof(HEAPDATA));
	    }
	    heap->hda[heap->size] = data;
	    heapify_up(heap->hda, heap->size);
	    heap->size++;
	}

/* Get the HEAPDADA data of minimum key.
 * @param heap - pointer to the heap.
 * @return - the minimum key HEAPDATA
 */
HEAPDATA heap_find_min(HEAP *heap){
	return heap->hda[0];
	}

/* Get the minimum key HEAPDADA data and delete it from the heap.
 * When the heap->size <= (heap->capacity)/4 and heap->capacity>4, shrink the HEAPDATA array by half.
 * @param heap - pointer to the heap.
 * @return - the minimum key HEAPDATA
 */
HEAPDATA heap_extract_min(HEAP *heap){
	HEAPDATA min = heap->hda[0];
	    heap->hda[0] = heap->hda[heap->size - 1];
	    heap->size--;
	    heapify_down(heap->hda, heap->size, 0);

	    if (heap->size <= heap->capacity / 4 && heap->capacity > 4) {
	        heap->capacity /= 2;
	        heap->hda = realloc(heap->hda, heap->capacity * sizeof(HEAPDATA));
	    }
	    return min;
	}


/* Changes heap->hda[index].key to new_key, heapify, return the index of new position of the new_key element.
 * @param heap - pointer to the heap.
 * @param index - index of HEAPDATA for key changing.
 * @param new_kay - key value to to be changed.
 * @return - position index of the new_key element.
 */
int heap_change_key(HEAP *heap, int index, KEYTYPE new_key){
	KEYTYPE old_key = heap->hda[index].key;
	    heap->hda[index].key = new_key;
	    if (cmp(new_key, old_key) < 0) {
	        return heapify_up(heap->hda, index);
	    } else {
	        return heapify_down(heap->hda, heap->size, index);
	    }
	}



/* Find and return the index of the first HEAPDATA data such that data.value == val.
 * @param heap - pointer to the heap.
 * @param val -  match value for search.
 * @return - position index of HEAPDATA data if found, otherwise -1.
 */
int heap_search_value(HEAP *heap, VALUETYPE val){
	for (int i = 0; i < heap->size; i++) {
	        if (heap->hda[i].value == val) {
	            return i;
	        }
	    }
	    return -1;
	}


/* Free dynamically allocated memory of the given heap, and set its pointer to NULL.
 * @param heapp - pointer of pointer to the heap.
 */
void heap_clean(HEAP **heapp){
	if (heapp) {
	    HEAP *heap = *heapp;
	    if (heap->capacity > 0) {
	      heap->capacity = 0;
	      heap->size = 0;
	      free(heap->hda);
	      free(heap);
	    }
	    *heapp = NULL;
	  }
}


/* Sort HEAPDATA array in place in decreasig order of HEAPDATA key.
 * @param *arr - array pointer of HEAPDATA array
 * @param n - length of the input array.
 */
void heap_sort(HEAPDATA *arr, int n){
	HEAP *heap = new_heap(n);
	    for (int i = 0; i < n; i++) {
	        heap_insert(heap, arr[i]);
	    }
	    for (int i = n - 1; i >= 0; i--) {
	        arr[i] = heap_extract_min(heap);
	    }
	    heap_clean(&heap);
	}
