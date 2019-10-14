#include <stdio.h>

float *run_gaussj(int N, float **A, float *b) {

}

float run_ludcmp(int N, float **A, float *b) {

}

float run_svdcmp(int N, float **A, float *b) {

}

/**
 * Load data from `ifp`.
 * @param ifp Input file pointer.
 * @param N Order of matrix A and vector b.
 * @param A 2D array representing matrix A.
 * @param b 1D array representing vector b.
 */
void load_data(FILE *ifp, int *N, float **A, float *b) {

}

/**
 * Solves the linear equation Ax=b where A is square matrix and b is vector.
 * @param argc Argument count.
 * @param argv `argv[1]` is relative path of data file containing elements of the matrix A and the vector b.
 * @return
 */
int main(int argc, char *argv[]) {
    FILE *ifp;
    ifp = fopen(argv[1], "r");
    if (ifp == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", argv[1]);
    }
    int N;
    float **A;
    float *b;
    load_data(ifp, &N, A, b);
    run_gaussj(N, A, b);
    run_ludcmp(N, A, b);
    run_svdcmp(N, A, b);

    return 0;
}