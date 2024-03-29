#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "nr.h"

float *run_gaussj(int N, float **A, float *b) {
    const int M = 1;
    // Copy elements.
    float **cpy_A = calloc(N + 1, sizeof(float *));
    for (int i = 1; i <= N; i++) {
        cpy_A[i] = calloc(N + 1, sizeof(float));
        memcpy(cpy_A[i], A[i], (N + 1) * sizeof(float));
    }
    float **cpy_b = calloc(N + 1, sizeof(float *));
    for (int i = 1; i <= N; i++) {
        cpy_b[i] = calloc(M + 1, sizeof(float));
        cpy_b[i][1] = b[i];
    }

    gaussj(cpy_A, N, cpy_b, M);
    float *ret = calloc(N + 1, sizeof(float));
    for (int i = 1; i <= N; i++)
        ret[i] = cpy_b[i][1];

    for (int i = 1; i <= N; i++)
        free(cpy_A[i]);
    free(cpy_A);
    for (int i = 1; i <= N; i++)
        free(cpy_b[i]);
    free(cpy_b);

    return ret;
}

float *run_ludcmp(int N, float **A, float *b) {

}

float *run_svdcmp(int N, float **A, float *b) {

}

/**
 * Allocate memory and load data from `ifp`.
 * @param ifp Input file pointer.
 * @param N Order of matrix A and vector b.
 * @param A 2D array representing matrix A.
 * @param b 1D array representing vector b.
 */
void load_data(FILE *ifp, int *N, float **A, float *b) {
    int M;
    fscanf(ifp, "%d %d", &M, N);
    assert(M == *N);
    // Make space for A and b.
    A = calloc(*N + 1, sizeof(float *));
    for (int i = 1; i <= *N; i++)
        A[i] = calloc(*N + 1, sizeof(float));
    b = calloc(*N + 1, sizeof(float));
    // Read A, b.
    for (int i = 1; i <= *N; i++)
        for (int j = 1; j <= *N; j++)
            fscanf(ifp, "%f", &A[i][j]);
    for (int i = 1; i <= *N; i++)
        fscanf(ifp, "%f", &b[i]);
}

/**
 * Solves the linear equation Ax=b where A is square matrix and b is vector.
 * @param argc Argument count.
 * @param argv `argv[1]` is relative path of data file containing elements of the matrix A and the vector b.
 * @return
 */
int main(int argc, char *argv[]) {
    FILE *ifp;
    int N;
    float **A = NULL;
    float *b = NULL;

    ifp = fopen(argv[1], "r");
    if (ifp == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", argv[1]);
    }
    load_data(ifp, &N, A, b);
    fclose(ifp);

    run_gaussj(N, A, b);
    // run_ludcmp(N, A, b);
    // run_svdcmp(N, A, b);

    for (int i = 1; i <= N; i++)
        free(A[i]);
    free(A);
    free(b);
    return 0;
}