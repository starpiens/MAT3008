#include <stdio.h>
#include "nr.h"
#include "run_funcs.h"

void bessj0d(float x, float *y, float *dy) {
    *y = bessj0(x);
    *dy = -bessj1(x);
}

void solve_problem0() {
    printf("===*** Problem 0 ***===\n\n");

    const float X1 = 1.0;
    const float X2 = 10.0;
    const float XACC = 1e-6;
    const int MAX_ROOTS = 100;
    const int NUM_BRACKETS = 1e5;

    int num_roots = MAX_ROOTS;
    float xb1[MAX_ROOTS], xb2[MAX_ROOTS];
    zbrak(bessj0, X1, X2, NUM_BRACKETS, xb1, xb2, &num_roots);

    printf("=== Bisection method ===\n");
    run_type1(rtbis, bessj0, xb1, xb2, num_roots, XACC);

    printf("=== Linear interpolation ===\n");
    run_type1(rtflsp, bessj0, xb1, xb2, num_roots, XACC);

    printf("=== Secant method ===\n");
    run_type1(rtsec, bessj0, xb1, xb2, num_roots, XACC);

    printf("=== Newton-Raphson ===\n");
    run_type2(rtnewt, bessj0d, xb1, xb2, num_roots, XACC);

    printf("=== Newton with bracketing ===\n");
    run_type2(rtsafe, bessj0d, xb1, xb2, num_roots, XACC);
}