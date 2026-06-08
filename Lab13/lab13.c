/*
 * ================================================================
 * LAB 13 - Eigenvalues & Eigenvectors (Power Method)
 * Course: Graph Theory (2301CS595)
 * ================================================================
 *
 * CONCEPTS USED:
 *   - Eigenvalue λ: A scalar such that A·v = λ·v
 *   - Eigenvector v: Non-zero vector satisfying A·v = λ·v
 *   - Power Method: Iterative algorithm to find dominant eigenvalue
 *   - Dominant Eigenvalue: The eigenvalue with largest absolute value
 *   - Spectrum of Graph: Set of all eigenvalues of adjacency matrix
 *
 * THEORY:
 *   For a matrix A and vector v:
 *     A · v = λ · v   means:
 *     "Multiplying A by v only scales v by factor λ"
 *     λ = eigenvalue,  v = eigenvector
 *
 *   POWER METHOD (finds LARGEST eigenvalue):
 *     Start with any non-zero vector x0 (e.g., all 1s)
 *     Repeat:
 *       x_new = A · x_old         (multiply matrix by vector)
 *       λ     = max(|x_new|)      (estimate eigenvalue = max component)
 *       x_old = x_new / λ         (normalize: divide by λ)
 *     Until λ converges (changes very little)
 *
 *   WHY GRAPH EIGENVALUES MATTER:
 *     - Largest eigenvalue (spectral radius): measures graph connectivity
 *     - Fiedler value (2nd smallest of Laplacian): algebraic connectivity
 *     - Eigenvalues reveal: clusters, bipartiteness, expansion
 *
 *   SPECTRAL RADIUS ρ(G):
 *     ρ(G) = largest eigenvalue of adjacency matrix A
 *     For k-regular graph: ρ(G) = k
 *
 * COMPILE:  gcc lab13.c -o lab13 -lm
 * RUN:      ./lab13
 */

#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_V 8
#define ITER  1000
#define EPS   1e-9

int V;
double A[MAX_V][MAX_V];   /* adjacency matrix (float for eigen computation) */
double L[MAX_V][MAX_V];   /* Laplacian matrix */

/* Matrix-vector multiply: result = M * vec */
void matVec(double M[MAX_V][MAX_V], double vec[], double result[]) {
    for (int i = 0; i < V; i++) {
        result[i] = 0.0;
        for (int j = 0; j < V; j++)
            result[i] += M[i][j] * vec[j];
    }
}

/* Power method: returns dominant eigenvalue, eigenvec stored in vec[] */
double powerMethod(double M[MAX_V][MAX_V], double vec[]) {
    double newvec[MAX_V];
    double lambda = 1.0, prevLambda;

    /* Initialize with all-ones vector */
    for (int i = 0; i < V; i++) vec[i] = 1.0;

    for (int iter = 0; iter < ITER; iter++) {
        matVec(M, vec, newvec);

        /* Find max absolute component (Rayleigh quotient approximation) */
        prevLambda = lambda;
        lambda = 0.0;
        for (int i = 0; i < V; i++)
            if (fabs(newvec[i]) > fabs(lambda)) lambda = newvec[i];

        /* Normalize */
        for (int i = 0; i < V; i++)
            vec[i] = (fabs(lambda) > EPS) ? newvec[i] / lambda : newvec[i];

        if (fabs(lambda - prevLambda) < EPS) break;
    }
    return lambda;
}

void printVec(double vec[], const char *name) {
    printf("%s = [ ", name);
    for (int i = 0; i < V; i++) printf("%.4f ", vec[i]);
    printf("]\n");
}

int main() {
    V = 5;
    memset(A, 0, sizeof(A));
    memset(L, 0, sizeof(L));

    /*
     * Undirected graph:
     *   0 -- 1 -- 2
     *   |    |
     *   3 -- 4
     * Edges: 0-1, 1-2, 0-3, 1-4, 3-4
     */
    int edges[][2] = {{0,1},{1,2},{0,3},{1,4},{3,4}};
    int E = 5;
    double deg[MAX_V] = {0};

    for (int i = 0; i < E; i++) {
        int u = edges[i][0], v = edges[i][1];
        A[u][v] = A[v][u] = 1.0;
        deg[u]++; deg[v]++;
    }

    /* Build Laplacian L = D - A */
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            L[i][j] = -A[i][j];
        L[i][i] = deg[i];
    }

    printf("=== Eigenvalues & Eigenvectors (Power Method) ===\n");
    printf("Graph: 0-1, 1-2, 0-3, 1-4, 3-4\n\n");

    /* Print adjacency matrix */
    printf("Adjacency Matrix A:\n   ");
    for (int i = 0; i < V; i++) printf("%5d", i);
    printf("\n");
    for (int i = 0; i < V; i++) {
        printf("%2d ", i);
        for (int j = 0; j < V; j++) printf("%5.0f", A[i][j]);
        printf("\n");
    }

    /* Dominant eigenvalue of adjacency matrix */
    printf("\n--- Adjacency Matrix A ---\n");
    double eigVecA[MAX_V];
    double lambdaA = powerMethod(A, eigVecA);
    printf("Dominant Eigenvalue (spectral radius) = %.6f\n", lambdaA);
    printVec(eigVecA, "Eigenvector");

    /* Dominant eigenvalue of Laplacian */
    printf("\n--- Laplacian Matrix L = D - A ---\n");
    double eigVecL[MAX_V];
    double lambdaL = powerMethod(L, eigVecL);
    printf("Dominant Eigenvalue of L = %.6f\n", lambdaL);
    printVec(eigVecL, "Eigenvector");

    printf("\nKey Facts:\n");
    printf("  Spectral radius of A = %.4f\n", lambdaA);
    printf("  Sum of all degrees = %d => average degree = %.2f\n",
           2 * E, (2.0 * E) / V);
    printf("  For connected graph: spectral radius >= average degree\n");
    printf("  Laplacian's smallest eigenvalue = 0 (constant vector is eigenvector)\n");
    printf("  Largest eigenvalue of L = %.4f\n", lambdaL);

    return 0;
}
