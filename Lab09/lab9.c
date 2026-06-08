/*
 * ================================================================
 * LAB 9 - Total Dominating Sets (Focused)
 * Course: Graph Theory (2301CS595)
 * ================================================================
 *
 * CONCEPTS USED:
 *   - Total Dominating Set (TDS): A vertex subset S where EVERY vertex
 *     in V (including vertices IN S) has ≥1 neighbor in S
 *   - Total Domination Number γt(G): Minimum size of any TDS
 *   - Neighborhood N(v): Set of all neighbors of vertex v
 *   - Open Neighborhood: N(v) does NOT include v itself
 *
 * THEORY:
 *   TOTAL DOMINATING SET S ⊆ V:
 *     Condition: ∀v ∈ V,  N(v) ∩ S ≠ ∅
 *     Translation: "Every vertex must have at least one NEIGHBOR in S"
 *
 *   Key difference from regular dominating set:
 *     - Regular DS: Only non-S vertices need a neighbor in S
 *     - Total DS: ALL vertices (even in S) need a neighbor in S
 *     → So no isolated vertex in S is allowed!
 *
 *   γt(G) ≥ 2  always (since each vertex in S needs a neighbor in S)
 *
 *   PROPERTIES:
 *     γ(G) ≤ γt(G) ≤ 2·γ(G)
 *     For a path Pn: γt(Pn) = ⌈n/2⌉
 *     For a cycle Cn: γt(Cn) = ⌈n/2⌉
 *
 *   GREEDY HEURISTIC:
 *     1. Find the vertex with the most neighbors (highest degree)
 *     2. Add it and its best-uncovered neighbor to S
 *     3. Repeat until all vertices are dominated
 *     (Not always optimal, but gives a good approximation)
 *
 * COMPILE:  gcc lab9.c -o lab9
 * RUN:      ./lab9
 */

#include <stdio.h>
#include <string.h>

#define MAX_V 15

int V, E;
int adj[MAX_V][MAX_V], adjSize[MAX_V];
int degree[MAX_V];

void addEdge(int u, int v) {
    adj[u][adjSize[u]++] = v;
    adj[v][adjSize[v]++] = u;
    degree[u]++; degree[v]++;
}

int popcount(int mask) {
    int c = 0; while (mask) { c += mask & 1; mask >>= 1; } return c;
}

/* Check if mask is a total dominating set */
int isTDS(int mask) {
    if (!mask) return 0;
    for (int v = 0; v < V; v++) {
        int hasNeighborInS = 0;
        for (int i = 0; i < adjSize[v]; i++)
            if (mask & (1 << adj[v][i])) { hasNeighborInS = 1; break; }
        if (!hasNeighborInS) return 0;
    }
    return 1;
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

/* Check coverage: how many vertices are dominated by set 'mask' */
int coverage(int mask) {
    int covered = 0;
    for (int v = 0; v < V; v++) {
        for (int i = 0; i < adjSize[v]; i++)
            if (mask & (1 << adj[v][i])) { covered++; break; }
    }
    return covered;
}

int main() {
    V = 7; E = 8;
    memset(adjSize, 0, sizeof(adjSize));
    memset(degree, 0, sizeof(degree));

    /*
     * Graph:
     *   0 -- 1 -- 2 -- 3
     *        |         |
     *        4 -- 5 -- 6
     */
    addEdge(0,1); addEdge(1,2); addEdge(2,3);
    addEdge(1,4); addEdge(4,5); addEdge(5,6);
    addEdge(3,6); addEdge(2,5);

    printf("=== Total Dominating Sets (Focused) ===\n");
    printf("Graph edges: 0-1, 1-2, 2-3, 1-4, 4-5, 5-6, 3-6, 2-5\n\n");

    printf("Vertex degrees:\n");
    for (int i = 0; i < V; i++)
        printf("  Vertex %d: degree = %d\n", i, degree[i]);

    /* Brute force: find minimum TDS */
    int minSize = V + 1, bestMask = -1;
    int total = 1 << V;
    for (int mask = 1; mask < total; mask++) {
        if (isTDS(mask) && popcount(mask) < minSize) {
            minSize = popcount(mask);
            bestMask = mask;
        }
    }

    printf("\nTotal Domination Number γt(G) = %d\n", minSize);
    printf("One minimum total dominating set: ");
    printSet(bestMask); printf("\n");

    printf("\nAll minimum total dominating sets:\n");
    for (int mask = 1; mask < total; mask++) {
        if (isTDS(mask) && popcount(mask) == minSize) {
            printf("  "); printSet(mask); printf("\n");
        }
    }

    /* Show why it works */
    printf("\nVerification of one TDS ");
    printSet(bestMask); printf(":\n");
    for (int v = 0; v < V; v++) {
        printf("  Vertex %d: neighbors in S = {", v);
        int first = 1;
        for (int i = 0; i < adjSize[v]; i++) {
            if (bestMask & (1 << adj[v][i])) {
                if (!first) printf(", ");
                printf("%d", adj[v][i]);
                first = 0;
            }
        }
        printf("} -> %s\n", first ? "FAIL" : "OK");
    }

    return 0;
}
