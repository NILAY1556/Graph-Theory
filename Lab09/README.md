# Lab 9 — Total Dominating Sets (Focused)

## Concepts
- **Total Dominating Set (TDS)** — every vertex in V (including those IN S) must have ≥1 neighbor in S
- **Total Domination Number γt(G)** — minimum size of any TDS
- **Open Neighborhood N(v)** — all neighbors of v, does NOT include v itself
- **Coverage** — how many vertices are "covered" (have a neighbor in S)

---

## Theory

**Key difference from regular dominating set:**

| Type | Who needs a neighbor in S? |
|------|---------------------------|
| Dominating Set | only vertices NOT in S |
| **Total** Dominating Set | **every** vertex, including those in S |

This means: no isolated vertex is allowed within S. Every member of S must have a buddy also in S.

**Mathematical condition:**
```
S is a TDS  ⟺  ∀ v ∈ V,  N(v) ∩ S ≠ ∅
```
"For every vertex v, at least one of v's neighbors is in S."

**Important bounds:**
```
γt(G) ≥ 2           (always, since each S-vertex needs another S-neighbor)
γ(G) ≤ γt(G) ≤ 2·γ(G)
For path Pn:  γt = ⌈n/2⌉
For cycle Cn: γt = ⌈n/2⌉
```

**Example with the lab graph:**
```
  0 - 1 - 2 - 3
      |       |
      4 - 5 - 6

S = {1, 2, 4, 5} ?
  Check each vertex:
    0: neighbor 1 in S ✓    1: neighbor 2 (or 4) in S ✓
    2: neighbor 1 in S ✓    3: neighbor 2 in S ✓
    4: neighbor 1 in S ✓    5: neighbor 4 (or 2) in S ✓
    6: neighbor 5 in S ✓
  All pass → valid TDS of size 4
```

---

## Code Walk-through (`lab9.c`)

### `isTDS(mask)` — check total dominating condition
```c
for (int v = 0; v < V; v++) {    // check EVERY vertex
    int hasNeighborInS = 0;
    for (int i = 0; i < adjSize[v]; i++)
        if (mask & (1 << adj[v][i])) { hasNeighborInS = 1; break; }
    if (!hasNeighborInS) return 0;   // this vertex fails
}
return 1;
```

### Brute-force minimum TDS
```c
for (int mask = 1; mask < (1 << V); mask++) {
    if (isTDS(mask) && popcount(mask) < minSize) {
        minSize = popcount(mask);
        bestMask = mask;
    }
}
```

### Verification output
After finding the minimum TDS, the code prints for each vertex which of its neighbors are in S, confirming every vertex is covered.

### `coverage(mask)` — count how many vertices have a neighbor in S
```c
for each v: check if any neighbor is in mask → if yes, count++
```

---

## Compile & Run
```bash
gcc lab9.c -o lab9
./lab9
```

## Quick Reference
| Symbol | Meaning |
|--------|---------|
| TDS | Total Dominating Set |
| γt(G) | Total domination number (minimum TDS size) |
| N(v) | Open neighborhood (does not include v) |
| γt ≥ 2 | Always, because S-vertices need each other |
