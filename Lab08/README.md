# Lab 8 — Dominating Sets

## Concepts
- **Dominating Set S** — a subset of vertices such that every vertex NOT in S has at least one neighbor in S
- **Domination Number γ(G)** — size of the smallest dominating set
- **Total Dominating Set** — every vertex (even those IN S) must have a neighbor in S
- **Total Domination Number γt(G)** — size of the smallest total dominating set
- **Bitmask enumeration** — represent subsets as integers; bit i = 1 means vertex i is in the set

---

## Theory

**Dominating Set:** S "guards" the whole graph. Every vertex outside S must be adjacent to someone inside S.

```
Graph: 6-cycle  0 - 1 - 2 - 3 - 4 - 5 - 0

S = {0, 2, 4}:
  Vertex 1: neighbors 0 and 2, both in S ✓
  Vertex 3: neighbors 2 and 4, both in S ✓
  Vertex 5: neighbors 4 and 0, both in S ✓
  → S is a dominating set, γ ≤ 3
```

**Total Dominating Set:** Even vertices IN S must have a neighbor also in S.

```
S = {0, 1}: regular dominating set, but 0 and 1 only cover each other.
All non-S vertices must have a neighbor in S:
  2: neighbor 1 in S ✓,  5: neighbor 0 in S ✓,  etc.
Every vertex in S has a neighbor in S: 0↔1 ✓
→ {0, 1} is a total dominating set if all others are also covered.
```

**Key fact:** γ(G) ≤ γt(G) ≤ 2·γ(G)

---

## Code Walk-through (`lab8.c`)

### Bitmask trick — represent a subset as one integer
```c
int mask = 0b001011; // means vertices 0, 1, 3 are in the set
// Check if vertex v is in the set:
if (mask & (1 << v)) { /* v is in set */ }
```

### `isDominating(mask)` — verify a dominating set
```c
for each vertex v NOT in mask:
    check if any neighbor of v IS in mask
    if none found → return 0  (not dominating)
return 1
```

### `isTotalDominating(mask)` — verify a total dominating set
```c
for EVERY vertex v (including those in mask):
    check if any neighbor of v IS in mask
    if none → return 0
return 1
```

### Main loop — brute-force over all 2^V subsets
```c
for (int mask = 1; mask < (1 << V); mask++) {
    if (isDominating(mask) && popcount(mask) < minDom)
        minDom = popcount(mask);  // track smallest
}
```

### `popcount(mask)` — count set bits = size of subset
```c
int c = 0;
while (mask) { c += mask & 1; mask >>= 1; }
```

---

## Compile & Run
```bash
gcc lab8.c -o lab8
./lab8
```

## Quick Reference
| Term | Condition |
|------|-----------|
| Dominating set | every non-S vertex has ≥1 neighbor in S |
| Total dominating set | every vertex (in or out of S) has ≥1 neighbor in S |
| γ(G) | min size of dominating set |
| γt(G) | min size of total dominating set; always ≥ 2 |
| Brute force | works for V ≤ 20 (2^V subsets) |
