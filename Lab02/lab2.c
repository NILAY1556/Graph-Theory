/*
 * ================================================================
 * LAB 2 - BFS: Breadth First Search
 * Course: Graph Theory (2301CS595)
 * ================================================================
 *
 * CONCEPTS USED:
 *   - BFS (Breadth First Search): Explore graph level by level
 *   - Queue: FIFO (First In First Out) data structure
 *   - Visited array: Track which vertices are already explored
 *
 * THEORY:
 *   BFS starts from a source vertex and explores all neighbors
 *   before moving to the next level.
 *
 *   Think of it like a ripple in water:
 *     Level 0: Start vertex
 *     Level 1: All direct neighbors
 *     Level 2: Neighbors of neighbors
 *     ...
 *
 *   ALGORITHM:
 *     1. Mark source as visited, add to queue
 *     2. While queue is not empty:
 *        a. Remove front vertex u from queue
 *        b. For each neighbor v of u:
 *           - If v not visited: mark visited, add to queue
 *
 *   WHY BFS?
 *     - Finds SHORTEST PATH in unweighted graphs
 *     - Explores all nodes at distance d before d+1
 *
 *   TIME COMPLEXITY : O(V + E)  (V = vertices, E = edges)
 *   SPACE COMPLEXITY: O(V)      (queue + visited array)
 *
 *   EXAMPLE:
 *     adj = [[1,2], [0,2,3], [0,1,4], [1,4], [2,3]]
 *     Start from 0:
 *       Visit 0 -> queue: [1,2]
 *       Visit 1 -> queue: [2,3]    (0 already visited)
 *       Visit 2 -> queue: [3,4]    (0,1 already visited)
 *       Visit 3 -> queue: [4]      (1,4... 4 added)
 *       Visit 4 -> done
 *     Output: [0, 1, 2, 3, 4]
 *
 * COMPILE:  gcc lab2.c -o lab2
 * RUN:      ./lab2
 */

#include <stdio.h>
#include <string.h>

#define MAX_V 100

/* Adjacency list using arrays (simpler than linked list) */
int adj[MAX_V][MAX_V];   /* adj[u] = list of neighbors of u */
int adjSize[MAX_V];      /* how many neighbors vertex u has */

int visited[MAX_V];      /* visited[v]=1 means v is already seen */
int queue[MAX_V];        /* our simple queue (array-based) */
int result[MAX_V];       /* BFS traversal order */
int resultSize;

/* Add undirected edge u--v */
void addEdge(int u, int v) {
    adj[u][adjSize[u]++] = v;
    adj[v][adjSize[v]++] = u;
}

/* BFS from source vertex */
void bfs(int source, int V) {
    memset(visited, 0, sizeof(visited));
    resultSize = 0;

    int front = 0, rear = 0;

    /* Step 1: start with source */
    visited[source] = 1;
    queue[rear++] = source;

    /* Step 2: process until queue empty */
    while (front < rear) {
        int u = queue[front++];          /* dequeue */
        result[resultSize++] = u;        /* record visit order */

        /* Step 3: visit all unvisited neighbors */
        for (int i = 0; i < adjSize[u]; i++) {
            int v = adj[u][i];
            if (!visited[v]) {
                visited[v] = 1;
                queue[rear++] = v;       /* enqueue */
            }
        }
    }
}

int main() {
    int V = 5;

    /*
     * Graph (undirected):
     * adj[][] = [[1,2], [0,2,3], [0,1,4], [1,4], [2,3]]
     *
     * Visual:
     *   0 -- 1 -- 3
     *   |  X    \ |
     *   2 ------- 4
     */
    memset(adjSize, 0, sizeof(adjSize));
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 2);
    addEdge(1, 3);
    addEdge(2, 4);
    addEdge(3, 4);

    printf("Graph has %d vertices\n", V);
    printf("Adjacency list:\n");
    for (int i = 0; i < V; i++) {
        printf("  %d -> ", i);
        for (int j = 0; j < adjSize[i]; j++)
            printf("%d ", adj[i][j]);
        printf("\n");
    }

    int source = 0;
    printf("\nBFS from vertex %d:\n  [ ", source);
    bfs(source, V);
    for (int i = 0; i < resultSize; i++) {
        printf("%d", result[i]);
        if (i < resultSize - 1) printf(", ");
    }
    printf(" ]\n");

    return 0;
}
