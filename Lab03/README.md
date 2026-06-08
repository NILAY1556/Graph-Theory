# Lab 3 — DFS: Depth-First Search

## Concepts
- **DFS (Depth-First Search)** — explore as deep as possible before backtracking
- **Recursion** — a function that calls itself; DFS uses the call stack as its "memory"
- **Visited array** — prevents revisiting vertices and infinite loops
- **DFS Forest** — running DFS on all vertices produces a collection of DFS trees

---

## Theory

Where BFS spreads wide, **DFS goes deep**. It's like exploring a maze: you keep going forward until you hit a dead end, then you back up and try another path.

```
Graph:  0 -- 1 -- 3
        |    |
        2    4
DFS from 0: visit 0 → go to 1 → go to 2 (dead end, back) → go to 3 → go to 4
Order: 0, 1, 2, 3, 4   (depends on adjacency list order)
```

**Algorithm (recursive):**
```
dfs(u):
  mark u as visited
  record u in order
  for each neighbor v of u:
    if v not visited:
      dfs(v)   ← go deeper
```

**Key properties:**
- Discovers ALL vertices reachable from the source.
- Naturally computes **discovery timestamps** (useful for articulation points later).
- `dfsAll()` handles **disconnected graphs** by calling `dfs` on every unvisited vertex.

**Complexity** — Time: O(V + E) | Space: O(V) for recursion stack

---

## Code Walk-through (`lab3.c`)

### Storage
```c
int adj[MAX_V][MAX_V];  // adjacency list (array-based)
int adjSize[MAX_V];
int visited[MAX_V];
int order[MAX_V];       // DFS traversal order
int orderSize;
```

### `dfs(u)` — recursive
```c
void dfs(int u) {
    visited[u] = 1;
    order[orderSize++] = u;    // record this vertex
    for (int i = 0; i < adjSize[u]; i++) {
        int v = adj[u][i];
        if (!visited[v]) dfs(v);   // go deeper
    }
}
```
Each recursive call "dives" one level deeper. When no unvisited neighbors remain, the function returns (backtracks).

### `dfsAll(V)` — handles disconnected graphs
```c
void dfsAll(int V) {
    memset(visited, 0, sizeof(visited));
    orderSize = 0;
    for (int i = 0; i < V; i++)
        if (!visited[i]) dfs(i);  // start new DFS tree for each component
}
```

### BFS vs DFS comparison
| Property | BFS | DFS |
|----------|-----|-----|
| Data structure | Queue | Call stack (recursion) |
| Order | Level by level | Deep first |
| Shortest path | Yes (unweighted) | No |
| Memory | O(V) queue | O(V) stack |
| Use case | Shortest path, connectivity | Topological sort, cycles, articulation pts |

---

## Compile & Run
```bash
gcc lab3.c -o lab3
./lab3
```
