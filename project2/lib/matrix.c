#include <stdio.h>
#include <stdlib.h>

double *multiply(double x[4][4], double *y) {
    int i, j;
    static double z[4] = {0, 0, 0, 0};
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%f", x[i][j]);
            printf("%f", y[j]);
            z[j] += (x[i][j] * y[j]);
        }
    }
    return z;
}
