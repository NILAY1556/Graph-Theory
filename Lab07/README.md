# Lab 7 — Connectivity

## Concepts
- **Vertex Connectivity κ(G)** — min number of vertices to remove to disconnect the graph
- **Edge Connectivity λ(G)** — min number of edges to remove to disconnect the graph
- **Minimum Degree δ(G)** — smallest degree among all vertices
- **Bridge** — an edge whose removal disconnects the graph (edge version of articulation point)
- **Separable Graph** — has at least one cut vertex; κ(G) = 1
- **Non-Separable (Biconnected)** — no cut vertex; κ(G) ≥ 2
- **Whitney's Theorem** — κ(G) ≤ λ(G) ≤ δ(G) always holds

---

## Theory

**How robust is a graph?** That's what connectivity measures.

```
                κ ≤ λ ≤ δ
  (vertex cut) ≤ (edge cut) ≤ (min degree)
```

**Bridge detection** (from Tarjan DFS):
- An edge (u, v) is a **bridge** if `low[v] > disc[u]`
- "Low" cannot reach back past u → removing (u,v) isolates the subtree at v.

**Example graph used in lab:**
```
  0 -- 1       Triangle A: {0, 1, 2}
  |  /         Bridge:      2 -- 3
  2 -- 3       Triangle B: {3, 4, 5}
       |  \
       4 -- 5
```
- Vertex 2 and vertex 3 are cut vertices → **separable**
- Edge 2--3 is a **bridge** → λ(G) = 1

---

## Code Walk-through (`lab7.c`)

### `addEdge(u, v)` — builds adjacency list + tracks degree
```c
degree[u]++; degree[v]++;  // used to compute δ(G)
```

### `dfs(u, parent)` — Tarjan's DFS for cut vertices AND bridges
```c
if (low[v] > disc[u]) isBridge[u][v] = 1;   // bridge rule
if (low[v] >= disc[u] && parent != -1) isAP[u] = 1; // cut vertex rule
```

### Computing connectivity values
```c
int lambda = bridges > 0 ? 1 : 2;  // if any bridge exists, λ=1
int kappa  = hasAP    ? 1 : 2;      // if any cut vertex, κ=1
// then verify: kappa <= lambda <= minDeg
```

### Output
- Lists all bridges and articulation points
- Prints κ, λ, δ and verifies Whitney's inequality
- Declares graph separable or non-separable

---

## Compile & Run
```bash
gcc lab7.c -o lab7
./lab7
```

## Quick Reference
| Symbol | Meaning | Value if … |
|--------|---------|------------|
| κ(G) | min vertices to remove | = 1 if cut vertex exists |
| λ(G) | min edges to remove | = 1 if bridge exists |
| δ(G) | minimum degree | count edges per vertex |
| Whitney | κ ≤ λ ≤ δ | always true |
| Separable | κ = 1 | has a cut vertex |
| Biconnected | κ ≥ 2 | no cut vertex |
