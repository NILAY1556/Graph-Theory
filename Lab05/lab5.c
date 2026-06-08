/*
 * ================================================================
 * LAB 5 - Spanning Trees, Rank, Nullity
 * Course: Graph Theory (2301CS595)
 * ================================================================
 *
 * CONCEPTS USED:
 *   - Connected Components: Groups of vertices that are reachable from each other
 *   - Spanning Tree: A tree that includes ALL vertices of a graph
 *   - Tree Branches: Edges in the spanning tree
 *   - Chords (Co-tree edges): Edges NOT in the spanning tree
 *   - Fundamental Circuit: A cycle formed by adding ONE chord to spanning tree
 *   - Rank of Graph: r(G) = V - number of connected components
 *   - Nullity of Graph: n(G) = E - r(G) = E - V + components
 *
 * THEORY:
 *   SPANNING TREE of graph G:
 *     - Subgraph that is a tree
 *     - Contains ALL vertices of G
 *     - Has exactly V-1 edges (for connected graph)
 *
 *   RANK  r(G) = V - k  where k = number of connected components
 *     For a connected graph: r(G) = V - 1
 *
 *   NULLITY n(G) = E - r(G) = E - V + k
 *     Also called: circuit rank, cyclomatic number
 *     = number of independent cycles in the graph
 *     = number of chords (co-tree edges)
 *
 *   FUNDAMENTAL CIRCUIT:
 *     When you add a chord (non-tree edge) to spanning tree,
 *     exactly ONE cycle is formed = fundamental circuit
 *
 *   P1 - FRIEND CIRCLES (Connected Components):
 *     Using Union-Find (Disjoint Set Union) to find groups
 *     If persons A,B are friends and B,C are friends -> one group
 *
 * COMPILE:  gcc lab5.c -o lab5
 * RUN:      ./lab5
 */

#include <stdio.h>
#include <string.h>

#define MAX_V 20

/* ===== PART 1: Friend Circles (Connected Components) ===== */
/* Union-Find data structure */
int parent[MAX_V], rank_uf[MAX_V];

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]); /* path compression */
    return parent[x];
}
void unite(int x, int y) {
    int px = find(x), py = find(y);
    if (px == py) return;
    if (rank_uf[px] < rank_uf[py]) { int t=px; px=py; py=t; }
    parent[py] = px;
    if (rank_uf[px] == rank_uf[py]) rank_uf[px]++;
}

/* ===== PART 2: Spanning Tree (BFS-based) ===== */
int adj[MAX_V][MAX_V], adjSize[MAX_V];
int inTree[MAX_V][MAX_V];   /* 1 if edge is in spanning tree */
int visited[MAX_V];

void addEdge(int u, int v) {
    adj[u][adjSize[u]++] = v;
    adj[v][adjSize[v]++] = u;
}

/* Build spanning tree using BFS */
void buildSpanningTree(int V) {
    memset(visited, 0, sizeof(visited));
    memset(inTree, 0, sizeof(inTree));
    int queue[MAX_V], front=0, rear=0;
    visited[0] = 1;
    queue[rear++] = 0;
    while (front < rear) {
        int u = queue[front++];
        for (int i = 0; i < adjSize[u]; i++) {
            int v = adj[u][i];
            if (!visited[v]) {
                visited[v] = 1;
                inTree[u][v] = inTree[v][u] = 1;  /* tree edge */
                queue[rear++] = v;
            }
        }
    }
}

int main() {
    /* === Part 1: Friend Circles === */
    printf("=== PART 1: Friend Circles (Connected Components) ===\n");
    int N = 5;
    for (int i = 0; i < N; i++) { parent[i] = i; rank_uf[i] = 0; }
    /* friendships: 0-1, 1-2, 3-4 */
    int friends[][2] = {{0,1},{1,2},{3,4}};
    int nF = 3;
    for (int i = 0; i < nF; i++)
        unite(friends[i][0], friends[i][1]);
    int groups = 0;
    printf("Group membership:\n");
    for (int i = 0; i < N; i++) {
        printf("  Person %d is in group %d\n", i, find(i));
        int isRoot = 1;
        for (int j = 0; j < i; j++) if (find(j) == find(i)) { isRoot = 0; break; }
        if (isRoot) groups++;
    }
    printf("Total friend circles: %d\n", groups);

    /* === Part 2: Spanning Tree + Rank/Nullity === */
    printf("\n=== PART 2: Spanning Tree, Rank, Nullity ===\n");
    int V = 5, E = 7;
    memset(adjSize, 0, sizeof(adjSize));
    addEdge(0,1); addEdge(0,2); addEdge(1,2);
    addEdge(1,3); addEdge(2,3); addEdge(3,4); addEdge(2,4);

    buildSpanningTree(V);

    printf("Edges classified:\n");
    int branches = 0, chords = 0;
    for (int u = 0; u < V; u++) {
        for (int i = 0; i < adjSize[u]; i++) {
            int v = adj[u][i];
            if (v > u) {
                if (inTree[u][v]) { printf("  Branch (tree edge): %d--%d\n", u, v); branches++; }
                else              { printf("  Chord  (co-tree)  : %d--%d\n", u, v); chords++; }
            }
        }
    }
    printf("\nTotal branches (tree edges) = %d\n", branches);
    printf("Total chords  (co-tree)    = %d\n", chords);

    int k = 1; /* connected graph has 1 component */
    int rankG    = V - k;
    int nullityG = E - rankG;
    printf("\nRank    r(G) = V - k = %d - %d = %d\n", V, k, rankG);
    printf("Nullity n(G) = E - r = %d - %d = %d\n", E, rankG, nullityG);
    printf("(Nullity = number of fundamental circuits = number of chords)\n");

    /* Show fundamental circuits */
    printf("\nFundamental Circuits (each chord + spanning tree path):\n");
    /* For simplicity, show which chord forms each circuit */
    int fc = 1;
    for (int u = 0; u < V; u++) {
        for (int i = 0; i < adjSize[u]; i++) {
            int v = adj[u][i];
            if (v > u && !inTree[u][v]) {
                printf("  Circuit %d: chord %d--%d adds a cycle\n", fc++, u, v);
            }
        }
    }

    return 0;
}
