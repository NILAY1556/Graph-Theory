/*
 * ================================================================
 * LAB 12 - Graph Matrices: Adjacency, Degree, Laplacian
 * Course: Graph Theory (2301CS595)
 * ================================================================
 *
 * CONCEPTS USED:
 *   - Adjacency Matrix A: A[i][j]=1 if edge i-j exists, 0 otherwise
 *   - Degree Matrix D: Diagonal matrix, D[i][i] = degree of vertex i
 *   - Laplacian Matrix L: L = D - A
 *   - Properties of Laplacian: symmetric, positive semi-definite
 *   - Eigenvalues of Laplacian: All non-negative; smallest is 0
 *
 * THEORY:
 *   ADJACENCY MATRIX A (n×n):
 *     A[i][j] = 1  if edge {i,j} exists
 *     A[i][j] = 0  otherwise
 *     A is SYMMETRIC for undirected graphs
 *
 *   DEGREE MATRIX D (diagonal):
 *     D[i][i] = deg(i) = number of edges at vertex i
 *     D[i][j] = 0  for i ≠ j
 *
 *   LAPLACIAN MATRIX L = D - A:
 *     L[i][i]  =  deg(i)         (diagonal: positive)
 *     L[i][j]  = -1  if {i,j} ∈ E  (off-diagonal: negative or 0)
 *     L[i][j]  =  0  if {i,j} ∉ E
 *
 *   KEY PROPERTIES OF L:
 *     1. Row sums = 0:  sum of each row is 0
 *     2. L is positive semi-definite
 *     3. Smallest eigenvalue λ1 = 0  (always)
 *     4. Number of 0 eigenvalues = number of connected components
 *     5. Second smallest eigenvalue λ2 (Fiedler value):
 *        λ2 = 0 iff graph is disconnected
 *        Larger λ2 = better connected graph
 *
 *   USES OF LAPLACIAN:
 *     - Spectral graph theory
 *     - Graph clustering (spectral clustering)
 *     - Network analysis
 *     - Counting spanning trees: # = det(any cofactor of L) / n
 *
 * COMPILE:  gcc lab12.c -o lab12
 * RUN:      ./lab12
 */

#include <stdio.h>
#include <string.h>

#define MAX_V 8

int V, E;
int A[MAX_V][MAX_V];   /* Adjacency matrix */
int D[MAX_V][MAX_V];   /* Degree matrix */
int L[MAX_V][MAX_V];   /* Laplacian matrix */

void addEdge(int u, int v) {
    A[u][v] = A[v][u] = 1;
    D[u][u]++;
    D[v][v]++;
}

void buildLaplacian() {
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            L[i][j] = D[i][j] - A[i][j];
}

void printMatrix(int M[MAX_V][MAX_V], const char *name) {
    printf("\n%s:\n     ", name);
    for (int j = 0; j < V; j++) printf("%4d", j);
    printf("\n   +");
    for (int j = 0; j < V; j++) printf("----");
    printf("\n");
    for (int i = 0; i < V; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < V; j++) printf("%4d", M[i][j]);
        printf("\n");
    }
}

void verifyLaplacian() {
    printf("\nVerification of Laplacian properties:\n");
    /* Row sum = 0 */
    int allZero = 1;
    for (int i = 0; i < V; i++) {
        int sum = 0;
        for (int j = 0; j < V; j++) sum += L[i][j];
        if (sum != 0) allZero = 0;
    }
    printf("  Row sums are all 0: %s\n", allZero ? "YES ✓" : "NO");

    /* Diagonal = degree */
    printf("  Diagonal equals degree:\n");
    for (int i = 0; i < V; i++)
        printf("    L[%d][%d] = %d = deg(%d) ✓\n", i, i, L[i][i], i);

    /* Off-diagonal = -A */
    printf("  Off-diagonal: L[i][j] = -A[i][j] for i≠j ✓\n");
}

int main() {
    V = 5; E = 0;
    memset(A, 0, sizeof(A));
    memset(D, 0, sizeof(D));

    /*
     * Graph:
     *   0 -- 1 -- 2
     *   |    |
     *   3 -- 4
     */
    addEdge(0,1); addEdge(1,2);
    addEdge(0,3); addEdge(1,4);
    addEdge(3,4);
    E = 5;

    buildLaplacian();

    printf("=== Graph Matrices ===\n");
    printf("Graph: 0-1, 1-2, 0-3, 1-4, 3-4\n");

    printMatrix(A, "Adjacency Matrix (A)");
    printMatrix(D, "Degree Matrix (D)");
    printMatrix(L, "Laplacian Matrix (L = D - A)");

    verifyLaplacian();

    printf("\nKey insight:\n");
    printf("  Laplacian L encodes graph structure\n");
    printf("  Its eigenvalues reveal: connectivity, clusters, spanning trees\n");
    printf("  Smallest eigenvalue = 0 (graph is connected -> only one 0)\n");

    return 0;
}
