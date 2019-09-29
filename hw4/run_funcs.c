#include "run_funcs.h"
#include <stdio.h>

void run_rtbis(float (*f)(float), float x1, float x2, float xacc) {
    int num_iter;
    printf("Finding a root using rtbis in range [%.1e, %.1e], accuracy %.1e\n", x1, x2, xacc);
    printf("Estimated value: %.10f\n", rtbis(f, x1, x2, xacc, &num_iter));
    printf("Number of iterations: %d\n\n", num_iter);
}

void run_rtflsp(float (*f)(float), float x1, float x2, float xacc) {
    int num_iter;
    printf("Finding a root using rtflsp in range [%.1e, %.1e], accuracy %.1e\n", x1, x2, xacc);
    printf("Estimated value: %.10f\n", rtflsp(f, x1, x2, xacc, &num_iter));
    printf("Number of iterations: %d\n\n", num_iter);
}

void run_rtsec(float (*f)(float), float x1, float x2, float xacc) {
    int num_iter;
    printf("Finding a root using rtsec in range [%.1e, %.1e], accuracy %.1e\n", x1, x2, xacc);
    printf("Estimated value: %.10f\n", rtsec(f, x1, x2, xacc, &num_iter));
    printf("Number of iterations: %d\n\n", num_iter);
}

void run_rtnewt(void (*df)(float, float *, float *), float x1, float x2, float xacc) {
    printf("Finding a root using rtnewt in range [%.1e, %.1e], accuracy %.1e\n", x1, x2, xacc);
    int num_iter;
    printf("Estimated value: %.10f\n", rtnewt(df, x1, x2, xacc, &num_iter));
    printf("Number of iterations: %d\n\n", num_iter);
}

void run_rtsafe(void (*df)(float, float *, float *), float x1, float x2, float xacc) {
    int num_iter;
    printf("Finding a root using rtsafe in range [%.1e, %.1e], accuracy %.1e\n", x1, x2, xacc);
    printf("Estimated value: %.10f\n", rtsafe(df, x1, x2, xacc, &num_iter));
    printf("Number of iterations: %d\n\n", num_iter);
}
