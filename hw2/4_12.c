#include <stdio.h>
#include <math.h>

void solve_4_12() {
    double g = 9.81;
    double t = 6;
    double c = 12.5;
    double dc = 1.5;
    double m = 50;
    double dm = 2;

    double v_dc = -g*m/(c*c) * (1-exp(-t*c/m)) - g*t/c * -exp(-t*c/m);
    double v_dm = (1 - (c*t/m+1)*exp(-c*t/m)) * g/c;
    double delta_v = fabs(v_dc) * dc + fabs(v_dm) * dm;
    double v = g*m*(1-exp(-c*t/m))/c;

    printf("========== Problem 4.12 ==========\n");
    printf("Estimated v: %f ± %f\n", v, delta_v);
}