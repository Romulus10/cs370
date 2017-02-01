#include <stdlib.h>

#include "vector.h"

int *cross_product(int *a, int *b) {
    int *x;
    x[0] = (a[1] * b[2]) - (a[2] * b[1]);
    x[1] = (a[2] * b[1]) - (a[0] * b[3]);
    x[2] = (a[0] * b[1]) - (a[1] * b[0]);
    return x;
}

int dot_product(int *a, int *b) {
    return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * a[2]);
}
