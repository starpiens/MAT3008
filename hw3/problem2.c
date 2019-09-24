#include <math.h>
#include <stdio.h>
#include "nr.h"
#include "run_funcs.h"

float f2(float x) {
    return exp(x) * x - 1;
}

void f2d(float x, float *y, float *dy) {
    *y = f2(x);
    *dy = exp(x) * (x + 1);
}

void solve_problem2() {
    printf("===*** Problem 2 ***===\n");
    const float X1 = 0;
    const float X2 = 1;
    const float XACC = 1e-6;

    int num_roots = 1;
    float xb1[2] = {0, X1};
    float xb2[2] = {0, X2};

    run_type2(rtsafe, f2d, xb1, xb2, num_roots, XACC);
}