# Lab 1 — Graph Representation

## Concepts
- **Graph** — a set of vertices (nodes) connected by edges
- **Directed Graph (Digraph)** — edge A→B does NOT imply B→A
- **Undirected Graph** — edge A–B goes both ways
- **Adjacency List** — each vertex stores a linked list of its neighbors
- **Adjacency Matrix** — 2-D array; `mat[i][j]=1` means edge i–j exists
- **Degree** — number of edges touching a vertex
- **Simple Graph** — no self-loops, no duplicate edges
- **Complete Graph Kₙ** — every pair of vertices is connected; edges = n(n−1)/2
- **Connected Graph** — every vertex is reachable from every other vertex

---

## Theory

A **graph** G = (V, E) has a vertex set V and an edge set E.

**Two ways to store a graph:**

| Storage | Best for | Memory |
|---------|----------|--------|
| Adjacency List | Sparse graphs (few edges) | O(V + E) |
| Adjacency Matrix | Dense graphs / quick edge check | O(V²) |

**Handshaking Lemma** — sum of all degrees = 2 × E (every edge contributes 2 to the total degree count).

**Connectivity check** — run BFS/DFS from any vertex. If every vertex is visited → connected.

---

## Problem 1 — Directed Graph via Adjacency List (`lab1_p1.c`)

### Data Structure
```c
struct Node {
    int vertex;
    struct Node *next;   // pointer to next neighbor
};
struct Node *adj[MAX_V]; // adj[i] = head of neighbor list of vertex i
```
Each vertex owns a **linked list** of destinations.

### Key Functions
| Function | What it does |
|----------|-------------|
| `newNode(v)` | Allocates a new list node for vertex `v` |
| `addEdge(src, dest)` | Appends `dest` to the list of `src` (directed) |
| `printAdjList(V)` | Loops over each vertex and prints its list |
| `freeAdj(V)` | Walks every list and calls `free()` — avoid memory leaks |

### Walk-through
1. All list heads start as `NULL` (empty).
2. `addEdge(0,1)` → traverses list of vertex 0 to the end, appends node(1).
3. Repeat for all edges.
4. Print: for each vertex i, follow pointers and print vertex numbers.

---

## Problem 2 — Undirected Graph via Adjacency Matrix (`lab1_p2.c`)

### Key Functions
| Function | What it does |
|----------|-------------|
| `buildMatrix(edges)` | Sets `mat[u][v]=mat[v][u]=1` and increments degree for each edge |
| `printMatrix()` | Prints the V×V grid |
| `printAdjList()` | Scans each row for 1s to list neighbors |
| `printDegree()` | Prints `degree[v]` for each vertex |
| `isConnected()` | BFS from vertex 0; connected if all vertices visited |
| `printProperties()` | Checks simple (no `mat[i][i]`), complete (E == V(V−1)/2), connected |

### Walk-through
```
Input: V=5, edges={0-1, 0-2, 1-2, 2-3, 3-4}
mat[0][1]=mat[1][0]=1  (edge 0-1)
...
degree[2] = 3  (connects to 0, 1, 3)
Complete? E=5, need 5*(5-1)/2=10 → NO
```

---

## Compile & Run
```bash
# Problem 1
gcc lab1_p1.c -o lab1_p1
./lab1_p1

# Problem 2
gcc lab1_p2.c -o lab1_p2
./lab1_p2
```
