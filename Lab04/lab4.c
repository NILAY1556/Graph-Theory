/*
 * ================================================================
 * LAB 4 - Tree Operations
 * Course: Graph Theory (2301CS595)
 * ================================================================
 *
 * CONCEPTS USED:
 *   - Tree: A connected graph with NO cycles, V vertices, V-1 edges
 *   - Pendent Vertex (Leaf): A vertex with degree 1
 *   - Distance: Shortest path length between two vertices (BFS)
 *   - Eccentricity: Max distance from a vertex to any other vertex
 *   - Center: Vertex with minimum eccentricity
 *   - Radius: Minimum eccentricity in the graph
 *   - Diameter: Maximum eccentricity = longest shortest path
 *
 * THEORY:
 *   A TREE is the simplest connected structure:
 *     - Connected (path exists between every pair)
 *     - Acyclic (no loops/cycles)
 *     - |E| = |V| - 1  (always!)
 *
 *   PENDENT VERTEX: degree = 1  (a leaf of the tree)
 *
 *   DISTANCE d(u,v): shortest path from u to v
 *     In a tree: there is exactly ONE path between any two vertices
 *
 *   ECCENTRICITY e(v) = max { d(v, u) : u is any vertex }
 *     "How far is the FARTHEST vertex from v?"
 *
 *   CENTER: vertex with smallest eccentricity
 *     A tree has 1 or 2 center vertices (always!)
 *
 *   RADIUS    r(G) = min { e(v) }
 *   DIAMETER  d(G) = max { e(v) }
 *
 *   HOW TO VERIFY A TREE:
 *     1. Graph must be CONNECTED (BFS/DFS visits all vertices)
 *     2. Number of edges must be exactly V-1
 *
 * COMPILE:  gcc lab4.c -o lab4
 * RUN:      ./lab4
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_V 20
#define INF   99999

int V, E;
int adj[MAX_V][MAX_V];
int adjSize[MAX_V];
int degree[MAX_V];

void addEdge(int u, int v) {
    adj[u][adjSize[u]++] = v;
    adj[v][adjSize[v]++] = u;
    degree[u]++;
    degree[v]++;
}

/* BFS from src: returns dist[] array (distance from src to all vertices) */
void bfsDistance(int src, int dist[]) {
    int visited[MAX_V] = {0};
    int queue[MAX_V];
    int front = 0, rear = 0;
    for (int i = 0; i < V; i++) dist[i] = INF;
    dist[src] = 0;
    visited[src] = 1;
    queue[rear++] = src;
    while (front < rear) {
        int u = queue[front++];
        for (int i = 0; i < adjSize[u]; i++) {
            int v = adj[u][i];
            if (!visited[v]) {
                visited[v] = 1;
                dist[v] = dist[u] + 1;
                queue[rear++] = v;
            }
        }
    }
}

/* Check if graph is connected (all vertices reachable from 0) */
int isConnected() {
    int dist[MAX_V];
    bfsDistance(0, dist);
    for (int i = 0; i < V; i++)
        if (dist[i] == INF) return 0;
    return 1;
}

int main() {
    V = 7; E = 6;
    memset(adjSize, 0, sizeof(adjSize));
    memset(degree, 0, sizeof(degree));

    /*
     * Tree:
     *       0
     *      / \
     *     1   2
     *    / \   \
     *   3   4   5
     *            \
     *             6
     */
    addEdge(0, 1); addEdge(0, 2);
    addEdge(1, 3); addEdge(1, 4);
    addEdge(2, 5); addEdge(5, 6);

    printf("=== Tree Operations ===\n");

    /* 1. Verify it is a tree */
    printf("\n1. Is it a Tree?\n");
    printf("   Vertices=%d, Edges=%d, V-1=%d\n", V, E, V-1);
    if (isConnected() && E == V - 1)
        printf("   YES - Connected and |E| = |V|-1\n");
    else
        printf("   NO\n");

    /* 2. Pendent vertices (degree=1) */
    printf("\n2. Pendent Vertices (degree=1): ");
    for (int i = 0; i < V; i++)
        if (degree[i] == 1) printf("%d ", i);
    printf("\n");

    /* 3. Degrees */
    printf("\n3. Degree of each vertex:\n");
    for (int i = 0; i < V; i++)
        printf("   Vertex %d: degree = %d\n", i, degree[i]);

    /* 4. Distance matrix */
    printf("\n4. Distance between all pairs:\n   ");
    for (int j = 0; j < V; j++) printf("%4d", j);
    printf("\n");
    int ecc[MAX_V];
    for (int i = 0; i < V; i++) {
        int dist[MAX_V];
        bfsDistance(i, dist);
        printf("%2d ", i);
        int maxDist = 0;
        for (int j = 0; j < V; j++) {
            printf("%4d", dist[j]);
            if (dist[j] != INF && dist[j] > maxDist) maxDist = dist[j];
        }
        ecc[i] = maxDist;
        printf("  | ecc=%d\n", ecc[i]);
    }

    /* 5. Eccentricity, Center, Radius, Diameter */
    printf("\n5. Eccentricity of each vertex:\n");
    int radius = INF, diameter = 0, center = -1;
    for (int i = 0; i < V; i++) {
        printf("   e(%d) = %d\n", i, ecc[i]);
        if (ecc[i] < radius) { radius = ecc[i]; center = i; }
        if (ecc[i] > diameter) diameter = ecc[i];
    }
    printf("\n   Radius   = %d\n", radius);
    printf("   Diameter = %d\n", diameter);
    printf("   Center vertices (e(v) == radius):");
    for (int i = 0; i < V; i++)
        if (ecc[i] == radius) printf(" %d", i);
    printf("\n");

    return 0;
}
