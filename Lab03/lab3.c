/*
 * ================================================================
 * LAB 3 - DFS: Depth First Search
 * Course: Graph Theory (2301CS595)
 * ================================================================
 *
 * CONCEPTS USED:
 *   - DFS (Depth First Search): Go as deep as possible before backtracking
 *   - Stack / Recursion: DFS uses a stack (recursion does this automatically)
 *   - Visited array: Avoid revisiting the same vertex
 *   - DFS Tree: The tree formed by DFS traversal edges
 *
 * THEORY:
 *   DFS explores a graph by going as DEEP as possible along each branch
 *   before backtracking.
 *
 *   Think of it like exploring a maze:
 *     - Go forward until you hit a dead end
 *     - Back up one step and try another path
 *     - Repeat
 *
 *   ALGORITHM (Recursive):
 *     dfs(u):
 *       1. Mark u as visited
 *       2. Print u
 *       3. For each neighbor v of u:
 *            If v not visited: call dfs(v)
 *
 *   DFS gives us:
 *     - Tree edges: edges used to discover new vertices
 *     - Back edges: edges going to an ancestor (indicate cycles!)
 *
 *   TIME COMPLEXITY : O(V + E)
 *   SPACE COMPLEXITY: O(V) for visited array + recursion stack
 *
 *   DIFFERENCE FROM BFS:
 *     BFS uses a QUEUE -> explores level by level (breadth)
 *     DFS uses a STACK -> explores branch by branch (depth)
 *
 *   EXAMPLE:
 *     Graph: 0-1, 0-2, 1-3, 2-4
 *     DFS from 0:
 *       Visit 0 -> go to neighbor 1
 *       Visit 1 -> go to neighbor 3
 *       Visit 3 -> no unvisited neighbors -> backtrack
 *       back to 1 -> no more neighbors -> backtrack
 *       back to 0 -> go to neighbor 2
 *       Visit 2 -> go to neighbor 4
 *       Visit 4 -> no more -> backtrack all
 *     Output: 0 1 3 2 4
 *
 * COMPILE:  gcc lab3.c -o lab3
 * RUN:      ./lab3
 */

#include <stdio.h>
#include <string.h>

#define MAX_V 100

int adj[MAX_V][MAX_V];   /* adj[u] stores neighbors of u */
int adjSize[MAX_V];
int visited[MAX_V];
int order[MAX_V];        /* DFS visit order */
int orderSize = 0;

/* Add undirected edge u--v */
void addEdge(int u, int v) {
    adj[u][adjSize[u]++] = v;
    adj[v][adjSize[v]++] = u;
}

/* Recursive DFS from vertex u */
void dfs(int u) {
    visited[u] = 1;
    order[orderSize++] = u;

    for (int i = 0; i < adjSize[u]; i++) {
        int v = adj[u][i];
        if (!visited[v]) {
            dfs(v);   /* go deeper */
        }
    }
}

/* DFS for entire graph (handles disconnected graphs too) */
void dfsAll(int V) {
    memset(visited, 0, sizeof(visited));
    orderSize = 0;
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    int V = 6;
    memset(adjSize, 0, sizeof(adjSize));

    /*
     * Graph (undirected):
     *   0 -- 1 -- 3
     *   |         |
     *   2 -- 4 -- 5
     */
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(2, 4);
    addEdge(3, 5);
    addEdge(4, 5);

    printf("Graph has %d vertices\n", V);
    printf("Adjacency list:\n");
    for (int i = 0; i < V; i++) {
        printf("  %d -> ", i);
        for (int j = 0; j < adjSize[i]; j++)
            printf("%d ", adj[i][j]);
        printf("\n");
    }

    int source = 0;
    printf("\nDFS from vertex %d:\n  [ ", source);
    memset(visited, 0, sizeof(visited));
    orderSize = 0;
    dfs(source);
    for (int i = 0; i < orderSize; i++) {
        printf("%d", order[i]);
        if (i < orderSize - 1) printf(", ");
    }
    printf(" ]\n");

    /* If graph is disconnected, use dfsAll */
    printf("\nDFS of entire graph (all components):\n  [ ");
    dfsAll(V);
    for (int i = 0; i < orderSize; i++) {
        printf("%d", order[i]);
        if (i < orderSize - 1) printf(", ");
    }
    printf(" ]\n");

    return 0;
}
