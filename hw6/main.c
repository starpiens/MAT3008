#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

float ran0(long *idum);

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;
    int n = atoi(argv[2]);

    if (strcmp(argv[1], "uniform") == 0) {
        if (argc < 5) return 1;
        int a = atoi(argv[3]);
        int b = atoi(argv[4]);
        long long idum = time(NULL);
        for (int i = 0; i < n; i++)
            printf("%f ", ran0(&idum) * (b - a) + a);

    } else if (strcmp(argv[1], "gauss") == 0) {

    }

    return 0;
}