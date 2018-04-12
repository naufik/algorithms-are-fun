# COMP20007 Design of Algorithms

**stub area to add soon**

### Repeated Source Removal

Method to topologically sort a graph by repeatedly removing a 'source' component, this ends up with a topologically sorted graph as source nodes have to appear early in a sorted order.

Each node is at most in one strongly connected component, if a node is in multiple strongly connected components - then those components are actually a single component. 

## Shortest Path Algorithms

Exploration can only tell that there exists a path without showing you the actual path. Shortest paths gives insight about the best path to go from two nodes $a,b$.

### Weighted Edges in Graphs

In weighted graphs, each edge has a cost, or weight. The distance from $u,v$ is the sum of the weights of the edges connecting them.

### Breadth-First Search

Unlike depth first search, BFS prioritizes scanning **all the siblings** of a specific graph rather than all the children (and the children of those children).

Depth first search is ineffective for finding shortest path. In breadth first search, the path traversed when we meet the destination for the first time is the shortest path between the source and the destination.

Complexity of breadth first search is $O(|V|+|E|)$.

### Djikstra's Algorithm

A very famous shortest path algorithm.

The first variant of Djikstra's algorithm is as follows:

```
dist(s) = 0
K = {}
x@G\{u}: dist(x) = inf

while (K != G) {
   u = min({dist(x): x in G})
   K.append(u)
   for (edge(u,v) : v \notin K) {
      dist(v) = min(dist(u) + w(u,v), dist(v))
   }
}
```

This variation of Djikstra's algorithm has the asymptotic complexity cost of order $\O(|V|^2+|E|)$.

#### Heap Invariant

An implementation with a (heap) priority queue has asymptotic complexity $O((|V|+|E|)\log{|V|})$. The implementation is as follows:


#### Extreme Cases

Djikstra's invariant is broken when we have a **negative cost** or **negative weight**. While the 'length' of a path cannot physically be negative, the algorithm can be used to explore different paths of graphs where weights can be negative  such as financial decisions.

### Shortest Paths in Directed Acyclic Graphs

In DAGs, shortest paths can be found in $\Theta(|V|+|E|)$ time.


