#include <stdio.h>
#include "nr.h"
#include <time.h>

void bessj0d(float x, float *y, float *dy) {
    *y = bessj0(x);
    *dy = -bessj1(x);
}

void run_type1(float (*method)(float (*func)(float), float, float, float),
               float (*func)(float),
               float *xb1,
               float *xb2,
               int num_roots,
               float xacc) {
    time_t start_time, end_time, total_time;
    total_time = 0;
    for (int i = 1; i <= num_roots; i++) {
        start_time = clock();
        float root = (*method)(func, xb1[i], xb2[i], xacc);
        end_time = clock();
        total_time += end_time - start_time;
        printf("#%d: %.10f\n", i, root);
    }
    printf("Time elapsed: %ldus\n\n", total_time * (int)1e6 / CLOCKS_PER_SEC);
}

void run_type2(float (*method)(void (*func)(float, float *, float *), float, float, float),
               void (*func)(float, float *, float *),
               float *xb1,
               float *xb2,
               int num_roots,
               float xacc) {
    time_t start_time, end_time, total_time;
    total_time = 0;
    for (int i = 1; i <= num_roots; i++) {
        start_time = clock();
        float root = (*method)(func, xb1[i], xb2[i], xacc);
        end_time = clock();
        total_time += end_time - start_time;
        printf("#%d: %.10f\n", i, root);
    }
    printf("Time elapsed: %ldus\n\n", total_time * (int)1e6 / CLOCKS_PER_SEC);
}

int main() {
    const float X1 = 1.0;
    const float X2 = 10.0;
    const float XACC = 1e-6;
    time_t start_time, end_time, total_time;

    printf("=== Bracketing method ===\n");
    int num_roots = 100;
    float xb1[100], xb2[100];
    start_time = clock();
    zbrak(bessj0, X1, X2, 1e5, xb1, xb2, &num_roots);
    end_time = clock();
    total_time = end_time - start_time;
    printf("Root%s found in %d interval%s: \n",
           num_roots > 1 ? "s" : "",
           num_roots,
           num_roots > 1 ? "s" : "");
    for (int i = 1; i <= num_roots; i++)
        printf("#%d: [%.10f, %.10f]\n", i, xb1[i], xb2[i]);
    printf("Time elapsed: %ldus\n\n", total_time * (int)1e6 / CLOCKS_PER_SEC);

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

    return 0;
}