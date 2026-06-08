# Lab 5 — Spanning Trees, Rank, Nullity & Circuits

## Concepts
- **Spanning Tree** — a subgraph that includes all V vertices, is connected, and has no cycles (V−1 edges)
- **Connected Components** — maximal subgraphs where every vertex can reach every other
- **Rank (r)** — number of edges in a spanning tree = V − (number of components)
- **Nullity (μ)** — number of extra edges (chords) = E − rank = E − V + components
- **Branch** — an edge that belongs to the spanning tree
- **Chord** — an edge NOT in the spanning tree (also called co-tree edge)
- **Fundamental Circuit** — adding one chord to the spanning tree creates exactly one cycle

---

## Theory

**Rank and Nullity** describe the structure of a graph:

```
Given: graph with V vertices, E edges, k connected components
  Rank    r = V − k        (minimum edges to connect everything)
  Nullity μ = E − V + k   (number of independent cycles)
```

**Fundamental Circuits:**
Every chord creates exactly one cycle when added back to the spanning tree.  
If nullity = 3, there are exactly 3 fundamental circuits (one per chord).

**Example:**
```
V=5, E=7, k=1 (connected)
Rank    = 5−1 = 4
Nullity = 7−5+1 = 3  → 3 independent cycles
```

---

## Code Walk-through (`lab5.c`)

### Union-Find (Disjoint Set Union) — for connected components
```c
int parent[MAX_V];
int find(int x) { return parent[x]==x ? x : find(parent[x]); }
void unite(int a, int b) { parent[find(a)] = find(b); }
```
- Each vertex starts as its own component (`parent[i]=i`).
- `unite(u,v)` merges two components.
- Count components = number of vertices where `parent[i]==i`.

### `buildSpanningTree()` — BFS spanning tree
```c
// BFS; when we first visit vertex v from u:
//   tree edge = (u, v)
// If v already visited → chord
```
Tree edges form the spanning tree; leftover edges are chords.

### `findFundamentalCircuits()` — per chord
For each chord (u, v), run BFS in the spanning tree from u to v.  
The path u→…→v in the tree **plus** the chord (u,v) = one fundamental circuit.

### Output summary
```
Rank    r = V - k = 5 - 1 = 4
Nullity μ = E - V + k = 7 - 5 + 1 = 3
Chords (3): give 3 fundamental circuits
```

---

## Key Formulas
| Quantity | Formula |
|----------|---------|
| Rank | r = V − k |
| Nullity | μ = E − V + k |
| Tree edges | r = V − k |
| Chords | μ = E − r |

---

## Compile & Run
```bash
gcc lab5.c -o lab5
./lab5
```
