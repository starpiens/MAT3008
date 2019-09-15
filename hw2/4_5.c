#include <stdio.h>
#include <math.h>

const int MAX_LEN = 5;
typedef struct Polynomial {
  int c[MAX_LEN];
} Polynomial;

void differentiate(Polynomial *f) {
    for (int i = 0; i < MAX_LEN - 1; i++) {
        f->c[i] = f->c[i + 1] * (i + 1);
    }
}

int get_y(Polynomial *f, int x) {
    int ans = 0;
    for (int i = 0; i < MAX_LEN; i++) {
        int term = 1;
        for (int j = 0; j < i; j++)
            term *= x;
        ans += term * f->c[i];
    }
    return ans;
}

void solve_4_5() {
    const int x = 3;
    const int a = 1;
    const int steps = 3;
    Polynomial f = {{-88, 7, -6, 25}};

    printf("========== Problem 4.5 ==========\n");
    double true_val = get_y(&f, x);
    printf("True value: %f\n", true_val);

    double sum = 0;
    int fac = 1;
    for (int i = 0; i <= steps; i++) {
        double term = get_y(&f, a);
        for (int j = 0; j < i; j++)
            term *= (x - a);
        term /= fac;
        sum += term;
        printf("Step #%d: estimated %f, relative err %f%%\n",
                i + 1,
                sum,
                fabs(true_val - sum) * 100 / true_val);
        differentiate(&f);
        fac *= i + 1;
    }
    printf("\n");
}