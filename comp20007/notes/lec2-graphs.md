# COMP20007 - Graphs

Models a 'network', 'pathways' between points called *nodes* or *vertices*.

Similar to a tree, but the nodes do not 'parent-child' restrictions. i.e. a node may have multiple parents.

Terminologies:

- **Nodes**: Points in a graph.
- **Edges**: A connection between *two* nodes.
- **Root**: A node such that *every other node is traversible* from that node.
Given any destination node *k*, it is possible to go from the *root* to *k*.

Applications:

- Transport.
- Networks.
- Relationship and connectivity maps.

## Levels of Abstraction in Graphs

Simple graphs often abstract detailed ideas, for instance if we have simplified a graph of the london train network as follows:

[image later]

We lost the following information:

- Do we need to change trains when commuting between London & Picadilly?
- What's the distance/travel time between any given two adjacent stations?
- and many more...

## Edges

Types of edges:

- **Directed**: One way connection, you can go $A \to B$ but you cannot go $B \to A$.
- **Undirected**: Two-way connection, if you can go $A \to B$ then you can go $B \to A$.

## Graph Components 

- **Strongly Connected**: Every node can be reached from every other node.
- **Sink**: A group of strongly-connected node in a graph that cannot be escaped. If we start from any node in this group then all the possible destinations are only nodes within the group.

## Types of Graphs

### Interaction Network

**Edges** indicate two events that **cannot occur simultaneously**.

Used in:

- Traffic light timing systems.
- Timetabling.
- Room bookings.
- Protein-with-protein interaction

## Graph Impementation in C

### Structure

**Nodes** are represented as a multi-'vector' `{v,p[]}` where:

- `v`: is the value of the node.
- `p[]`: an array to pointers of the edges connected to this node.

**Edges** (assuming that it is directed) are represented as a `struct` containing two pointers:

- `node`: pointer to the node that it connects to node.

In this representation:

- **Undirected edges** are represented by having two edges, one connecting from `A` to `B` and the other connecting from `B` to `A`.


