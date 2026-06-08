# Lab 6 — Articulation Points

## Concepts
- **Articulation Point (Cut Vertex)** — a vertex whose removal disconnects the graph
- **DFS Tree** — the tree formed by DFS traversal edges
- **Discovery Time (disc[v])** — the DFS timestamp when vertex v is first visited
- **Low Value (low[v])** — the earliest discovery time reachable from the subtree rooted at v using at most one back edge
- **Back Edge** — a DFS edge that goes to an ancestor (creates a cycle)
- **Tarjan's Algorithm** — efficient O(V+E) method to find all articulation points

---

## Theory

**When is vertex u an articulation point?**

Two rules (from Tarjan's algorithm):

1. **Root rule:** If u is the DFS root AND has more than 1 child in DFS tree → u is an articulation point.
2. **Non-root rule:** If u is NOT the root AND has a child v where `low[v] >= disc[u]` → u is an articulation point.
   - `low[v] >= disc[u]` means: the subtree below v cannot "escape" past u via a back edge.

**Intuition for low[v]:**
```
low[v] = min of:
  disc[v]            (itself)
  disc[w]            (for any back edge v→w)
  low[child]         (for any DFS-tree child)
```
If v can reach an ancestor of u via a back edge, the subtree "escapes" — removing u won't disconnect it.

---

## Code Walk-through (`lab6.c`)

### Key arrays
```c
int disc[MAX_V];   // discovery time of each vertex
int low[MAX_V];    // low value of each vertex
int isAP[MAX_V];   // isAP[v]=1 if v is an articulation point
int timer_val;     // global DFS clock
```

### `dfs(u, parent)` — the core
```c
disc[u] = low[u] = timer_val++;   // stamp this vertex
for each neighbor v:
    if not visited:
        children++;
        dfs(v, u);                // recurse
        low[u] = min(low[u], low[v]);   // propagate low values
        // Root rule:
        if parent == -1 && children > 1 → isAP[u] = 1
        // Non-root rule:
        if parent != -1 && low[v] >= disc[u] → isAP[u] = 1
    else if v != parent:
        low[u] = min(low[u], disc[v]);  // back edge: update low
```

### Example trace
```
Graph: 0-1-2-3-4  (path)
disc:  0=0, 1=1, 2=2, 3=3, 4=4
low:   4=4, 3=3, 2=2, 1=1, 0=0
Articulation points: 1, 2, 3  (removing any splits the path)
```

### Output
The code also prints the disc/low table for every vertex so you can trace the algorithm manually.

---

## Compile & Run
```bash
gcc lab6.c -o lab6
./lab6
```

## Quick Rule Summary
| Case | Articulation point condition |
|------|------------------------------|
| DFS root | has ≥ 2 DFS children |
| Non-root u, child v | `low[v] >= disc[u]` |
