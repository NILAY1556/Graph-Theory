# Graph Theory — Lab Solutions
**Course:** Graph Theory (2301CS595)

C implementations of all 15 labs — each with a beginner-friendly solution file and a concept-first README lecture.

---

## What's Inside Each Lab

```
LabXX/
├── labXX.c       ← C solution with full theory comment block + working code
└── README.md     ← Lecture-style notes: concepts → theory → code walkthrough → compile & run
```

---

## Lab Directory

```
Graph-Theory/
│
├── Lab01/  — Graph Representations
│   ├── P1: Directed Graph — Adjacency List
│   │       Build a digraph using linked-list adjacency list; addEdge, printAdjList
│   └── P2: Undirected Graph — Adjacency Matrix & Basic Operations
│           Adjacency matrix, degree, simple/complete/connected checks, BFS
│
├── Lab02/  — BFS: Breadth First Search
│   └── P1: BFS Traversal
│           Queue-based level-order traversal; visited array; adjacency list
│
├── Lab03/  — DFS: Depth First Search
│   └── P1: DFS Traversal
│           Recursive DFS; DFS tree; back edges; visit-order recording
│
├── Lab04/  — Tree Operations
│   └── P1: Tree Metrics
│           Pendent vertices, eccentricity, radius, diameter, center via BFS distances
│
├── Lab05/  — Spanning Trees, Rank & Nullity
│   └── P1: Spanning Tree + Fundamental Circuits
│           Union-Find components; BFS spanning tree; rank r = V−k; nullity μ = E−V+k
│
├── Lab06/  — Articulation Points (Cut Vertices)
│   └── P1: Tarjan's Algorithm for Cut Vertices
│           DFS disc/low arrays; root rule; non-root rule; O(V+E)
│
├── Lab07/  — Connectivity
│   └── P1: Vertex & Edge Connectivity + Whitney's Theorem
│           κ ≤ λ ≤ δ; bridge detection; separable vs biconnected graphs
│
├── Lab08/  — Dominating Sets
│   └── P1: Domination Number γ(G)
│           Bitmask enumeration of all 2^V subsets; isDominating check; minimum set
│
├── Lab09/  — Total Dominating Sets
│   └── P1: Total Domination Number γt(G)
│           Every vertex (including S members) needs a neighbor in S; γt ≥ 2 always
│
├── Lab10/  — Matching in Bipartite Graphs
│   └── P1: Maximal, Maximum & Perfect Matching
│           Greedy maximal; DFS augmenting-path maximum; perfect matching check
│
├── Lab11/  — Hall's Marriage Theorem
│   └── P1: Hall's Condition Check
│           For all S ⊆ L: |N(S)| ≥ |S|; bitmask neighborhood; deficiency formula
│
├── Lab12/  — Graph Matrices
│   └── P1: Adjacency, Degree & Laplacian Matrix
│           Build A, D, L = D−A; verify row-sum=0, diagonal=degree, PSD properties
│
├── Lab13/  — Eigenvalues & Eigenvectors
│   └── P1: Power Method for Dominant Eigenvalue
│           Iterative multiply-normalize loop on A and L; spectral radius
│
├── Lab14/  — Spectral Clustering
│   └── P1: Fiedler Vector & 2-Cluster Partition
│           Shift-deflation to get 2nd eigenvector; cluster by sign of Fiedler vector
│
└── Lab15/  — All-Pairs Shortest Path
    └── P1: Floyd-Warshall Algorithm
            Triple-loop DP; dist[i][j] via relay k; path reconstruction; negative cycle check
```

---

## Lab Summaries

| Lab | Title | Key Topics |
|-----|-------|-----------|
| 01 | Graph Representations | Adjacency list, adjacency matrix, directed/undirected, degree |
| 02 | BFS Traversal | Queue, visited array, level-order exploration |
| 03 | DFS Traversal | Recursive stack, back edges, DFS tree |
| 04 | Tree Operations | Eccentricity, radius, diameter, center, pendent vertices |
| 05 | Spanning Trees, Rank & Nullity | Union-Find, BFS tree, rank r = V−k, nullity μ = E−V+k |
| 06 | Articulation Points | Tarjan's DFS, disc/low values, cut vertex rules |
| 07 | Connectivity | κ ≤ λ ≤ δ (Whitney), bridges, separable vs biconnected |
| 08 | Dominating Sets | Bitmask enumeration, domination number γ(G) |
| 09 | Total Dominating Sets | TDS condition, γt(G), coverage verification |
| 10 | Bipartite Matching | Augmenting paths, greedy maximal, DFS maximum, perfect matching |
| 11 | Hall's Marriage Theorem | N(S) neighborhood, Hall's condition, deficiency |
| 12 | Graph Matrices | Adjacency A, degree D, Laplacian L = D−A, Fiedler value |
| 13 | Eigenvalues & Eigenvectors | Power method, spectral radius, eigenvector convergence |
| 14 | Spectral Clustering | Fiedler vector, deflation, 2-cluster partition by sign |
| 15 | Floyd-Warshall APSP | Triple-loop DP, path reconstruction, negative cycle detection |

---

## Compile & Run

```bash
# Labs 1–12, 15  (no math library needed)
gcc LabXX/labXX.c -o labXX
./labXX

# Labs 13, 14  (use math.h — power method / sqrt)
gcc Lab13/lab13.c -o lab13 -lm
gcc Lab14/lab14.c -o lab14 -lm
```

