/*
 * ================================================================
 * LAB 15 - All-Pairs Shortest Path: Floyd-Warshall Algorithm
 * Course: Graph Theory (2301CS595)
 * ================================================================
 *
 * CONCEPTS USED:
 *   - Shortest Path: Path with minimum total edge weight between two vertices
 *   - All-Pairs Shortest Path (APSP): Shortest path between EVERY pair (u,v)
 *   - Floyd-Warshall: Dynamic programming algorithm for APSP
 *   - Intermediate Vertex: A vertex k "relays" path from i to j (i->k->j)
 *   - Negative Cycle: Cycle whose total weight is negative (makes APSP undefined)
 *   - Distance Matrix: dist[i][j] = shortest distance from i to j
 *
 * THEORY:
 *   FLOYD-WARSHALL ALGORITHM:
 *     Key idea: "Can we make path i->j shorter by going through vertex k?"
 *
 *     dist[i][j] = min(dist[i][j],   dist[i][k] + dist[k][j])
 *                        direct           via intermediate vertex k
 *
 *   ALGORITHM:
 *     1. Initialize dist[i][j] = weight(i,j) if edge exists, else INFINITY
 *        dist[i][i] = 0  (distance from vertex to itself)
 *     2. For each intermediate vertex k (from 0 to V-1):
 *        For each pair (i, j):
 *          If dist[i][k] + dist[k][j] < dist[i][j]:
 *            dist[i][j] = dist[i][k] + dist[k][j]
 *            next[i][j] = next[i][k]   (track path)
 *     3. If dist[i][i] < 0 for any i: negative cycle detected
 *
 *   TIME COMPLEXITY : O(V^3)  - three nested loops
 *   SPACE COMPLEXITY: O(V^2)  - distance matrix
 *
 *   PATH RECONSTRUCTION:
 *     Use next[i][j] matrix:
 *       next[i][j] = first vertex after i on shortest path i->j
 *     To print path i->j: print i, then follow next[i][j] until j
 *
 *   COMPARISON:
 *     Dijkstra: Single source, O((V+E)logV), no negative weights
 *     Bellman-Ford: Single source, O(VE), handles negative weights
 *     Floyd-Warshall: All pairs, O(V^3), handles negative weights (no neg cycles)
 *
 * COMPILE:  gcc lab15.c -o lab15
 * RUN:      ./lab15
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_V 8
#define INF   99999   /* large number representing "no direct path" */

int V, E;
int dist[MAX_V][MAX_V];   /* distance matrix */
int next_v[MAX_V][MAX_V]; /* next vertex on shortest path */

/* Initialize dist matrix from edge list */
void init(int edges[][3], int numEdges) {
    /* Start: dist[i][j] = INF for all, 0 for diagonal */
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) {
            dist[i][j]   = (i == j) ? 0 : INF;
            next_v[i][j] = (i == j) ? i : -1;
        }

    /* Set edge weights */
    for (int e = 0; e < numEdges; e++) {
        int u = edges[e][0], v = edges[e][1], w = edges[e][2];
        dist[u][v] = w;
        next_v[u][v] = v;
        /* For undirected graph, add both directions */
        dist[v][u] = w;
        next_v[v][u] = u;
    }
}

/* Floyd-Warshall APSP */
void floydWarshall() {
    /* Try every vertex k as an intermediate relay */
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                /* Skip if path through k is via infinity */
                if (dist[i][k] == INF || dist[k][j] == INF) continue;
                int via_k = dist[i][k] + dist[k][j];
                if (via_k < dist[i][j]) {
                    dist[i][j]   = via_k;
                    next_v[i][j] = next_v[i][k];  /* go through k first */
                }
            }
        }
    }
}

/* Print the shortest path from src to dst */
void printPath(int src, int dst) {
    if (dist[src][dst] == INF) {
        printf("No path");
        return;
    }
    printf("%d", src);
    int cur = src;
    while (cur != dst) {
        cur = next_v[cur][dst];
        printf(" -> %d", cur);
    }
}

void printDistMatrix() {
    printf("\nShortest Distance Matrix:\n     ");
    for (int j = 0; j < V; j++) printf("%6d", j);
    printf("\n   +");
    for (int j = 0; j < V; j++) printf("------");
    printf("\n");
    for (int i = 0; i < V; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) printf("   INF");
            else printf("%6d", dist[i][j]);
        }
        printf("\n");
    }
}

int main() {
    V = 5;
    /*
     * Weighted undirected graph:
     *     4       2
     * 0 ----- 1 ----- 2
     * |       |       |
     * 8       3       1
     * |       |       |
     * 3 ----- 4 ----- (2)
     *     5
     * Edges: (u, v, weight)
     */
    int edges[][3] = {
        {0, 1, 4},
        {0, 3, 8},
        {1, 2, 2},
        {1, 4, 3},
        {2, 4, 1},
        {3, 4, 5}
    };
    int numEdges = 6;

    init(edges, numEdges);

    printf("=== All-Pairs Shortest Path: Floyd-Warshall ===\n");
    printf("Edges (u, v, weight):\n");
    for (int i = 0; i < numEdges; i++)
        printf("  %d -- %d  (weight=%d)\n", edges[i][0], edges[i][1], edges[i][2]);

    printf("\nInitial distance matrix (before Floyd-Warshall):\n");
    printf("(INF means no direct edge)\n");
    printDistMatrix();

    floydWarshall();

    printf("\nAfter Floyd-Warshall:");
    printDistMatrix();

    /* Check negative cycle */
    int negCycle = 0;
    for (int i = 0; i < V; i++)
        if (dist[i][i] < 0) { negCycle = 1; break; }
    printf("\nNegative Cycle: %s\n", negCycle ? "DETECTED (result unreliable)" : "None detected");

    /* Print some specific paths */
    printf("\nShortest Paths (with routes):\n");
    int queries[][2] = {{0,2},{0,4},{3,2},{1,3}};
    int nq = 4;
    for (int i = 0; i < nq; i++) {
        int s = queries[i][0], t = queries[i][1];
        printf("  %d -> %d : distance=%d, path=", s, t, dist[s][t]);
        printPath(s, t);
        printf("\n");
    }

    return 0;
}
