#include <stdio.h>

void machar(int *ibeta, int *it, int *irnd, int *ngrd, int *machep, int *negep,
            int *iexp, int *minexp, int *maxexp, float *eps, float *epsneg,
            float *xmin, float *xmax);

void machar_double(int *ibeta, int *it, int *irnd, int *ngrd, int *machep, int *negep,
                   int *iexp, int *minexp, int *maxexp, double *eps, double *epsneg,
                   double *xmin, double *xmax);

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
    printf("Machine epsilon by machar():\n");
    int ibeta, it, irnd, ngrd, machep, negep, iexp, minexp, maxexp;
    float f_eps_1, f_epsneg, f_xmin, f_xmax;
    machar(&ibeta, &it, &irnd, &ngrd, &machep, &negep, &iexp, &minexp, &maxexp,
            &f_eps_1, &f_epsneg, &f_xmin, &f_xmax);
    printf("Epsilon of float:  %g (%.23f)\n", f_eps_1, f_eps_1);
    double d_eps_1, d_epsneg, d_xmin, d_xmax;
    machar_double(&ibeta, &it, &irnd, &ngrd, &machep, &negep, &iexp, &minexp, &maxexp,
            &d_eps_1, &d_epsneg, &d_xmin, &d_xmax);
    printf("Epsilon of double: %g (%.52f)\n", d_eps_1, d_eps_1);
    printf("\n");

    // Method 2
    printf("Machine epsilon by get_eps():\n");
    float f_eps_2 = get_eps_float();
    double d_eps_2 = get_eps_double();
    printf("Epsilon of float:  %g (%.23f)\n", f_eps_2, f_eps_2);
    printf("Epsilon of double: %g (%.52f)\n", d_eps_2, d_eps_2);
    printf("\n");

    printf("Difference: \n");
    printf("Epsilon of float:  %.23f\n", f_eps_1 - f_eps_2);
    printf("Epsilon of double: %.52f\n", d_eps_1 - d_eps_2);
    return 0;
}