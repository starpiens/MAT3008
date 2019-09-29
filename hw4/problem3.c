#include <stdio.h>
#include <math.h>
#include "run_funcs.h"

float f3(float R) {
    return -0.20597 + 1.671e-4 * R + 9.7215e-8 * pow(R, 2) - 9.5838e-11 * pow(R, 3) + 1.9520e-14 * pow(R, 4);
}

void df3(float R, float *y, float *dy) {
    *y = f3(R);
    *dy = 1.671e-4 + 9.7215e-8 * 2 * R - 9.5838e-11 * 3 * pow(R, 2) + 1.9520e-14 * 4 * pow(R, 3);
}

void solve_problem3() {
    printf("========== Problem 3 ==========\n");\

    run_rtbis(f3, 1000, 1500, 1e-4);
    run_rtflsp(f3, 1000, 1500, 1e-4);
    run_rtsec(f3,1000, 1500, 1e-4);
    run_rtnewt(df3, 1000, 1500, 1e-4);
    run_rtsafe(df3, 1000, 1500, 1e-4);
}