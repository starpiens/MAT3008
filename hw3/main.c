#include <stdio.h>
#include "nr.h"

void bessj0d(float x, float *y, float *dy) {
    *y = bessj0(x);
    *dy = -bessj1(x);
}

int main() {
    const float X1 = 1.0;
    const float X2 = 10.0;
    const float XACC = 1e-6;

    printf("=== Bracketing method ===\n");
    int num_roots = 100;
    float xb1[100], xb2[100];
    zbrak(bessj0, X1, X2, 1e5, xb1, xb2, &num_roots);
    printf("Root%s found in %d interval%s: \n",
           num_roots > 1 ? "s" : "",
           num_roots,
           num_roots > 1 ? "s" : "");
    for (int i = 1; i <= num_roots; i++)
        printf("#%d: [%.10f, %.10f]\n", i, xb1[i], xb2[i]);
    printf("\n");

    printf("=== Bisection method ===\n");
    for (int i = 1; i <= num_roots; i++)
        printf("#%d: %.10f\n", i, rtbis(bessj0, xb1[i], xb2[i], XACC));
    printf("\n");

    printf("=== Linear interpolation ===\n");
    for (int i = 1; i <= num_roots; i++)
        printf("#%d: %.10f\n", i, rtflsp(bessj0, xb1[i], xb2[i], XACC));
    printf("\n");

    printf("=== Secant method ===\n");
    for (int i = 1; i <= num_roots; i++)
        printf("#%d: %.10f\n", i, rtsec(bessj0, xb1[i], xb2[i], XACC));
    printf("\n");

    printf("=== Newton-Raphson ===\n");
    for (int i = 1; i <= num_roots; i++)
        printf("#%d: %.10f\n", i, rtnewt(bessj0d, xb1[i], xb2[i], XACC));
    printf("\n");

    printf("=== Newton with bracketing ===\n");
    for (int i = 1; i <= num_roots; i++)
        printf("#%d: %.10f\n", i, rtsafe(bessj0d, xb1[i], xb2[i], XACC));
    printf("\n");

    return 0;
}