/*
 * ================================================================
 * LAB 10 - Matching in Bipartite Graphs
 * Course: Graph Theory (2301CS595)
 * ================================================================
 *
 * CONCEPTS USED:
 *   - Bipartite Graph: Vertices split into 2 sets (L, R); edges only between L and R
 *   - Matching: A set of edges with NO shared vertices
 *   - Maximal Matching: Can't add any more edges (no augmenting path of length 1)
 *   - Maximum Matching: Largest possible matching (by edge count)
 *   - Perfect Matching: Every vertex is matched (possible only if |L| = |R|)
 *   - Augmenting Path: Path from unmatched L to unmatched R via alternating edges
 *
 * THEORY:
 *   BIPARTITE GRAPH G = (L ∪ R, E):
 *     L = "left" vertices, R = "right" vertices
 *     All edges go from L to R (no L-L or R-R edges)
 *
 *   MATCHING M ⊆ E: No two edges in M share a vertex
 *   Matched vertex: endpoint of some edge in M
 *   Unmatched (free) vertex: not in any edge of M
 *
 *   MAXIMUM MATCHING (Hungarian / Hopcroft-Karp approach):
 *     Use AUGMENTING PATHS:
 *     - Alternating path: edges alternately NOT in M, IN M, NOT in M...
 *     - Augmenting path: starts and ends at unmatched vertices
 *     - If we "flip" the matching along augmenting path: matching grows by 1!
 *     - No augmenting path exists => matching is maximum
 *
 *   ALGORITHM (Simple DFS augmentation):
 *     For each unmatched vertex in L:
 *       Try to find augmenting path using DFS
 *       If found: flip the path (grow matching by 1)
 *
 *   PERFECT MATCHING: |M| = |L| = |R|
 *   MAXIMAL != MAXIMUM: maximal is locally optimal, maximum is globally optimal
 *
 * COMPILE:  gcc lab10.c -o lab10
 * RUN:      ./lab10
 */

#include <stdio.h>
#include <string.h>

#define MAX_L 10   /* max left vertices */
#define MAX_R 10   /* max right vertices */

int nL, nR;
int adjL[MAX_L][MAX_R];   /* neighbors of left vertex i */
int adjLSize[MAX_L];
int matchL[MAX_L];        /* matchL[i] = right vertex matched to left i (-1 if free) */
int matchR[MAX_R];        /* matchR[j] = left vertex matched to right j (-1 if free) */
int visited[MAX_R];       /* visited during DFS for augmenting path */

/* Add edge from left vertex u to right vertex v */
void addEdge(int u, int v) {
    adjL[u][adjLSize[u]++] = v;
}

/* DFS to find augmenting path from left vertex u */
int augment(int u) {
    for (int i = 0; i < adjLSize[u]; i++) {
        int v = adjL[u][i];
        if (visited[v]) continue;
        visited[v] = 1;
        /* v is free OR we can re-match v's current partner */
        if (matchR[v] == -1 || augment(matchR[v])) {
            matchL[u] = v;
            matchR[v] = u;
            return 1;  /* augmenting path found */
        }
    }
    return 0;  /* no augmenting path from u */
}

/* Find maximum matching, return matching size */
int maxMatching() {
    memset(matchL, -1, sizeof(matchL));
    memset(matchR, -1, sizeof(matchR));
    int result = 0;
    for (int u = 0; u < nL; u++) {
        memset(visited, 0, sizeof(visited));
        if (augment(u)) result++;
    }
    return result;
}

/* Greedy maximal matching (not necessarily maximum) */
int maximalMatching(int matchedL[], int matchedR[]) {
    memset(matchedL, -1, MAX_L * sizeof(int));
    memset(matchedR, -1, MAX_R * sizeof(int));
    int count = 0;
    for (int u = 0; u < nL; u++) {
        if (matchedL[u] != -1) continue;
        for (int i = 0; i < adjLSize[u]; i++) {
            int v = adjL[u][i];
            if (matchedR[v] == -1) {
                matchedL[u] = v; matchedR[v] = u; count++; break;
            }
        }
    }
    return count;
}

int main() {
    nL = 4; nR = 4;
    memset(adjLSize, 0, sizeof(adjLSize));

    /*
     * Bipartite graph:
     * L: {0,1,2,3}  R: {0,1,2,3}
     * Edges:
     *   L0 -> R0, R1
     *   L1 -> R0, R2
     *   L2 -> R1, R3
     *   L3 -> R2, R3
     */
    addEdge(0,0); addEdge(0,1);
    addEdge(1,0); addEdge(1,2);
    addEdge(2,1); addEdge(2,3);
    addEdge(3,2); addEdge(3,3);

    printf("=== Matching in Bipartite Graph ===\n");
    printf("L = {L0,L1,L2,L3}, R = {R0,R1,R2,R3}\n");
    printf("Adjacency (L->R):\n");
    for (int u = 0; u < nL; u++) {
        printf("  L%d -> ", u);
        for (int i = 0; i < adjLSize[u]; i++) printf("R%d ", adjL[u][i]);
        printf("\n");
    }

    /* Greedy maximal matching */
    int mL[MAX_L], mR[MAX_R];
    int maximal = maximalMatching(mL, mR);
    printf("\n1. Maximal Matching (greedy, size=%d):\n", maximal);
    for (int u = 0; u < nL; u++)
        if (mL[u] != -1) printf("   L%d -- R%d\n", u, mL[u]);

    /* Maximum matching */
    int maxMatch = maxMatching();
    printf("\n2. Maximum Matching (size=%d):\n", maxMatch);
    for (int u = 0; u < nL; u++)
        if (matchL[u] != -1) printf("   L%d -- R%d\n", u, matchL[u]);

    printf("\n3. Is it Perfect Matching? %s\n",
           maxMatch == nL && maxMatch == nR ? "YES (every vertex matched)" : "NO");

    return 0;
}
