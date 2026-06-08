# Lab 10 — Matching in Bipartite Graphs

## Concepts
- **Bipartite Graph** — vertices split into two sets L (left) and R (right); edges only go L→R
- **Matching M** — a subset of edges where no two edges share a vertex
- **Maximal Matching** — can't add any more edges (greedy, locally saturated)
- **Maximum Matching** — largest possible matching by edge count (globally optimal)
- **Perfect Matching** — every vertex is matched; requires |L| = |R| and |M| = |L|
- **Augmenting Path** — alternating path from a free L-vertex to a free R-vertex; flipping it grows the matching by 1

---

## Theory

**Matching intuition:** Assign L-vertices (jobs) to R-vertices (workers) such that each person does at most one job.

```
L = {L0, L1, L2, L3}    R = {R0, R1, R2, R3}
Edges:  L0→R0,R1   L1→R0,R2   L2→R1,R3   L3→R2,R3

Greedy matching (maximal): L0→R0, L1→R2, L2→R1, L3→R3   size=4 (perfect!)
```

**Augmenting path trick:**
```
Suppose matching M = {L0→R0, L1→R2}
Free L-vertex: L2 (unmatched)
L2 can go to R1 (free) → augmenting path found!
New matching: add L2→R1  → size grows to 3
```

**Key theorem (Berge):** A matching is **maximum** if and only if there is **no augmenting path**.

---

## Code Walk-through (`lab10.c`)

### Data structures
```c
int adjL[MAX_L][MAX_R];   // neighbors of each left vertex
int matchL[MAX_L];        // matchL[i] = right vertex matched to i (-1 if free)
int matchR[MAX_R];        // matchR[j] = left vertex matched to j (-1 if free)
int visited[MAX_R];       // DFS visited flag per right vertex
```

### `augment(u)` — DFS for augmenting path from left vertex u
```c
for each right neighbor v of u:
    if not visited[v]:
        if v is free (matchR[v]==-1) OR augment(matchR[v]) succeeds:
            matchL[u]=v; matchR[v]=u; return 1;  // path found, flip!
return 0;  // no augmenting path
```
The recursion `augment(matchR[v])` tries to "re-route" v's current partner.

### `maxMatching()` — iterate over all L-vertices
```c
for each u in L:
    reset visited[]
    if augment(u): result++
```

### `maximalMatching()` — greedy (first-fit)
```c
for each u in L (in order):
    pick the first free R-neighbor v → match u to v and stop
```
Greedy is fast but may miss larger matchings.

### Perfect matching check
```c
maxMatch == nL && maxMatch == nR   // every vertex on both sides is matched
```

---

## Compile & Run
```bash
gcc lab10.c -o lab10
./lab10
```

## Quick Reference
| Term | Meaning |
|------|---------|
| Maximal matching | locally saturated; no free edge can be added |
| Maximum matching | globally largest; found via augmenting paths |
| Perfect matching | \|M\| = \|L\| = \|R\|; everyone matched |
| Augmenting path | free L → (unmatched) → (matched) → … → free R |
| Time complexity | O(V · E) for simple DFS augmentation |
