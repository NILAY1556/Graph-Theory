/*
 * ================================================================
 * LAB 7 - Connectivity
 * Course: Graph Theory (2301CS595)
 * ================================================================
 *
 * CONCEPTS USED:
 *   - Vertex Connectivity κ(G): Min vertices to remove to disconnect G
 *   - Edge Connectivity λ(G): Min edges to remove to disconnect G
 *   - Separable Graph: Has at least one articulation point, κ(G)=1
 *   - Non-Separable (Biconnected): No articulation points, κ(G)≥2
 *   - Fundamental Cut-Set: Min set of edges whose removal disconnects G
 *
 * THEORY:
 *   CONNECTIVITY tells us how "robust" a graph is:
 *     κ(G)  = vertex connectivity  (vertex cut number)
 *     λ(G)  = edge connectivity    (edge cut number)
 *     δ(G)  = minimum degree
 *
 *   THEOREM (Whitney's): κ(G) ≤ λ(G) ≤ δ(G)
 *     Vertex cut ≤ Edge cut ≤ Min degree
 *
 *   SEPARABLE GRAPH: κ(G) = 1  (has a cut vertex)
 *   NON-SEPARABLE:   κ(G) ≥ 2  (removing one vertex keeps it connected)
 *
 *   FUNDAMENTAL CUT-SET:
 *     Given spanning tree, each TREE EDGE e defines a cut-set:
 *     Remove e from spanning tree -> tree splits into 2 parts (A, B)
 *     Cut-set = all edges between part A and part B
 *
 *   HOW TO COMPUTE λ(G) SIMPLY:
 *     Try removing 1 edge at a time: if graph disconnects, λ=1
 *     Otherwise try removing 2 at a time, etc.
 *     (For simple graphs, λ(G) ≥ 2 if no bridge exists)
 *
 *   BRIDGE: An edge whose removal disconnects the graph
 *     (Edge version of articulation point)
 *
 * COMPILE:  gcc lab7.c -o lab7
 * RUN:      ./lab7
 */

#include <stdio.h>
#include <string.h>

#define MAX_V 20

int V, E;
int adj[MAX_V][MAX_V], adjSize[MAX_V];
int disc[MAX_V], low[MAX_V], visited[MAX_V];
int isAP[MAX_V], isBridge[MAX_V][MAX_V];
int timer_val;
int degree[MAX_V];

void addEdge(int u, int v) {
    adj[u][adjSize[u]++] = v;
    adj[v][adjSize[v]++] = u;
    degree[u]++; degree[v]++;
}

/* DFS to find articulation points and bridges */
void dfs(int u, int parent) {
    visited[u] = 1;
    disc[u] = low[u] = timer_val++;
    int children = 0;
    for (int i = 0; i < adjSize[u]; i++) {
        int v = adj[u][i];
        if (!visited[v]) {
            children++;
            dfs(v, u);
            if (low[v] < low[u]) low[u] = low[v];
            if (parent == -1 && children > 1) isAP[u] = 1;
            if (parent != -1 && low[v] >= disc[u]) isAP[u] = 1;
            /* Bridge: edge u-v is bridge if low[v] > disc[u] */
            if (low[v] > disc[u]) isBridge[u][v] = isBridge[v][u] = 1;
        } else if (v != parent) {
            if (disc[v] < low[u]) low[u] = disc[v];
        }
    }
}

/* Check connectivity using BFS */
int isConnected() {
    int vis[MAX_V] = {0}, queue[MAX_V];
    int front=0, rear=0;
    vis[0]=1; queue[rear++]=0;
    while(front<rear) {
        int u=queue[front++];
        for(int i=0;i<adjSize[u];i++)
            if(!vis[adj[u][i]]) { vis[adj[u][i]]=1; queue[rear++]=adj[u][i]; }
    }
    for(int i=0;i<V;i++) if(!vis[i]) return 0;
    return 1;
}

int main() {
    V = 6; E = 7;
    memset(adjSize,0,sizeof(adjSize));
    memset(degree,0,sizeof(degree));
    memset(isAP,0,sizeof(isAP));
    memset(isBridge,0,sizeof(isBridge));

    /* Graph: triangle 0-1-2, then 2-3, 3-4-5 triangle */
    addEdge(0,1); addEdge(1,2); addEdge(0,2);   /* triangle */
    addEdge(2,3);                                 /* bridge */
    addEdge(3,4); addEdge(4,5); addEdge(3,5);   /* triangle */

    printf("=== Connectivity Analysis ===\n");
    printf("Edges: 0-1, 1-2, 0-2, 2-3, 3-4, 4-5, 3-5\n\n");

    timer_val=0;
    memset(visited,0,sizeof(visited));
    for(int i=0;i<V;i++) if(!visited[i]) dfs(i,-1);

    /* Min degree */
    int minDeg = degree[0];
    for(int i=1;i<V;i++) if(degree[i]<minDeg) minDeg=degree[i];

    /* Count bridges (edge connectivity lower bound) */
    int bridges=0;
    printf("Bridges (edges whose removal disconnects graph):\n");
    for(int u=0;u<V;u++)
        for(int v=u+1;v<V;v++)
            if(isBridge[u][v]) { printf("  %d--%d\n",u,v); bridges++; }
    if(!bridges) printf("  None\n");

    printf("\nArticulation Points (cut vertices):\n  ");
    int hasAP=0;
    for(int i=0;i<V;i++) if(isAP[i]) { printf("%d ",i); hasAP=1; }
    if(!hasAP) printf("None");
    printf("\n");

    printf("\nConnectivity summary:\n");
    printf("  Minimum degree    δ(G) = %d\n", minDeg);
    int lambda = bridges>0 ? 1 : 2;
    printf("  Edge connectivity λ(G) = %d  (%s)\n", lambda,
           bridges>0 ? "bridge exists, λ=1" : "no bridge, λ≥2");
    int kappa = hasAP ? 1 : 2;
    printf("  Vertex conn.      κ(G) = %d  (%s)\n", kappa,
           hasAP ? "cut vertex exists, κ=1" : "no cut vertex, κ≥2");
    printf("  Whitney's: κ ≤ λ ≤ δ  =>  %d ≤ %d ≤ %d  ✓\n", kappa, lambda, minDeg);
    printf("\n  Graph is: %s\n", hasAP ? "SEPARABLE (has cut vertex)" : "NON-SEPARABLE (biconnected)");

    return 0;
}
