#include <stdlib.h>

double *multiply(double **x, double *y) {
    int i, j;
    static double z[4] = {0, 0, 0, 0};
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            x[i][j] = z[j];
        }
    }
    return z;
}
