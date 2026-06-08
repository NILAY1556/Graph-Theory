/*
 * ================================================================
 * LAB 8 - Dominating Sets
 * Course: Graph Theory (2301CS595)
 * ================================================================
 *
 * CONCEPTS USED:
 *   - Dominating Set: A subset S of vertices such that every vertex
 *     NOT in S has at least one neighbor IN S
 *   - Domination Number γ(G): Size of the smallest dominating set
 *   - Total Dominating Set: Every vertex (including those IN S)
 *     must have at least one neighbor IN S
 *   - Total Domination Number γt(G): Size of smallest total dom. set
 *
 * THEORY:
 *   DOMINATING SET S:
 *     For every vertex v NOT in S:
 *       v must be adjacent to at least one vertex in S
 *     (S "covers" or "dominates" all other vertices)
 *
 *   DOMINATION NUMBER γ(G) = minimum size of a dominating set
 *
 *   EXAMPLE:
 *     Graph: 0-1, 1-2, 2-3, 3-4
 *     S = {1, 3} is a dominating set:
 *       0: neighbor 1 is in S ✓
 *       2: neighbors 1,3 in S ✓
 *       4: neighbor 3 in S ✓
 *       1,3 are IN S ✓
 *     So γ(G) ≤ 2
 *
 *   TOTAL DOMINATING SET S:
 *     EVERY vertex (even those IN S) must have a neighbor in S
 *     (no vertex can be "isolated" within S)
 *
 *   APPROACH (Brute Force for small graphs):
 *     Try all 2^V subsets of vertices
 *     Check each subset: is it a dominating set?
 *     Find the smallest valid subset
 *
 * COMPILE:  gcc lab8.c -o lab8
 * RUN:      ./lab8
 */

#include <stdio.h>
#include <string.h>

#define MAX_V 15

int V, E;
int adj[MAX_V][MAX_V], adjSize[MAX_V];

void addEdge(int u, int v) {
    adj[u][adjSize[u]++] = v;
    adj[v][adjSize[v]++] = u;
}

/* Check if subset (bitmask) is a dominating set */
int isDominating(int mask) {
    for (int v = 0; v < V; v++) {
        if (mask & (1 << v)) continue;  /* v is IN S, skip */
        /* v is NOT in S: must have a neighbor in S */
        int dominated = 0;
        for (int i = 0; i < adjSize[v]; i++) {
            if (mask & (1 << adj[v][i])) { dominated = 1; break; }
        }
        if (!dominated) return 0;
    }
    return 1;
}

/* Check if subset (bitmask) is a TOTAL dominating set */
int isTotalDominating(int mask) {
    if (mask == 0) return 0;
    for (int v = 0; v < V; v++) {
        /* EVERY vertex must have a neighbor in S */
        int dominated = 0;
        for (int i = 0; i < adjSize[v]; i++) {
            if (mask & (1 << adj[v][i])) { dominated = 1; break; }
        }
        if (!dominated) return 0;
    }
    return 1;
}

/* Count number of 1-bits in mask */
int popcount(int mask) {
    int c = 0;
    while (mask) { c += mask & 1; mask >>= 1; }
    return c;
}

void printSet(int mask) {
    printf("{");
    int first = 1;
    for (int i = 0; i < V; i++) {
        if (mask & (1 << i)) {
            if (!first) printf(", ");
            printf("%d", i);
            first = 0;
        }
    }
    printf("}");
}

int main() {
    V = 6; E = 6;
    memset(adjSize, 0, sizeof(adjSize));
    /*
     * Graph (cycle + one extra):
     *   0 -- 1 -- 2
     *   |         |
     *   5 -- 4 -- 3
     * (hexagon / 6-cycle)
     */
    addEdge(0,1); addEdge(1,2); addEdge(2,3);
    addEdge(3,4); addEdge(4,5); addEdge(5,0);

    printf("=== Dominating Sets ===\n");
    printf("Graph: 6-cycle (0-1-2-3-4-5-0)\n\n");

    int minDom = V + 1, minTot = V + 1;
    int bestDom = -1, bestTot = -1;
    int total = 1 << V;

    for (int mask = 1; mask < total; mask++) {
        int sz = popcount(mask);
        if (isDominating(mask) && sz < minDom) {
            minDom = sz; bestDom = mask;
        }
        if (isTotalDominating(mask) && sz < minTot) {
            minTot = sz; bestTot = mask;
        }
    }

    printf("1. All Dominating Sets of minimum size:\n");
    printf("   Domination Number γ(G) = %d\n", minDom);
    printf("   One minimum dominating set: ");
    printSet(bestDom); printf("\n");
    printf("   All minimum dominating sets:\n");
    for (int mask = 1; mask < total; mask++)
        if (isDominating(mask) && popcount(mask) == minDom) {
            printf("     "); printSet(mask); printf("\n");
        }

    printf("\n2. Total Dominating Sets:\n");
    printf("   Total Domination Number γt(G) = %d\n", minTot);
    printf("   One minimum total dominating set: ");
    printSet(bestTot); printf("\n");
    printf("   (Every vertex must have a neighbor in this set)\n");

    return 0;
}
