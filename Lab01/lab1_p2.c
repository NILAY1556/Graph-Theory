/*
 * ================================================================
 * LAB 1 - PROBLEM 2: Basic Graph Operations
 * Course: Graph Theory (2301CS595)
 * ================================================================
 *
 * CONCEPTS USED:
 *   - Adjacency Matrix : 2D array; matrix[i][j]=1 means edge i--j
 *   - Adjacency List   : list of neighbors per vertex
 *   - Degree           : number of edges connected to a vertex
 *   - Simple Graph     : no self-loops (i--i) and no parallel edges
 *   - Complete Graph   : every pair of vertices is connected (K_n)
 *   - Connected Graph  : you can reach any vertex from any other vertex
 *
 * THEORY:
 *   DEGREE of vertex v = how many edges touch v
 *     - For undirected: degree[v] = count of neighbors
 *     - Sum of all degrees = 2 * E  (Handshaking Lemma)
 *
 *   SIMPLE graph: no edge from a vertex to itself, no duplicate edges
 *
 *   COMPLETE graph K_n: every vertex connects to all others
 *     - Total edges in K_n = n*(n-1)/2
 *
 *   CONNECTED graph: BFS/DFS from any vertex visits ALL vertices
 *
 * COMPILE:  gcc lab1_p2.c -o lab1_p2
 * RUN:      ./lab1_p2
 */

#include <stdio.h>
#include <string.h>

#define MAX_V 10

int V, E;
int mat[MAX_V][MAX_V];   /* adjacency matrix */
int degree[MAX_V];        /* degree of each vertex */

/* -------- Build adjacency matrix -------- */
void buildMatrix(int edges[][2]) {
    memset(mat, 0, sizeof(mat));
    memset(degree, 0, sizeof(degree));
    for (int i = 0; i < E; i++) {
        int u = edges[i][0], v = edges[i][1];
        mat[u][v] = 1;
        mat[v][u] = 1;      /* undirected: both directions */
        degree[u]++;
        degree[v]++;
    }
}

/* -------- Print adjacency matrix -------- */
void printMatrix() {
    printf("\n1. Adjacency Matrix:\n   ");
    for (int i = 0; i < V; i++) printf("%3d", i);
    printf("\n");
    for (int i = 0; i < V; i++) {
        printf("%2d ", i);
        for (int j = 0; j < V; j++) printf("%3d", mat[i][j]);
        printf("\n");
    }
}

/* -------- Print adjacency list -------- */
void printAdjList() {
    printf("\n2. Adjacency List:\n");
    for (int i = 0; i < V; i++) {
        printf("   %d ->", i);
        for (int j = 0; j < V; j++)
            if (mat[i][j]) printf(" %d", j);
        printf("\n");
    }
}

/* -------- Print degree of each vertex -------- */
void printDegree() {
    printf("\n3. Degree of each vertex:\n");
    for (int i = 0; i < V; i++)
        printf("   Vertex %d: degree = %d\n", i, degree[i]);
}

/* -------- BFS to check connectivity -------- */
int isConnected() {
    int visited[MAX_V] = {0};
    int queue[MAX_V], front = 0, rear = 0;
    visited[0] = 1;
    queue[rear++] = 0;
    while (front < rear) {
        int u = queue[front++];
        for (int v = 0; v < V; v++) {
            if (mat[u][v] && !visited[v]) {
                visited[v] = 1;
                queue[rear++] = v;
            }
        }
    }
    for (int i = 0; i < V; i++)
        if (!visited[i]) return 0;
    return 1;
}

/* -------- Check simple, complete, connected -------- */
void printProperties() {
    printf("\n4. Graph Properties:\n");

    /* Simple: no self-loop */
    int simple = 1;
    for (int i = 0; i < V; i++)
        if (mat[i][i]) { simple = 0; break; }
    printf("   Simple   : %s\n", simple ? "YES" : "NO");

    /* Complete: all pairs connected => edges = V*(V-1)/2 */
    int complete = (E == V * (V - 1) / 2) ? 1 : 0;
    printf("   Complete : %s\n", complete ? "YES" : "NO");

    printf("   Connected: %s\n", isConnected() ? "YES" : "NO");
}

/* -------- Print total V and E -------- */
void printCount() {
    printf("\n5. Total vertices = %d, Total edges = %d\n", V, E);
}

int main() {
    /* Input: V=5, edges={(0,1),(0,2),(1,2),(2,3),(3,4)} */
    V = 5;
    int edges[][2] = {{0,1},{0,2},{1,2},{2,3},{3,4}};
    E = 5;

    buildMatrix(edges);
    printMatrix();
    printAdjList();
    printDegree();
    printProperties();
    printCount();

    return 0;
}
