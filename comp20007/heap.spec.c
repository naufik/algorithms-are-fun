/**
  * TEST CASES FOR HEAP.C
  * This file will not be compiled with `make`, that is intentional.
  * Naufal Fikri Setiawan <nsetiawan@student.unimelb.edu.au>
  */

#include "heap.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int minimum(int a, int b);
int is_valid_heap(Heap *h);
void test_create();
void test_insert();
void test_delete();
void test_min_insert();

void dump_heap(Heap *h) {
  for (int i = 0; i < h->length; ++i) {
    printf("%d, %.12f\n", i, h->items[i].key);
  }
}

void custom_test() {
  Heap *h = new_heap(20);
  heap_insert(h, 10.11, 200);
  heap_insert(h, 0.352, 200);
  heap_pop_min(h);
  dump_heap(h);
  assert(heap_peek_key(h) > 10);
  heap_insert(h, 2, 2000);
  assert(heap_peek_key(h) < 3);
}

int minimum(int a, int b) {
  return a <= b ? a : b;
}

/*
 * Check if a heap holds the valid heap data structure
 */
int is_valid_heap(Heap *h) {
  for (int i = 0; i < h->length; ++i) {
    int left = 2*i + 1;
    int right = left + 1;
    
    if (left < h->length && h->items[i].key > h->items[left].key) {
      dump_heap(h);
      return 0;
    }

    if (right < h->length && h->items[i].key > h->items[right].key) {
      dump_heap(h);
      return 0;
    }
  }

  return 1;
}

void top_k_test() {
  Heap *top = new_heap(16);
  float items[400];
  srand(2552);
  for (float i = 1; i <= 400; ++i) {
    items[(int)i-1] = (i)/2.0;
  }

  for (int i = 0; i < 16; ++i) {
    heap_insert(top, items[i], i);
  }

  for (int i = 16; i < 400; ++i) {
    if (items[i] > heap_peek_key(top)) {
      heap_pop_min(top);
      heap_insert(top, items[i], i);
    }
  }
  dump_heap(top);
}

void heap_sbox_test() {
  Heap *h = new_heap(20);
  heap_insert(h, 0, 10);
  heap_insert(h, 20, 10);
  heap_pop_min(h);
  dump_heap(h);
}

int main(int argc, char **argv) {
  test_create();
  test_insert();
  test_delete();
  custom_test();
  test_min_insert();
  top_k_test();
}

void test_create() {
  Heap *h = new_heap(5);
  Heap *g = new_heap(30);

  assert(is_valid_heap(h));
  assert(is_valid_heap(g));
  assert(h->length == 0);
  assert(g->length == 0);
  assert(h->size == 5);
  assert(g->size == 30);

  printf("Creation test passed!\n");
  free_heap(h);
  free_heap(g);
}

void test_insert() {
  Heap *h = new_heap(3000);
  assert(h->length == 0);
  assert(h->size == 3000);

  heap_insert(h, 2, 10);
  assert(h->length == 1);
  assert(h->items[0].data == 10);

  heap_insert(h, 0.2, 100);
  assert(h->length == 2);
  assert(h->items[0].data == 100);

  for (int i = 0; i < 2000; ++i) {
    heap_insert(h, rand() % 3000, rand() % 50); 
    assert(h->length == 3 + i);
    assert(h->size == 3000);
    assert(is_valid_heap(h));
    printf("Insertion %d good\n", i + 1);
  }

  printf("Insertion test passed!\n");
  free_heap(h);
}

void test_delete() {
  Heap *h = new_heap(30);
  assert(h->length == 0);
  assert(h->size == 30);

  for(int i = 0; i < 25; ++i) {
    heap_insert(h, rand() % 20, rand() % 100);
  }
  assert(h->length == 25);
  assert(is_valid_heap(h));

  for(int i = 0; i < 15; ++i) {
    int min = h->items[0].data;
    int value = heap_pop_min(h);
    
    assert(is_valid_heap(h));
    assert(value == min);
    printf("Deletion %d good\n", i + 1);
    assert(h->length == 24 - i);
    assert(h->size == 30);
  }

  printf("Deletion tests passed!\n");
  free_heap(h);
}


void test_min_insert() {
  Heap *h = new_heap(6000);
  for (int i = 5500; i > 0; --i) {
    heap_insert(h, i, 0);
    assert(is_valid_heap(h));
    assert(0 == heap_peek_min(h));
    assert(i == heap_peek_key(h));
  }
  printf("Minimum insertion test passed.\n");
}


