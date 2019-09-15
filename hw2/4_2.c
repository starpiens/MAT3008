#include <stdio.h>
#include <math.h>

void solve_4_2() {
    printf("========== Problem 4.2 ==========\n");
    double sum = 1, term = 1;
    for (int i = 1; sum != .5; i++) {
        term *= -M_PI * M_PI / ((2 * i - 1) * (2 * i)) / 9;
        sum += term;
        printf("Step #%d: estimated %e, relative err %f%%\n", i, sum, fabs(.5 - sum) * 100 / sum);
    }
    printf("\n");
}