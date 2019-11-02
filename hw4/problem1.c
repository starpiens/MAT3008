#include <stdio.h>
#include <math.h>
#include "run_funcs.h"

float f1(float R) {
    return exp(-0.005 * R) * cos(sqrt(2000 - R * R * 0.01) * 0.05) - 0.01;
}

void df1(float R, float *y, float *dy) {
    *y = f1(R);
    float tmp = sqrt(2000 - R * R * 0.01) * 0.05;
    *dy = exp(-0.005 * R) * (sin(tmp) / tmp - cos(tmp)) * 0.005;
}

void solve_problem1() {
    printf("========== Problem 1 ==========\n");

    run_rtbis(f1, 0, 400, 1e-4);
    run_rtflsp(f1, 0, 400, 1e-4);
    run_rtsec(f1, 0, 400, 1e-4);
    run_rtsafe(df1, 0, 400, 1e-4);

    run_rtbis(f1, 0, 400, 1e-6);
    run_rtflsp(f1, 0, 400, 1e-6);
    run_rtsec(f1, 300, 400, 1e-6);
    run_rtsafe(df1, 0, 400, 1e-6);
}