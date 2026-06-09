/*
 * LAB 1 - PROBLEM 2
 * Basic Graph Operations - Undirected Graph
 *
 * IDEA:
 *   Store graph as adjacency matrix: mat[i][j] = 1 means edge i--j
 *   Everything else (degree, properties) is read from that matrix.
 */

#include <stdio.h>

int v, e;
int mat[10][10];

/* --- check if all vertices reachable from vertex 0 (BFS) --- */
int isConnected()
{
    int visited[10] = {0};
    int queue[10], front = 0, rear = 0;

    visited[0] = 1;
    queue[rear++] = 0;

    while (front < rear)
    {
        int u = queue[front++];
        for (int i = 0; i < v; i++)
            if (mat[u][i] == 1 && !visited[i])
            {
                visited[i] = 1;
                queue[rear++] = i;
            }
    }

    for (int i = 0; i < v; i++)
        if (!visited[i]) return 0;
    return 1;
}

int main()
{
    printf("Enter number of vertices: ");
    scanf("%d", &v);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++)
    {
        int u, w;
        scanf("%d %d", &u, &w);
        mat[u][w] = 1;
        mat[w][u] = 1;   /* undirected: both sides */
    }

    /* 1. Adjacency Matrix */
    printf("\n1. Adjacency Matrix:\n  ");
    for (int i = 0; i < v; i++) printf(" %d", i);
    printf("\n");
    for (int i = 0; i < v; i++)
    {
        printf("%d ", i);
        for (int j = 0; j < v; j++)
            printf(" %d", mat[i][j]);
        printf("\n");
    }

    /* 2. Adjacency List */
    printf("\n2. Adjacency List:\n");
    for (int i = 0; i < v; i++)
    {
        printf("%d -> ", i);
        for (int j = 0; j < v; j++)
            if (mat[i][j]) printf("%d ", j);
        printf("\n");
    }

    /* 3. Degree of each vertex */
    printf("\n3. Degree:\n");
    for (int i = 0; i < v; i++)
    {
        int deg = 0;
        for (int j = 0; j < v; j++)
            deg += mat[i][j];   /* count 1s in row */
        printf("Vertex %d: %d\n", i, deg);
    }

    /* 4. Properties */
    int simple   = !mat[0][0];             /* check one diagonal cell (all same) */
    for (int i = 0; i < v; i++) if (mat[i][i]) { simple = 0; break; }
    int complete = (e == v * (v - 1) / 2);

    printf("\n4. Properties:\n");
    printf("Simple    : %s\n", simple    ? "YES" : "NO");
    printf("Complete  : %s\n", complete  ? "YES" : "NO");
    printf("Connected : %s\n", isConnected() ? "YES" : "NO");

    return 0;
}

/*
 * SAMPLE RUN:
 *   Enter number of vertices: 5
 *   Enter number of edges: 5
 *   Enter edges (u v):
 *   0 1
 *   0 2
 *   1 2
 *   2 3
 *   3 4
 *
 *   1. Adjacency Matrix:
 *     0 1 2 3 4
 *   0  0 1 1 0 0
 *   1  1 0 1 0 0
 *   2  1 1 0 1 0
 *   3  0 0 1 0 1
 *   4  0 0 0 1 0
 *
 *   2. Adjacency List:
 *   0 -> 1 2
 *   1 -> 0 2
 *   2 -> 0 1 3
 *   3 -> 2 4
 *   4 -> 3
 *
 *   3. Degree:
 *   Vertex 0: 2
 *   Vertex 1: 2
 *   Vertex 2: 3
 *   Vertex 3: 2
 *   Vertex 4: 1
 *
 *   4. Properties:
 *   Simple    : YES
 *   Complete  : NO
 *   Connected : YES
 */
