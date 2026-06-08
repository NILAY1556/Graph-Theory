# Lab 4 — Tree Properties

## Concepts
- **Tree** — a connected graph with no cycles; V vertices, V−1 edges
- **Pendent Vertex (Leaf)** — vertex with degree 1 (only one edge)
- **Degree** — number of edges attached to a vertex
- **Distance d(u,v)** — number of edges on the shortest path between u and v
- **Eccentricity e(v)** — the farthest any vertex is from v: `max over all u of d(v,u)`
- **Radius r(G)** — smallest eccentricity in the graph: `min over all v of e(v)`
- **Diameter d(G)** — largest eccentricity: `max over all v of e(v)`
- **Center** — vertex (or vertices) whose eccentricity equals the radius

---

## Theory

A **tree** is the simplest connected structure. No cycles, just pure paths.

```
Example tree:
      0
     / \
    1   2
   / \
  3   4

Degrees:  0→2, 1→3, 2→1(leaf), 3→1(leaf), 4→1(leaf)
Pendent (leaves): 2, 3, 4
```

**Distance** — shortest path length (BFS gives this in O(V+E)).

**Eccentricity** — "how far is the worst-case destination from me?"

```
e(0) = max(d(0,1), d(0,2), d(0,3), d(0,4)) = max(1,1,2,2) = 2
e(1) = max(1, 2, 1, 1) = 2
e(2) = max(1, 2, 3, 3) = 3
```

**Key theorem:** The center of a tree is always **1 or 2 adjacent vertices** found by repeatedly removing leaves.

---

## Code Walk-through (`lab4.c`)

### `pendentVertices(V)` — count leaves
```c
for (int i = 0; i < V; i++)
    if (adjSize[i] == 1) count++;  // degree-1 = leaf
```

### `bfsDistance(src, dist[], V)` — distances from one vertex
Runs BFS from `src`; `dist[v]` holds the hop count to each vertex.

### `eccentricity(v, V)` — worst-case distance
```c
bfsDistance(v, dist, V);
int ecc = 0;
for (int i = 0; i < V; i++)
    if (dist[i] > ecc) ecc = dist[i];
return ecc;
```

### `findCenterRadiusDiameter(V)`
```c
for each vertex v:
    ecc[v] = eccentricity(v, V)
radius   = min(ecc[])
diameter = max(ecc[])
center   = all v where ecc[v] == radius
```

### `isTree(V, E)` — verification
A graph is a tree if and only if:
- It is **connected** (BFS visits all V vertices), AND
- It has exactly **V−1 edges**.

---

## Compile & Run
```bash
gcc lab4.c -o lab4
./lab4
```

## Quick Reference
| Term | Formula |
|------|---------|
| Pendent vertex | degree = 1 |
| Eccentricity e(v) | max { d(v,u) : u ∈ V } |
| Radius r(G) | min { e(v) : v ∈ V } |
| Diameter d(G) | max { e(v) : v ∈ V } |
| Center | { v : e(v) = r(G) } |
