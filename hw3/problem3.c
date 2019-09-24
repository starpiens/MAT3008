#include <math.h>
#include <stdio.h>
#include "nr.h"
#include "run_funcs.h"

float f3(float x) {
    return cos(x + sqrt(2)) + x * (x / 2 + sqrt(2));
}

void f3d(float x, float *y, float *dy) {
    *y = f3(x);
    *dy = x - sin(x + sqrt(2)) + sqrt(2);
}

void solve_problem3() {
    printf("===*** Problem 3 ***===\n");
    const float X1 = -2;
    const float X2 = -1;
    const float XACC = 1e-6;

    int num_roots = 1;
    float xb1[2] = {0, X1};
    float xb2[2] = {0, X2};

    run_type2(rtsafe, f3d, xb1, xb2, num_roots, XACC);
}