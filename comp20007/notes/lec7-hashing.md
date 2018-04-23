# Hashing

A hash function is a function that maps an object from a set of keys $S$ to integers $\{0, \cdots, k\}$. This is heavily used for 'dictionary'-type data structures, also known as hash tables.

### Hashing Integers

When the input is an integer, then the set of keys $S$ is easy to handle because the hash functions can simply be integer arithmetic functions. A common hash function is
$$
h(n) = An\mod{k}
$$
Where $A$ is preferably prime, and must not be a power of $k$.

- Note that if $A = k^c, c \in \mathbb{N} \implies h(n) = n\mod{k}$.
- There is a definite collision between $n, n+k$.

Prime value of $A$ contributes to the likelihood that $h(n)$ is uniform.

### Hashing Strings

Most hash functions are $O(|S|)$ .

## Handling Hash Collisions

A collision is when for distinct $u,v \in S$, we have the property $h(u) = h(v)$.

No matter how hard we try to handle collisions, we will always have collisions in the end (errata: the pigeonhole principle).

### Separate Chaining

Instead of having one slot per hash index, we have a single collection for every slot that can contain multiple items (also known as buckets). The collection can be an:

- Array
- Linked List

Arrays might be a better implementation in practice because computer caches will expect that the **next slot in memory** will be the next used and will attempt to make optimization, however nodes in linked lists are scattered all over the memory.

We will lost the $O(1)$ worst-case access and deletion time, however it is still $O(1)$ in the average case.

Optimizations:

- Skew: if there is any skew (i.e. some items accessed more frequently than others), then put that in front of the linked list. Sort that collection by "frequent access score"