# Analysis of Algorithms

What to be analyzed:

- Correctness.
- Ease of coding.
- Runtime (experimental and theoretical/practical), how long does it take to run with the current state of computing power?

## RAM-World Model

*Reference: Lecture 2, Slide 5*

Data is represented in words of fixed-length in bits.

Fundamental operations are assumed to take **one unit of time**:

- Basic arithmetic
- Memory access
- Comparisons
- Logical operators
- Bitwise operators

Past:

- Big delays to write to RAM.

## Running Time 'Orders'

We use the notion of **order** of functions when we analyze the running time of algorithms. 

Order only cares about the function when the input `n` grows in size / approaches infinity (hence asymptotic analysis).

When talking about order, we neglect:

- Constants
  $O(3000n^2)$ is treated the same as $O(0.020n^2)$.

  We simply say $O(n)$.

- Logarithmic bases (for the same reason as constants).

  Recall $$\log_b{n} = \frac{\log{n}}{\log{b}}$$.

  We simply say $O(\log{n})$ for **all logarithmic bases**.

### Big-O Notation

Characterize running times of algorithms based on the RAM-world model of 'one unit of time'.

Standard notation to describe the **growth** of functions.

It is defined formally in mathematics as:
$$
g(n) \in O(f(n)) \iff \forall{n}\in\mathbb{\mathbb{N}}, \exists{c}\in\mathbb{R}^+: c\cdot f(n)
$$

- $g(n)$ is of order $f(n)$ **iff**  $g(n)$ is less than a multiple for $f(n)$ for all n.

### Big-Omega Notation

$$
g\in O(f(n)) \iff f \in \Omega(g(n))
$$

### Big-Theta Notation

$$
g\in O(f(n)) \wedge g\in\Omega(f(n)) \implies g\in \Theta(f(n))
$$

### Analysis Shorthands

- $a \lt b \implies n^a \in O(n^b)$

We can compare the order of two functions $f, g$ by performing the following limit comparison:
$$
L(x) = \lim_{n \to \infty} \frac{f(x)}{g(x)} = \left\{\array{0 & f < g \\ c & f = g \\ \infty & f > g}\right.
$$


### Little-O Notation

$$
g \in o(f(n)) \iff \forall c\in\mathbb{R}^+: g(n) \leq f(n)
$$

### Example Analysis

With the Fibonacci Algorithm below:

```c
int fib(int n) {
    int A[n]; // O(1)
    
    A[0] = 0; // O(1)
    A[1] = 1; // O(1)
    
    for (i=1;i<n;i++){
        A[i] = A[i-1] + A[i-2] // O(1) looped (n-2) times
    }
}
```

We are often interested only the big-O time of the worst case scenario, or the average case scenario, examples:

- Quicksort has worst case time $O(n^2)$, but the cases are really rare, the average case is $O(n\log{n})$.
- Hashing has worst case $O(n)$, but most hash functions are well designed so the *likely* worst case and the average case is $O(1)$.

### Coding Practice

- Do not spend too much time shaving down constants.
- Always do optimization **in respect to big-O notation**.
- Careless algorithms can run a really, really long time (like **5 years**).

## Divide and Conquer

Solving a problem with a large amount of data by:

- Dividing into smaller pieces.
- Solve the **same** problem on each piece.
- Combine into a solution to the whole data.

We always have a special case for when the input is **tiny**. (e.g. special case of unit or empty arrays in quicksort).

### Induction

Complexity of recursive algorithms can often be shown via induction.

**Principle**:

If we can prove:

- The base case (i.e. $P(0)$ or $P(1)$), **and**
- For a general $k$, if $P(k)$ is true then $P(k+1)$ is true.

Therefore we can conclude that the proposition $P$ is true for all integers starting at the base case (or natural numbers).

A variation of the induction is called **strong induction**, the difference being:

- Instead of making the assumption $P(k)$ is true, we assume $P(n)$ is true for all $n \leq k$ to prove $P(k)$.

## The Master Theorem

The Master Theorem describes the time complexity for **any** algorithm which has the time function as follows:

$$
T(n) = aT(\frac{n}{b}) + O(n^c)
$$

Then we can conclude that:

$$
T(n) \in \left\{\array{O(n^d) & d \gt \log_b{a} \\ O(n^d\log{n}) & d = \log_b{a} \\ O(n^{\log_b{a}}) & d \lt \log_b{a} }\right.
$$
