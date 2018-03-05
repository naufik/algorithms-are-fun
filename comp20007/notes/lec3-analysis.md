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
  $O(3000n^2)$ is treated the same as $O(0.020n^2)$

- Logarithmic bases (for the same reason as constants).

  Recall $$\log_b{n} = \frac{\log{n}}{\log{b}}$$.

  We simply say $O(\log{n})$ for **all logarithmic bases**.

### Big-O Notation

Characterize running times of algorithms based on the RAM-world model of 'one unit of time'.

Standard notation to describe the **growth** of functions.

It is defined formally in mathematics as:
$$
g(n) \in O(f(n)) \iff \forall{n}\in\mathbb{N}\exists{c}\in\mathbb{R}^+: c\cdot f(n)
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

- $a<b \implies n^a \in O(n^b)$

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