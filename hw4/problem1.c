#include <stdio.h>
#include <math.h>
#include "nr.h"

float f(float R) {
    return exp(-0.005 * R) * cos(sqrt(2000 - R * R * 0.01) * 0.05) - 0.01;
}

void df(float R, float *y, float *dy) {
    *y = f(R);
    float tmp = sqrt(2000 - R * R * 0.01) * 0.05;
    *dy = exp(-0.005 * R) * (sin(tmp) / tmp - cos(tmp)) * 0.005;
}

void run_rtsafe(float x1, float x2, float xacc) {
    int num_iter;
    printf("Finding a root using rtsafe in range [%.1e, %.1e], accuracy %.1e\n", x1, x2, xacc);
    printf("Estimated value: %.10f\n", rtsafe(df, x1, x2, xacc, &num_iter));
    printf("Number of iterations: %d\n\n", num_iter);
}

void run_rtbis(float x1, float x2, float xacc) {
    int num_iter;
    printf("Finding a root using rtbis in range [%.1e, %.1e], accuracy %.1e\n", x1, x2, xacc);
    printf("Estimated value: %.10f\n", rtbis(f, x1, x2, xacc, &num_iter));
    printf("Number of iterations: %d\n\n", num_iter);
}

void run_rtnewt(float x1, float x2, float xacc) {
    int num_iter;
    printf("Finding a root using rtnewt in range [%.1e, %.1e], accuracy %.1e\n", x1, x2, xacc);
    printf("Estimated value: %.10f\n", rtbis(f, x1, x2, xacc, &num_iter));
    printf("Number of iterations: %d\n\n", num_iter);
}

void solve_problem1() {
    printf("========== Problem 1 ==========\n");
    int num_iter;
    float x1, x2, xacc;

    run_rtbis(0, 400, 1e-4);
    run_rtnewt(0, 400, 1e-4);
    run_rtsafe(0, 400, 1e-4);

    run_rtbis(0, 400, 1e-6);
    run_rtnewt(0, 400, 1e-6);
    run_rtsafe(0, 400, 1e-6);
}