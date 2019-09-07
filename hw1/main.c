#include <stdio.h>
#include <math.h>

void machar(int *ibeta, int *it, int *irnd, int *ngrd, int *machep, int *negep,
            int *iexp, int *minexp, int *maxexp, float *eps, float *epsneg,
            float *xmin, float *xmax);

float get_eps_float() {
    float eps = 1;
    while (1 + eps != 1)
        eps /= 2;
    return eps * 2;
}

double get_eps_double() {
    double eps = 1;
    while (1 + eps != 1)
        eps /= 2;
    return eps * 2;
}

int main() {
    // Method 1
    printf("Method #1\n");
    int ibeta, it, irnd, ngrd, machep, negep, iexp, minexp, maxexp;
    float eps, epsneg, xmin, xmax;
    machar(&ibeta, &it, &irnd, &ngrd, &machep, &negep, &iexp, &minexp, &maxexp, &eps, &epsneg, &xmin, &xmax);
    printf("Epsilon of float:  %g (%.23f)\n", eps, eps);
    printf("\n");

    // Method 2
    printf("Method #2\n");
    float eps_float = get_eps_float();
    double eps_double = get_eps_double();
    printf("Epsilon of float:  %g (%.23f)\n", eps_float, eps_float);
    printf("Epsilon of double: %g (%.52f)\n", eps_double, eps_double);
    return 0;
}