/*
 * LAB 1 - PROBLEM 1
 * Directed Graph - Adjacency List
 *
 * IDEA:
 *   Store all edges as pairs: (source, destination)
 *   To print neighbors of vertex i → scan all edges, print dest where src == i
 */

#include <stdio.h>

int main()
{
    int v, e;

    printf("Enter number of vertices: ");
    scanf("%d", &v);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    int edges[e][2];   /* edges[i][0] = source,  edges[i][1] = destination */

    printf("Enter edges (source destination):\n");
    for (int i = 0; i < e; i++)
        scanf("%d %d", &edges[i][0], &edges[i][1]);

    /* Print adjacency list */
    printf("\nAdjacency List:\n");
    for (int i = 0; i < v; i++)
    {
        printf("%d -> ", i);
        for (int j = 0; j < e; j++)
            if (edges[j][0] == i)          /* this edge starts from vertex i */
                printf("%d ", edges[j][1]); /* print where it goes */
        printf("\n");
    }

    return 0;
}

/*
 * SAMPLE RUN:
 *   Enter number of vertices: 4
 *   Enter number of edges: 5
 *   Enter edges (source destination):
 *   0 1
 *   1 2
 *   1 3
 *   2 3
 *   3 0
 *
 *   Adjacency List:
 *   0 -> 1
 *   1 -> 2 3
 *   2 -> 3
 *   3 -> 0
 */
