# Lab 13 — Eigenvalues & Eigenvectors (Power Method)

## Concepts
- **Eigenvalue λ** — scalar where A·v = λ·v; multiplying A by v just scales v
- **Eigenvector v** — the non-zero vector that only gets scaled (direction preserved)
- **Dominant Eigenvalue** — eigenvalue with the largest absolute value
- **Power Method** — iterative algorithm: multiply, normalize, repeat → converges to dominant eigenvalue
- **Spectral Radius ρ(G)** — largest eigenvalue of the adjacency matrix A
- **Fiedler Value** — 2nd smallest eigenvalue of Laplacian L; measures connectivity

---

## Theory

**What is an eigenvalue?**
```
If A · v = λ · v, then:
  - v is an eigenvector (direction unchanged by A)
  - λ is the eigenvalue (scaling factor)
```

**Power Method — step by step:**
```
Start: x = [1, 1, 1, ..., 1]
Loop:
  y = A · x          (matrix-vector multiply)
  λ = max(|y|)        (biggest component ≈ eigenvalue)
  x = y / λ           (normalize)
Until λ stops changing.
```

**Why does this work?**  
Any vector is a combination of all eigenvectors. Repeated multiplication by A amplifies the dominant eigenvector's component until it dominates the rest.

**Graph spectral facts:**
```
For adjacency matrix A:
  Spectral radius ρ ≥ average degree
  For k-regular graph: ρ = k exactly

For Laplacian L:
  Smallest eigenvalue = 0  (constant vector [1,1,…,1] is eigenvec)
  Largest eigenvalue ≤ 2 · max_degree
```

---

## Code Walk-through (`lab13.c`)

### `matVec(M, vec, result)` — matrix × vector
```c
for (int i = 0; i < V; i++) {
    result[i] = 0.0;
    for (int j = 0; j < V; j++)
        result[i] += M[i][j] * vec[j];
}
```

### `powerMethod(M, vec)` — returns dominant eigenvalue
```c
vec = [1, 1, ..., 1]          // starting guess
for up to 1000 iterations:
    newvec = M * vec           // multiply
    lambda = max(|newvec|)     // estimate eigenvalue
    vec = newvec / lambda      // normalize
    if |lambda - prevLambda| < EPS: break
return lambda
```

### Main — runs Power Method on both A and L
1. Builds adjacency matrix A and Laplacian L
2. Calls `powerMethod(A, ...)` → spectral radius of A
3. Calls `powerMethod(L, ...)` → largest eigenvalue of L
4. Prints both eigenvalues and their eigenvectors

---

## Compile & Run
```bash
gcc lab13.c -o lab13 -lm
./lab13
```
`-lm` is needed for `fabs()` and `sqrt()` from `math.h`.

## Quick Reference
| Concept | Formula / Note |
|---------|---------------|
| Eigenvalue equation | A · v = λ · v |
| Power method | iterate: y=A·x, λ=max(\|y\|), x=y/λ |
| Spectral radius ρ | largest eigenvalue of A |
| k-regular graph | ρ = k |
| Laplacian smallest | λ₁ = 0 always |
| Convergence | stops when Δλ < 10⁻⁹ |
