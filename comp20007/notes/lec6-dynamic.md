# Dynamic Algorithms

==todo continue==

## Knapsack Problem

Given a list of $n$ items having a weights $w_i$ and value $v_i$ and a maximum capacity $W$, find a list of items $(w, v)$ that fits within the capacity and optimizes the total value.

There are two variations of the Knapsack Problem:

- Allowing repetition (easier).
- No repetitions allowed (harder).

Without repetition, there are $2^n$ possible solutions for a list of $n$ items. A brute-force solution  will not be optimal.

### Greedy Algorithms

Being greedy on $w_i$ or $v_i$, or even being greedy on the ratio $\frac{v_i}{w_i}$ will **not** give a solution that is with optimal values.

### Dynamic Programming Algorithms

#### With Repetition

We can try to "put the highest value item that will fit", hence our value function will be:
$$
V(W) = \max\{V(W-w_i)+v_i\}, \quad V(0) = 0
$$
This is an approach that allows repetition.

```c
table[0] = 0
for (int i = 1; i <= W; ++i) {
	table[i] = max(table[i-weights[j]]) //see above
}
return v[W];
```

The complexity of this algorithm is $O(Wn)$, which is way better than $O(2^n)$.

#### Without Repetition

The algorithm above cannot be implemented for the Knapsack Problem without repetition as it does not take into account all the items that we have previously used.

We can use a prefix table in order to solve this problem and pass it as a parameter to the algorithm.

- Let $K(W, j)$ be the highest value for a knapsack with capacity $W$ and using only the items $(v, w)_{i\cdots j}$.
- Suppose we know the value of $K(w, x)$ s.t.  $x < j$, how do we find the value of $K(w, j)$ from that?

Then our Knapsack value function would be:
$$
K(w, j) = \max\{K(w-w_j, j-1) + v_j, K(w, j-1)\}, \quad 0\in\{w,j\} \implies K(w, j) = 0
$$
This is equivalent adding the items step by step and making sure that it fits. In the $\max$ cases, the left case is the case where we put the item $j$ into the knapsack.

The algorithm's complexity is:

- Space complexity (amount of things stored): $O(Wn)$
- Time complexity: $O(1)$ time per thing, and $O(Wn)$ total.

Note that we can optimize the space complexity:

- We filled in everything but we only need the last row.
- To calculate the last row **only the previous row** is needed.
- Hence we can only keep the last two rows and reduce the space complexity to $O(W)$.

