# Lab 15 — All-Pairs Shortest Path: Floyd-Warshall

## Concepts
- **Shortest Path** — minimum total weight path between two vertices
- **All-Pairs Shortest Path (APSP)** — compute shortest distances for every (u, v) pair at once
- **Floyd-Warshall** — dynamic programming algorithm for APSP in O(V³)
- **Intermediate Vertex k** — "Can going through k shorten the path i→j?"
- **Negative Cycle** — cycle with negative total weight; makes APSP undefined (detected when dist[i][i] < 0)
- **Path Reconstruction** — `next[i][j]` stores the next hop so full paths can be printed

---

## Theory

**Core idea:** Try every vertex k as a "relay station" between every pair (i, j).

```
If dist[i][k] + dist[k][j] < dist[i][j]:
    update dist[i][j] = dist[i][k] + dist[k][j]
```

**Algorithm (3 nested loops):**
```
Initialize: dist[i][j] = weight(i,j), dist[i][i] = 0, else ∞

For k = 0 to V-1:          // try each intermediate vertex
  For i = 0 to V-1:
    For j = 0 to V-1:
      dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
```

**Worked example:**
```
Graph: 0-1 (w=4), 1-2 (w=2), 0-3 (w=8), 1-4 (w=3), 2-4 (w=1), 3-4 (w=5)

Initial dist[0][2] = ∞ (no direct edge)
After k=1: dist[0][2] = dist[0][1] + dist[1][2] = 4+2 = 6
After k=4: dist[0][2] via 0→1→4→2 = 4+3+1 = 8 (no improvement)
Final dist[0][2] = 6  ✓
```

**Comparison table:**
| Algorithm | Paths | Time | Negative weights |
|-----------|-------|------|-----------------|
| Dijkstra | Single source | O((V+E)logV) | No |
| Bellman-Ford | Single source | O(VE) | Yes |
| **Floyd-Warshall** | **All pairs** | **O(V³)** | **Yes (no neg cycle)** |

---

## Code Walk-through (`lab15.c`)

### `init(edges, numEdges)` — build initial distance matrix
```c
dist[i][i] = 0;    // self-distance = 0
dist[i][j] = INF;  // no path known yet
// for each edge (u,v,w):
dist[u][v] = dist[v][u] = w;   // undirected
next_v[u][v] = v;              // direct hop
```

### `floydWarshall()` — the triple loop
```c
for (int k = 0; k < V; k++)
  for (int i = 0; i < V; i++)
    for (int j = 0; j < V; j++) {
        if (dist[i][k]==INF || dist[k][j]==INF) continue;
        int via_k = dist[i][k] + dist[k][j];
        if (via_k < dist[i][j]) {
            dist[i][j] = via_k;
            next_v[i][j] = next_v[i][k];  // track the route
        }
    }
```

### `printPath(src, dst)` — follow next_v to reconstruct path
```c
printf("%d", src);
int cur = src;
while (cur != dst) { cur = next_v[cur][dst]; printf(" -> %d", cur); }
```

### Negative cycle detection
```c
for each i: if (dist[i][i] < 0) → negative cycle detected
```

---

## Compile & Run
```bash
gcc lab15.c -o lab15
./lab15
```

## Quick Reference
| Term | Detail |
|------|--------|
| Time complexity | O(V³) — three nested loops |
| Space complexity | O(V²) — distance matrix |
| INF | large sentinel (99999 here) |
| Negative cycle | dist[i][i] < 0 after algorithm |
| Path recovery | follow next_v[i][j] until destination |
| APSP vs SSSP | APSP = all pairs; SSSP = single source |
