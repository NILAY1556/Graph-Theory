# Lab 14 — Spectral Clustering

## Concepts
- **Spectral Clustering** — use eigenvalues/vectors of the Laplacian to detect natural clusters
- **Fiedler Value λ₂** — 2nd smallest eigenvalue of L; λ₂ > 0 iff graph is connected
- **Fiedler Vector** — eigenvector corresponding to λ₂; its signs reveal the 2-cluster partition
- **Graph Partition** — divide V into groups that minimize cut edges between groups
- **Deflation** — technique to find non-dominant eigenvectors by removing already-found ones

---

## Theory

**Why does the Fiedler vector split the graph?**

The Laplacian L encodes the graph structure. Its eigenvectors capture "smooth" signals on the graph:
- Eigenvector 1 (λ₁=0): constant, no information → ignore
- Eigenvector 2 (λ₂, Fiedler): varies most smoothly, splits the graph at its weakest point

```
Graph: two triangles connected by one bridge
  Cluster A: {0, 1, 2}   (densely connected)
  Cluster B: {3, 4, 5}   (densely connected)
  Bridge:     2 -- 3     (single weak link)

Fiedler vector f:
  f[0], f[1], f[2] ≈ negative values
  f[3], f[4], f[5] ≈ positive values
  Sign of f[i] → cluster assignment!
```

**Partition rule (2 clusters):**
```
Cluster 0: all i where f[i] < 0
Cluster 1: all i where f[i] ≥ 0
```

**Algorithm overview:**
1. Build Laplacian L
2. Find Fiedler vector (2nd eigenvector of L)
3. Assign clusters by sign of Fiedler vector components

---

## Code Walk-through (`lab14.c`)

### `fiedlerVector(fv[])` — key function
**Step 1:** Estimate λ_max via power method on L
```c
for 200 iterations: y = L*x, lmax = x·y, x = normalize(y)
```

**Step 2:** Build shifted matrix M = (λ_max + 1)·I − L
```c
M[i][j] = (i==j ? lmax+1 : 0.0) - Lap[i][j];
```
This flips eigenvalues so the largest of M corresponds to the 2nd smallest of L.

**Step 3:** Power method on M, orthogonalized against the constant vector u=[1/√V,…]
```c
orthogonalize(fv, u);   // remove component along eigvec-1
normalize(fv);
for ITER iterations:
    y = M * fv
    orthogonalize(y, u) // keep orthogonal to constant
    normalize(y)
    fv = y
```

### `orthogonalize(v, u)` — Gram-Schmidt step
```c
double proj = dot(v, u);
for each i: v[i] -= proj * u[i];   // v = v - (v·u)u
```
Removes the "constant" component so we get the Fiedler vector, not the trivial one.

### Output
- Prints Laplacian matrix
- Prints Fiedler vector entries per vertex
- Assigns each vertex to Cluster 0 (f<0) or Cluster 1 (f≥0)

---

## Compile & Run
```bash
gcc lab14.c -o lab14 -lm
./lab14
```

## Quick Reference
| Term | Meaning |
|------|---------|
| λ₂ (Fiedler value) | 2nd smallest eigenvalue of L |
| Fiedler vector | eigenvector for λ₂ |
| λ₂ = 0 | graph is disconnected |
| Larger λ₂ | better connected (harder to cut) |
| Sign of f[i] | cluster assignment for vertex i |
| Deflation / shift | trick to find 2nd eigenvector via power method |
