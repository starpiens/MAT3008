#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nrutil.h"

typedef struct {
  float x;
  float y;
  float xp;
  float yp;
} Data;

typedef struct {
  Data *data;
  size_t size;
  size_t _capacity;
} Datalist;

Datalist *read_data(const char *filename) {
    FILE *ifp = fopen(filename, "r");
    if (ifp == NULL) {
        fprintf(stderr, "Failed to open file %s\n", filename);
        exit(1);
    }

    Datalist *datalist = malloc(sizeof(Datalist));
    datalist->data = malloc(sizeof(Data));
    datalist->size = 0;
    datalist->_capacity = 1;
    Data *d = datalist->data;
    while(fscanf(ifp, "%f %f %f %f", &d->x, &d->y, &d->xp, &d->yp) == 4) {
        if (++datalist->size == datalist->_capacity) {
            datalist->_capacity *= 2;
            datalist->data = realloc(datalist->data, sizeof(Data) * (datalist->_capacity));
        }
        d = &datalist->data[datalist->size];
    }

    fclose(ifp);
    return datalist;
}

void free_datalist(Datalist *datalist) {
    free(datalist->data);
    free(datalist);
}

// Compute 'a' which satisfies F^t * F * a = F^t * y.
// F: N * M matrix
// y: N * K matrix
// a: M * K matrix
float **fit(float **F, float **y, int N, int M, int K) {
    float **Ft_F = matrix(1, M, 1, M);
    float **Ft_y = matrix(1, M, 1, K);
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= M; j++) {
            Ft_F[i][j] = 0;
            for (int k = 1; k <= N; k++)
                Ft_F[i][j] += F[k][i] * F[k][j];
        }
    }
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= K; j++) {
            Ft_y[i][j] = 0;
            for (int k = 1; k <= N; k++)
                Ft_y[i][j] += F[k][i] * y[k][j];
        }
    }

    void gaussj(float **a, int n, float **b, int m);
    gaussj(Ft_F, M, Ft_y, K);

    free_matrix(Ft_F, 1, M, 1, M);
    return Ft_y;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <data_file>\n", argv[0]);
        exit(1);
    }
    Datalist *datalist = read_data(argv[1]);

    int N = datalist->size;
    int M = 3;
    int K = 2;
    float **F = matrix(1, N, 1, M);
    float **y = matrix(1, N, 1, K);
    for (int i = 1; i <= N; i++) {
        F[i][1] = datalist->data[i - 1].x;
        F[i][2] = datalist->data[i - 1].y;
        F[i][3] = 1;
        y[i][1] = datalist->data[i - 1].xp;
        y[i][2] = datalist->data[i - 1].yp;
    }
    float **a = fit(F, y, N, M, K);
    for (int i = 1; i <= K; i++)
        for (int j = 1; j <= M; j++)
            printf("a_%d: %f\n", (i - 1) * M + j, a[j][i]);

    free_matrix(F, 1, N, 1, M);
    free_matrix(y, 1, N, 1, K);
    free_matrix(a, 1, M, 1, K);
    free_datalist(datalist);
    return 0;
}