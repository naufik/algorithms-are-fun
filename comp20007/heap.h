typedef struct {
  float key;
  int data;
} HeapItem;

typedef struct {
  HeapItem *items;
  int length;
  int size;
} Heap;

// Creation of a new (empty heap).
Heap *new_heap(int size);
// Insertion of a data into a heap.
void heap_insert(Heap *h, float key, int data);
// Get the data with the smallest key in a heap and removes it.
int heap_pop_min(Heap *h);
// Peeks the data with the smallest key in the heap.
int heap_peek_min(Heap *h);
// Peeks the smallest key in the heap.
float heap_peek_key(Heap *h);
// Frees the memory used by the heap.
void free_heap(Heap *h);

// 'Fixes' the heap so that it maintains the heap property
// a.k.a 'sift-down'.
void sift_down(Heap *h, int i);
// 'Sifts up' the heap so that it maintains the heap property
void sift_up(Heap *h, int i);