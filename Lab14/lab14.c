/*
 * ================================================================
 * LAB 14 - Spectral Clustering
 * Course: Graph Theory (2301CS595)
 * ================================================================
 *
 * CONCEPTS USED:
 *   - Spectral Clustering: Use eigenvalues/vectors of Laplacian to cluster graph
 *   - Fiedler Vector: Eigenvector for the 2nd smallest eigenvalue of Laplacian
 *   - Fiedler Value (λ2): Algebraic connectivity; λ2 > 0 iff graph is connected
 *   - Graph Partition: Divide vertices into groups (clusters)
 *   - k-means on Fiedler vector: Split based on sign or median of Fiedler vector
 *
 * THEORY:
 *   SPECTRAL CLUSTERING steps (for 2 clusters):
 *     1. Build Laplacian matrix L = D - A
 *     2. Find Fiedler vector f (eigenvector for 2nd smallest eigenvalue λ2)
 *     3. Partition: vertices where f[i] < 0 -> Cluster 1
 *                   vertices where f[i] >= 0 -> Cluster 2
 *
 *   WHY FIEDLER VECTOR WORKS:
 *     - The Laplacian L encodes graph structure
 *     - Smallest eigenvalue λ1=0, its eigenvector is constant (all same)
 *     - Second eigenvalue λ2 (Fiedler value) and its eigenvector (Fiedler vector)
 *       capture the "most natural split" of the graph
 *     - Sign of Fiedler vector component tells which cluster vertex belongs to
 *
 *   POWER METHOD FOR FIEDLER VECTOR:
 *     Direct power method gives LARGEST eigenvalue
 *     For SMALLEST non-zero eigenvalue, use INVERSE ITERATION or
 *     deflation: subtract λ_max * I and iterate
 *
 *     Simpler approach used here:
 *       Shift L: L' = L + c*I  (shifts all eigenvalues by c)
 *       Then largest eigenvalue of (-L + max*I) corresponds to smallest of L
 *       Fiedler vector approximated by orthogonalizing against [1,1,...,1]
 *
 * COMPILE:  gcc lab14.c -o lab14 -lm
 * RUN:      ./lab14
 */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX_V 8
#define ITER  2000
#define EPS   1e-10

int V;
double Lap[MAX_V][MAX_V];

/* Dot product */
double dot(double a[], double b[]) {
    double s = 0;
    for (int i = 0; i < V; i++) s += a[i] * b[i];
    return s;
}

/* Normalize vector in-place */
void normalize(double v[]) {
    double n = sqrt(dot(v, v));
    if (n < EPS) return;
    for (int i = 0; i < V; i++) v[i] /= n;
}

/* Subtract projection of v onto u from v: v = v - (v·u)*u */
void orthogonalize(double v[], double u[]) {
    double proj = dot(v, u);
    for (int i = 0; i < V; i++) v[i] -= proj * u[i];
}

/* Matrix-vector multiply */
void matVec(double M[MAX_V][MAX_V], double in[], double out[]) {
    for (int i = 0; i < V; i++) {
        out[i] = 0;
        for (int j = 0; j < V; j++) out[i] += M[i][j] * in[j];
    }
}

/*
 * Find Fiedler vector using power method with deflation:
 * Deflate largest eigenvalue, then find next dominant eigenvector,
 * orthogonalized against constant vector (eigvec for λ1=0).
 */
void fiedlerVector(double fv[]) {
    /* Build shifted matrix: M = λ_max*I - L  (so largest eig of L becomes 0) */
    /* Estimate λ_max via one power iteration on L */
    double x[MAX_V], y[MAX_V];
    for (int i = 0; i < V; i++) x[i] = 1.0;
    normalize(x);
    double lmax = 0;
    for (int it = 0; it < 200; it++) {
        matVec(Lap, x, y);
        lmax = dot(x, y);
        normalize(y);
        for (int i = 0; i < V; i++) x[i] = y[i];
    }

    /* Shifted matrix M[i][j] = (lmax+1)*delta(i,j) - L[i][j] */
    double M[MAX_V][MAX_V];
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            M[i][j] = (i == j ? (lmax + 1.0) : 0.0) - Lap[i][j];

    /* Constant eigenvector u = [1/sqrt(V), ...] for λ1=0 */
    double u[MAX_V];
    for (int i = 0; i < V; i++) u[i] = 1.0 / sqrt((double)V);

    /* Power method orthogonalized against u */
    for (int i = 0; i < V; i++) fv[i] = (i % 2 == 0) ? 1.0 : -1.0;
    orthogonalize(fv, u);
    normalize(fv);

    for (int it = 0; it < ITER; it++) {
        matVec(M, fv, y);
        orthogonalize(y, u);
        normalize(y);
        double diff = 0;
        for (int i = 0; i < V; i++) diff += fabs(y[i] - fv[i]);
        for (int i = 0; i < V; i++) fv[i] = y[i];
        if (diff < EPS) break;
    }
}

int main() {
    V = 6;
    memset(Lap, 0, sizeof(Lap));

    /*
     * Graph with 2 natural clusters:
     * Cluster A: {0,1,2} densely connected
     * Cluster B: {3,4,5} densely connected
     * One bridge: 2--3
     *
     * Edges: 0-1, 1-2, 0-2, 2-3, 3-4, 4-5, 3-5
     */
    int edges[][2] = {{0,1},{1,2},{0,2},{2,3},{3,4},{4,5},{3,5}};
    int E = 7;
    double deg[MAX_V] = {0};

    for (int i = 0; i < E; i++) {
        int u = edges[i][0], v = edges[i][1];
        Lap[u][v] -= 1.0;
        Lap[v][u] -= 1.0;
        deg[u]++; deg[v]++;
    }
    for (int i = 0; i < V; i++) Lap[i][i] = deg[i];

    printf("=== Spectral Clustering ===\n");
    printf("Graph: cluster {0,1,2} and {3,4,5} joined by bridge 2-3\n\n");

    printf("Laplacian Matrix L:\n     ");
    for (int j = 0; j < V; j++) printf("%5d", j);
    printf("\n");
    for (int i = 0; i < V; i++) {
        printf("%3d  ", i);
        for (int j = 0; j < V; j++) printf("%5.0f", Lap[i][j]);
        printf("\n");
    }

    double fv[MAX_V];
    fiedlerVector(fv);

    printf("\nFiedler Vector (2nd eigenvector of Laplacian):\n");
    for (int i = 0; i < V; i++)
        printf("  f[%d] = %+.6f\n", i, fv[i]);

    printf("\nSpectral Clustering (2 clusters by sign of Fiedler vector):\n");
    printf("  Cluster 0 (f[i] < 0): ");
    for (int i = 0; i < V; i++) if (fv[i] < 0) printf("%d ", i);
    printf("\n  Cluster 1 (f[i] >= 0): ");
    for (int i = 0; i < V; i++) if (fv[i] >= 0) printf("%d ", i);
    printf("\n");

    printf("\nConclusion:\n");
    printf("  Fiedler vector correctly identifies the two natural clusters!\n");
    printf("  Vertices {0,1,2} form one tight group, {3,4,5} form another.\n");
    printf("  The bridge edge 2-3 is the minimum cut.\n");

    return 0;
}
