/**
  * Implementation of a Min-Heap
  * Author: Naufal Fikri Setiawan
  * nsetiawan@student.unimelb.edu.au
  */

#include <stdlib.h>
#include <assert.h>
#include "heap.h"
#include <stdio.h>

// Creates a new (empty) heap.
Heap *new_heap(int size) {
  Heap *h = (Heap*)malloc(sizeof(Heap));
  HeapItem *hi = (HeapItem*)malloc(size * sizeof(HeapItem));

  assert(h != NULL);
  assert(hi != NULL);

  h->items = hi;
  h->length = 0;
  h->size = size;
  return h;
}

// Inserts a data of type integer associated to a key value
// the heap will be sorted based on the key value and NOT the data.
void heap_insert(Heap *h, float key, int data) {
  assert(h->length < h->size);

  h->items[h->length].key = key;
  h->items[h->length].data = data;

  // Performing 'sift-up'
  int i = h->length;
  while (i > 0 && h->items[(i-1)/2].key > h->items[i].key) {
    
    HeapItem swap = h->items[(i-1)/2];
    h->items[(i-1)/2] = h->items[i];
    h->items[i] = swap;

    i = (i-1)/2;
  }

  h->length += 1;
}

// Obtain the data with smallest key in the heap and remove it from the
// heap data structure.
int heap_pop_min(Heap *h) {
  assert(h->length > 0);

  int item = h->items[0].data;
  h->length -= 1;
  h->items[0] = h->items[h->length];

  min_heapify(h, 0);
  return item;
}

// Peeks the data with the smallest key in the heap, returning its value
// without removing it from the heap.
int heap_peek_min(Heap *h) {
  return (h->items[0]).data;
}

// Peeks the smallest key element in the heap data structure, returning
// its key without removing the data from the heap.
float heap_peek_key(Heap *h) {
  return (h->items[0]).key;
}

// Frees the memory allocated to the heap and all its element.
void free_heap(Heap *h) {
  free(h->items);
  free(h);
}

// Helper function to fix the heap so it maintains the heap property.
// Modified implementation from "Introduction to Algorithms" by
// Cormen, Leiserson, Rivest, Stein (CLRS).
void min_heapify(Heap *h, int i) {
  int left = 2*i + 1;
  int right = left + 1;
  int min = i;

  if (left < h->length && h->items[left].key < h->items[min].key) {
    min = left;
  }

  if (right < h->length && h->items[right].key < h->items[min].key) {
    min = right;  
  }

  if (min != i) {
    HeapItem swap = h->items[i];
    h->items[i] = h->items[min];
    h->items[min] = swap;

    min_heapify(h, min);
  }
}
