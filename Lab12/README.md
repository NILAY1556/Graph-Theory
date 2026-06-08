# Lab 12 — Graph Matrices: Adjacency, Degree, Laplacian

## Concepts
- **Adjacency Matrix A** — A[i][j] = 1 if edge {i,j} exists, 0 otherwise
- **Degree Matrix D** — diagonal matrix; D[i][i] = degree of vertex i
- **Laplacian Matrix L** — L = D − A
- **Positive Semi-Definite** — all eigenvalues ≥ 0
- **Fiedler Value λ₂** — 2nd smallest eigenvalue of L; measures algebraic connectivity

---

## Theory

**Adjacency Matrix (A):**
```
Graph: 0-1, 1-2, 0-3, 1-4, 3-4

     0  1  2  3  4
0  [ 0  1  0  1  0 ]
1  [ 1  0  1  0  1 ]
2  [ 0  1  0  0  0 ]
3  [ 1  0  0  0  1 ]
4  [ 0  1  0  1  0 ]
```

**Degree Matrix (D):** — only diagonal entries
```
D[0][0]=2, D[1][1]=3, D[2][2]=1, D[3][3]=2, D[4][4]=2
```

**Laplacian L = D − A:**
```
     0   1   2   3   4
0  [ 2  -1   0  -1   0 ]
1  [-1   3  -1   0  -1 ]
2  [ 0  -1   1   0   0 ]
3  [-1   0   0   2  -1 ]
4  [ 0  -1   0  -1   2 ]
```

**Key properties of L:**
1. Every row sums to **0** (diagonal = sum of off-diagonal magnitudes)
2. Symmetric (since graph is undirected)
3. All eigenvalues ≥ 0 (positive semi-definite)
4. Smallest eigenvalue λ₁ = **0** always
5. Number of zero eigenvalues = number of **connected components**
6. λ₂ > 0 iff graph is **connected**; larger λ₂ = better connected

---

## Code Walk-through (`lab12.c`)

### `addEdge(u, v)` — builds A and D simultaneously
```c
A[u][v] = A[v][u] = 1;  // symmetric adjacency
D[u][u]++;               // degree of u
D[v][v]++;               // degree of v
```

### `buildLaplacian()` — element-wise L = D − A
```c
for (int i = 0; i < V; i++)
    for (int j = 0; j < V; j++)
        L[i][j] = D[i][j] - A[i][j];
```

### `verifyLaplacian()` — automated property checks
```c
// Property 1: row sums = 0
for each row i: sum = sum(L[i][*]); check sum == 0

// Property 2: diagonal = degree
for each i: check L[i][i] == D[i][i]

// Property 3: off-diagonal = -A
for i != j: check L[i][j] == -A[i][j]
```

### `printMatrix(M, name)` — formatted grid display
Prints column headers then each row with a labeled row index.

---

## Compile & Run
```bash
gcc lab12.c -o lab12
./lab12
```

## Quick Reference
| Matrix | Formula | Key property |
|--------|---------|--------------|
| A | A[i][j] = 1 if edge | symmetric, 0/1 entries |
| D | D[i][i] = deg(i) | diagonal only |
| L | L = D − A | row sums = 0, PSD |
| λ₁(L) | always 0 | constant vector is eigenvec |
| λ₂(L) | Fiedler value | 0 iff disconnected |
| #(λ=0) | connected components | count zero eigenvalues |
