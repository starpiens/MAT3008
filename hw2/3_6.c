#include <stdio.h>

double neg_exp(int n, int num_iter, int method) {
    double ans = 1, term = 1;
    for (int i = 1; i < num_iter; i++) {
        if (method == 1) term *= -1;
        term *= (double)n / i;
        ans += term;
    }
    if (method == 1)
        return ans;
    else
        return 1 / ans;
}

void solve_3_6() {
    printf("========== Problem 3.6 ==========\n");
    double true_val = 6.737947e-3;
    for (int i = 1; i <= 2; i++) {
        printf("Method #%d\n", i);
        double aprx_val = neg_exp(5, 20, i);
        printf("Approximate value: %e\n", aprx_val);
        printf("Relative error:    %e\n", (true_val - aprx_val) / true_val);
        printf("\n");
    }
}