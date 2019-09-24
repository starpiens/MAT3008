#include <time.h>
#include <stdio.h>

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