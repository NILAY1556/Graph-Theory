/*
 * ================================================================
 * LAB 11 - Hall's Marriage Theorem
 * Course: Graph Theory (2301CS595)
 * ================================================================
 *
 * CONCEPTS USED:
 *   - Hall's Condition: For every subset S ⊆ L, |N(S)| ≥ |S|
 *   - N(S): Neighborhood of S = all right-vertices adjacent to some vertex in S
 *   - Perfect Matching from L to R: Exists IF AND ONLY IF Hall's condition holds
 *   - Hall's Theorem (Marriage Theorem): A bipartite graph G=(L∪R,E) has a
 *     matching saturating all of L iff for every S⊆L: |N(S)| ≥ |S|
 *
 * THEORY:
 *   HALL'S MARRIAGE THEOREM:
 *     Imagine L = "boys", R = "girls"
 *     Each boy knows some girls (edges in bipartite graph)
 *     A "perfect matching from L" = every boy gets paired with a girl he knows
 *
 *     Hall's Condition: For every group S of boys,
 *       the number of girls they collectively know ≥ number of boys in S
 *       i.e., |N(S)| ≥ |S|  for all S ⊆ L
 *
 *   If even ONE subset S violates this: |N(S)| < |S|
 *     → No matching from L exists
 *     → Hall's condition FAILS
 *
 *   HOW TO CHECK (brute force for small graphs):
 *     For all 2^|L| subsets S of L:
 *       Compute N(S) = union of all neighbors of vertices in S
 *       Check if |N(S)| ≥ |S|
 *       If any subset fails → Hall's condition is violated
 *
 *   DEFICIENCY: def(G) = max over all S of (|S| - |N(S)|)
 *     Max matching size = |L| - deficiency
 *
 * COMPILE:  gcc lab11.c -o lab11
 * RUN:      ./lab11
 */

#include <stdio.h>
#include <string.h>

#define MAX_L 10
#define MAX_R 10

int nL, nR;
int adjL[MAX_L][MAX_R], adjLSize[MAX_L];

void addEdge(int u, int v) {
    adjL[u][adjLSize[u]++] = v;
}

/* Compute N(S) as a bitmask over right vertices */
int neighborhood(int S_mask) {
    int N = 0;
    for (int u = 0; u < nL; u++) {
        if (!(S_mask & (1 << u))) continue;
        for (int i = 0; i < adjLSize[u]; i++)
            N |= (1 << adjL[u][i]);
    }
    return N;
}

int popcount(int x) {
    int c = 0; while (x) { c += x & 1; x >>= 1; } return c;
}

void printSubset(int mask, char side) {
    printf("{");
    int first = 1;
    for (int i = 0; i < (side=='L' ? nL : nR); i++) {
        if (mask & (1 << i)) {
            if (!first) printf(", ");
            printf("%c%d", side, i);
            first = 0;
        }
    }
    printf("}");
}

int main() {
    printf("=== Hall's Marriage Theorem ===\n\n");

    /* --- Test Case 1: Hall's condition HOLDS --- */
    printf("--- Test 1: Hall's condition HOLDS ---\n");
    nL = 3; nR = 3;
    memset(adjLSize, 0, sizeof(adjLSize));
    addEdge(0,0); addEdge(0,1);
    addEdge(1,1); addEdge(1,2);
    addEdge(2,0); addEdge(2,2);

    printf("L = {L0,L1,L2}, R = {R0,R1,R2}\n");
    printf("Edges: L0->R0,R1 | L1->R1,R2 | L2->R0,R2\n\n");

    int hallOK = 1, deficiency = 0;
    printf("Checking all subsets S of L:\n");
    for (int S = 1; S < (1 << nL); S++) {
        int NS = neighborhood(S);
        int sS = popcount(S), sNS = popcount(NS);
        int diff = sS - sNS;
        if (diff > deficiency) deficiency = diff;
        printf("  S="); printSubset(S,'L');
        printf(", N(S)="); printSubset(NS,'R');
        printf(", |S|=%d, |N(S)|=%d -> %s\n",
               sS, sNS, sNS >= sS ? "OK" : "FAIL!");
        if (sNS < sS) hallOK = 0;
    }
    printf("\nHall's condition: %s\n", hallOK ? "HOLDS -> Perfect matching exists" : "FAILS -> No perfect matching");
    printf("Deficiency = %d, Max matching size = %d\n\n", deficiency, nL - deficiency);

    /* --- Test Case 2: Hall's condition FAILS --- */
    printf("--- Test 2: Hall's condition FAILS ---\n");
    nL = 3; nR = 3;
    memset(adjLSize, 0, sizeof(adjLSize));
    addEdge(0,0);
    addEdge(1,0);
    addEdge(2,1); addEdge(2,2);

    printf("L = {L0,L1,L2}, R = {R0,R1,R2}\n");
    printf("Edges: L0->R0 | L1->R0 | L2->R1,R2\n\n");

    hallOK = 1; deficiency = 0;
    printf("Checking all subsets S of L:\n");
    for (int S = 1; S < (1 << nL); S++) {
        int NS = neighborhood(S);
        int sS = popcount(S), sNS = popcount(NS);
        int diff = sS - sNS;
        if (diff > deficiency) deficiency = diff;
        printf("  S="); printSubset(S,'L');
        printf(", N(S)="); printSubset(NS,'R');
        printf(", |S|=%d, |N(S)|=%d -> %s\n",
               sS, sNS, sNS >= sS ? "OK" : "FAIL!");
        if (sNS < sS) hallOK = 0;
    }
    printf("\nHall's condition: %s\n", hallOK ? "HOLDS" : "FAILS -> No perfect matching from L");
    printf("Deficiency = %d, Max matching size = %d\n", deficiency, nL - deficiency);

    return 0;
}
