/*
 * ================================================================
 * LAB 1 - PROBLEM 1: Directed Graph - Adjacency List
 * Course: Graph Theory (2301CS595)
 * ================================================================
 *
 * CONCEPTS USED:
 *   - Graph      : A set of vertices (nodes) connected by edges
 *   - Directed Graph (Digraph): Edges have direction; A->B does NOT mean B->A
 *   - Adjacency List: Each vertex stores a list of vertices it points to
 *   - Linked List: A chain of nodes where each node points to the next
 *
 * THEORY:
 *   A Graph G = (V, E):
 *     V = vertices  (the "points")
 *     E = edges     (the "connections between points")
 *
 *   In a DIRECTED graph, edge (u, v) means:
 *     u ---> v   (arrow FROM u TO v, not the other way)
 *
 *   ADJACENCY LIST stores, for each vertex, WHO it connects to:
 *     Vertex 0 -> [1]       means edge 0->1 exists
 *     Vertex 1 -> [2]       means edge 1->2 exists
 *     Vertex 2 -> [0]       means edge 2->0 exists
 *
 *   WHY adjacency list?
 *     - Saves memory when graph has few edges (sparse graph)
 *     - Easy to loop over all neighbors of a vertex
 *
 * COMPILE:  gcc lab1_p1.c -o lab1_p1
 * RUN:      ./lab1_p1
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_V 100   /* maximum vertices supported */

/* --- Node for linked list --- */
/* Each node holds: which vertex + pointer to next node */
struct Node {
    int vertex;
    struct Node *next;
};

/* adj[i] = head of list of neighbors of vertex i */
struct Node *adj[MAX_V];

/* Create a fresh node for vertex 'v' */
struct Node *newNode(int v) {
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    n->vertex = v;
    n->next   = NULL;
    return n;
}

/* Add directed edge: src -> dest */
void addEdge(int src, int dest) {
    struct Node *node = newNode(dest);
    /* Append to end so order matches input */
    if (adj[src] == NULL) {
        adj[src] = node;
    } else {
        struct Node *tmp = adj[src];
        while (tmp->next != NULL) tmp = tmp->next;
        tmp->next = node;
    }
}

/* Print adjacency list for V vertices */
void printAdjList(int V) {
    printf("\nAdjacency List:\n");
    for (int i = 0; i < V; i++) {
        printf("  %d ->", i);
        struct Node *tmp = adj[i];
        if (tmp == NULL) {
            printf(" NULL");
        }
        while (tmp) {
            printf(" %d", tmp->vertex);
            tmp = tmp->next;
        }
        printf("\n");
    }
}

/* Free all allocated memory for V vertices */
void freeAdj(int V) {
    for (int i = 0; i < V; i++) {
        struct Node *tmp = adj[i];
        while (tmp) {
            struct Node *next = tmp->next;
            free(tmp);
            tmp = next;
        }
        adj[i] = NULL;
    }
}

int main() {
    /* ---- Test Case 1 ---- */
    int V1 = 3;
    int edges1[][2] = {{0,1},{1,2},{2,0}};
    int E1 = 3;

    for (int i = 0; i < V1; i++) adj[i] = NULL;
    for (int i = 0; i < E1; i++) addEdge(edges1[i][0], edges1[i][1]);

    printf("Test Case 1 (V=%d):", V1);
    printAdjList(V1);
    freeAdj(V1);

    /* ---- Test Case 2 ---- */
    int V2 = 4;
    int edges2[][2] = {{0,1},{1,2},{1,3},{2,3},{3,0}};
    int E2 = 5;

    for (int i = 0; i < V2; i++) adj[i] = NULL;
    for (int i = 0; i < E2; i++) addEdge(edges2[i][0], edges2[i][1]);

    printf("\nTest Case 2 (V=%d):", V2);
    printAdjList(V2);
    freeAdj(V2);

    return 0;
}
