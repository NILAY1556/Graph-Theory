# Lab 11 — Hall's Marriage Theorem

## Concepts
- **Hall's Condition** — for every subset S ⊆ L, the neighborhood |N(S)| ≥ |S|
- **N(S)** — all right-vertices adjacent to at least one vertex in S
- **Perfect Matching from L** — every left-vertex gets a unique right-vertex partner
- **Deficiency** — def(G) = max over all S of (|S| − |N(S)|); max matching = |L| − deficiency
- **Bitmask** — represent subsets as integers (bit i = 1 means vertex i is in the subset)

---

## Theory

**The Marriage Problem:** n boys, n girls. Each boy knows some girls. Can every boy be matched to a girl he knows?

**Hall's Theorem says:** YES, if and only if for every group S of boys, they collectively know at least |S| girls.

```
Test 1 — condition HOLDS:
  L={L0,L1,L2}, R={R0,R1,R2}
  L0→R0,R1  |  L1→R1,R2  |  L2→R0,R2

  S={L0}:     N(S)={R0,R1}   |S|=1 ≤ |N(S)|=2  ✓
  S={L0,L1}:  N(S)={R0,R1,R2} 2 ≤ 3  ✓
  S={L0,L1,L2}: N(S)={R0,R1,R2} 3 ≤ 3  ✓
  → Hall's holds → perfect matching exists

Test 2 — condition FAILS:
  L0→R0  |  L1→R0  |  L2→R1,R2
  S={L0,L1}: N(S)={R0}  |S|=2 > |N(S)|=1  ✗
  → Hall's fails → no perfect matching from L
```

**Deficiency formula:**
```
deficiency = max(|S| - |N(S)|) over all S
max matching size = |L| - deficiency
```

---

## Code Walk-through (`lab11.c`)

### `neighborhood(S_mask)` — compute N(S) as a bitmask
```c
int N = 0;
for each vertex u in S_mask:
    for each neighbor v of u:
        N |= (1 << v);   // set bit v in N
return N;
```
Each bit in `N` represents one right-vertex that is reachable from S.

### `popcount(x)` — count bits (= subset size)
```c
int c = 0;
while (x) { c += x & 1; x >>= 1; }
```

### Main check loop — iterate all 2^|L| non-empty subsets
```c
for (int S = 1; S < (1 << nL); S++) {
    int NS = neighborhood(S);
    if (popcount(NS) < popcount(S)) hallOK = 0;  // found violating subset
    int diff = popcount(S) - popcount(NS);
    if (diff > deficiency) deficiency = diff;
}
```

### Output
- Lists every subset S with its N(S), sizes, and OK/FAIL
- Prints final verdict: Hall's holds or fails
- Prints deficiency and maximum matching size

---

## Compile & Run
```bash
gcc lab11.c -o lab11
./lab11
```

## Quick Reference
| Symbol | Meaning |
|--------|---------|
| N(S) | All R-neighbors of vertices in S |
| Hall's condition | ∀ S ⊆ L: \|N(S)\| ≥ \|S\| |
| Deficiency | max(\|S\| − \|N(S)\|) |
| Max matching | \|L\| − deficiency |
| Bitmask | integer where bit i = 1 means vertex i is chosen |
| Complexity | O(2^n · n) — only practical for small n ≤ 20 |
