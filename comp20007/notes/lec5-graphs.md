# COMP20007 Design of Algorithms

**stub area to add soon**

### Repeated Source Removal

Method to topologically sort a graph by repeatedly removing a 'source' component, this ends up with a topologically sorted graph as source nodes have to appear early in a sorted order.

Each node is at most in one strongly connected component, if a node is in multiple strongly connected components - then those components are actually a single component. 

## Shortest Path Algorithms

Exploration can only tell that there exists a path without showing you the actual path. Shortest paths gives insight about the best path to go from two nodes $a,b$.

### Weighted Graphs

Each edge has a cost, or weight. The distance from $u,v$ is the sum of the weights of the edges connecting them.

### Breadth-First Search

Unlike depth first search, BFS prioritizes scanning **all the siblings** of a specific graph rather than all the children (and the children of those children).

Depth first search is ineffective for finding shortest path. In breadth first search, the path traversed when we meet the destination for the first time is the shortest path between the source and the destination.

Complexity of breadth first search is $O(|V|+|E|)$.
