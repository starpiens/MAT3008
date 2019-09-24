#include <math.h>
#include <stdio.h>
#include "nr.h"
#include "run_funcs.h"

float f1(float x) {
    return 10 * exp(-x) * sin(2 * M_PI * x) - 2;
}

void f1d(float x, float *y, float *dy) {
    *y = f1(x);
    *dy = 10 * exp(-x) * (2 * M_PI * cos(2 * M_PI * x) - sin(2 * M_PI * x));
}

void solve_problem1() {
    printf("===*** Problem 1 ***===\n");

    const float X1 = 0.1;
    const float X2 = 1;
    const float XACC = 1e-6;

    int num_roots = 1;
    float xb1[2] = {0, X1};
    float xb2[2] = {0, X2};

    run_type2(rtsafe, f1d, xb1, xb2, num_roots, XACC);
}