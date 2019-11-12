#include <stdio.h>
#include <time.h>
#include "nrutil.h"

float ran0(long *idum);
void jacobi(float **a, int n, float d[], float **v, int *nrot);
void eigsrt(float d[], float **v, int n);

int main() {
    const int N = 11;
    float **a = matrix(1, N, 1, N);
    float **v = matrix(1, N, 1, N);
    float *d = vector(1, N);
    long idum = time(NULL);
    int nrot;

    // Generate random matrix.
    for (int i = 1; i <= N; i++)
        for (int j = i; j <= N; j++)
            a[i][j] = a[j][i] = ran0(&idum);

    printf("Random matrix:\n");
    for (int i = 1; i <= N; i++, printf("\n"))
        for (int j = 1; j <= N; j++)
            printf("%f ", a[i][j]);

    jacobi(a, 11, d, v, &nrot);
    eigsrt(d, v, N);

    printf("\nEigen vectors:\n");
    for (int i = 1; i <= N; i++, printf("\n"))
        for (int j = 1; j <= N; j++)
            printf("%f ", v[i][j]);

    printf("\nEigen values:\n");
    for (int i = 1; i <= N; i++)
        printf("%f ", d[i]);

    return 0;
}