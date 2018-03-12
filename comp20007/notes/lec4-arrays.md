# COMP20007 - Array Algorithms

## Array Sorting

### Merge Sort

```c
/**
 * THIS IS A PSUEDOCODE
 */
mergesort(data A[], int n) {
  if (n <= 1) {
    return A;
  }

  left = mergesort(A[0, ..., n/2]);
  right = mergesort(A[n/2 + 1, ..., n]);
  return merge(left, right); 
}

merge(data A[], data B[]) {
  int i, j, k = 0;
  data C[];
  
  if (A[i] < B[j]) {
    C[k++] = A[i++];
  } else {
    C[k++] = A[j++];
 }

  return C;
}
```

**Cost analysis of mergesort** (via Master's theorem):

$$
T(n) = 2T(\frac{n}{2})  + O(n) \\
\therefore T(n) \in O(n\log{n})
$$

Note that $$O(n\log{n})$$ is the fastest possible sorting time for atomic values so far.

## Merge-Heavy vs. Partition-Heavy Algorithms

We have shown you a merge-heavy algorithm such as merge-sort, now what about analysis of  partition-heavy algorithms.

**Parititoning is useful for solving two questions**:

- Finding k-th smallest item.
- Sorting an array.


### Quicksort

Remember that quicksort (implemented as `qsort`) in C `stdlib`:

*Implementation later*

## Priority Queues and Heaps

A priority queue is an array structured with several benefits:

- You will always be able to find the smallest element (highest priority).

### Min-Heap

This is often **implemented as a min-heap**, which is tree structure with the following properties:

- A parent is always larger than any of its children.
- The root node is always the smallest element.

**Insertion into a heap**:

Add a new node to the bottom layer of the tree, then sift up that node until:

- Its parent is less than or equal to it **OR**
- It is now the root.

Due to insertion requiring you to compare at least [depth of tree] amount of times, then insertion takes $$O(\log{n})$$ times.

**Array representation**:

A heap is not often represented as an actual tree, but uses an array instead where:

- Children of `A[i]` are `A[2i+1], A[2i+2]`
- The parent of `A[j]` is `(int) A[(j-1)/2`
