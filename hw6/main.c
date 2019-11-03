#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

float ran0(long *idum);
float gasdev(long *idum);

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;

    int n = atoi(argv[1]);

    if (strcmp(argv[2], "uniform") == 0) {
        long long idum = time(NULL);
        for (int i = 0; i < n; i++)
            printf("%f ", ran0(&idum));

    } else if (strcmp(argv[2], "gaussian") == 0) {
        long long idum = time(NULL);
        for (int i = 0; i < n; i++)
            printf("%f ", gasdev(&idum));
    } else return 1;

    return 0;
}