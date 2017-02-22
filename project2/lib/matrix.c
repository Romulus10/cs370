float *multiply(float *x, float *y) {
    int i, j;
    float z[4];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            x[i][j] = z[j];
        }
    }
    return z;
}

int *multiply(int *x, int *y) {
    int i, j;
    int z[4];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            x[i][j] = z[j];
        }
    }
    return z;
}
