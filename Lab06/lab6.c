/*
 * ================================================================
 * LAB 6 - Articulation Points (Cut Vertices)
 * Course: Graph Theory (2301CS595)
 * ================================================================
 *
 * CONCEPTS USED:
 *   - Articulation Point (Cut Vertex): A vertex whose removal disconnects the graph
 *   - DFS Tree: Tree formed by DFS traversal
 *   - Discovery Time: When a vertex is first visited in DFS
 *   - Low Value: Minimum discovery time reachable from a subtree
 *   - Back Edge: Edge in DFS going to an ancestor (not parent)
 *
 * THEORY:
 *   A vertex u is an ARTICULATION POINT if:
 *   Case 1: u is ROOT of DFS tree AND has >= 2 children
 *   Case 2: u is NOT root AND has a child v where low[v] >= disc[u]
 *           (meaning: subtree of v can NOT reach any ancestor of u)
 *
 *   disc[u] = discovery time of u in DFS
 *   low[u]  = min(disc[u], disc of ancestors reachable via back edges)
 *
 *   WHY ARTICULATION POINTS MATTER:
 *     - Identify single points of failure in a network
 *     - If you remove an articulation point, the graph splits
 *     - Important in network design (routers, bridges)
 *
 *   ALGORITHM (Tarjan's):
 *     1. Do DFS, assign disc[] and low[] values
 *     2. For each vertex u with child v:
 *        - Update low[u] = min(low[u], low[v])
 *        - Check articulation point conditions above
 *
 * COMPILE:  gcc lab6.c -o lab6
 * RUN:      ./lab6
 */

#include <stdio.h>
#include <string.h>

#define MAX_V 20

int adj[MAX_V][MAX_V], adjSize[MAX_V];
int disc[MAX_V];   /* discovery time */
int low[MAX_V];    /* minimum reachable discovery time */
int visited[MAX_V];
int isAP[MAX_V];   /* isAP[v]=1 means v is articulation point */
int timer_val = 0;

void addEdge(int u, int v) {
    adj[u][adjSize[u]++] = v;
    adj[v][adjSize[v]++] = u;
}

/* DFS to find articulation points */
void dfs(int u, int parent) {
    visited[u] = 1;
    disc[u] = low[u] = timer_val++;
    int children = 0;

    for (int i = 0; i < adjSize[u]; i++) {
        int v = adj[u][i];

        if (!visited[v]) {
            children++;
            dfs(v, u);

            /* Update low[u] through child v */
            if (low[v] < low[u]) low[u] = low[v];

            /* Case 1: u is root with 2+ children */
            if (parent == -1 && children > 1)
                isAP[u] = 1;

            /* Case 2: u is not root, child v cannot reach above u */
            if (parent != -1 && low[v] >= disc[u])
                isAP[u] = 1;

        } else if (v != parent) {
            /* Back edge: update low[u] */
            if (disc[v] < low[u]) low[u] = disc[v];
        }
    }
}

int main() {
    int V = 7;
    memset(adjSize, 0, sizeof(adjSize));
    memset(visited, 0, sizeof(visited));
    memset(isAP, 0, sizeof(isAP));

    /*
     * Graph:
     *   0 -- 1 -- 3 -- 4
     *   |    |
     *   2    5 -- 6
     *   |
     * (0,1,2 form a cycle; 1,5,6 chain; 3,4 chain)
     * Articulation points: 1, 3, 5
     */
    addEdge(0, 1); addEdge(0, 2); addEdge(1, 2);
    addEdge(1, 3); addEdge(3, 4);
    addEdge(1, 5); addEdge(5, 6);

    printf("=== Articulation Points (Cut Vertices) ===\n");
    printf("Graph edges: 0-1, 0-2, 1-2, 1-3, 3-4, 1-5, 5-6\n\n");

    /* Run DFS for all components */
    for (int i = 0; i < V; i++)
        if (!visited[i]) dfs(i, -1);

    printf("DFS discovery and low values:\n");
    printf("  %-8s %-10s %-10s %-12s\n", "Vertex", "disc[]", "low[]", "Articuln.Pt?");
    for (int i = 0; i < V; i++)
        printf("  %-8d %-10d %-10d %-12s\n",
               i, disc[i], low[i], isAP[i] ? "YES" : "no");

    printf("\nArticulation Points: ");
    int found = 0;
    for (int i = 0; i < V; i++) {
        if (isAP[i]) { printf("%d ", i); found = 1; }
    }
    if (!found) printf("NONE");
    printf("\n");

    printf("\nMeaning: Removing any of these vertices disconnects the graph.\n");

    return 0;
}
