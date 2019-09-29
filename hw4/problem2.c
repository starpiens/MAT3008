#include <stdio.h>
#include <math.h>
#include "run_funcs.h"

float f2(float R) {
    return pow(R*R + .9*.9, 1.5) / R - 100 / (8.85 * M_PI);
}

void df2(float R, float *y, float *dy) {
    *y = f2(R);
    float tmp = R * R + .9 * .9;
    *dy = 3 * pow(tmp, 0.5) - pow(tmp, 1.5) / R / R;
}

void solve_problem2() {
    printf("========== Problem 2 ==========\n");\

    run_rtbis(f2, .2, .25, 1e-4);
    run_rtflsp(f2, .2, .25, 1e-4);
    run_rtsec(f2, .2, .25, 1e-4);
    run_rtnewt(df2, .2, .25, 1e-4);
    run_rtsafe(df2, .2, .25, 1e-4);

    run_rtbis(f2, 1, 2, 1e-4);
    run_rtflsp(f2, 1, 2, 1e-4);
    run_rtsec(f2,1, 2, 1e-4);
    run_rtnewt(df2, 1, 2, 1e-4);
    run_rtsafe(df2, 1, 2, 1e-4);
}