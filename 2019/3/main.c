#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

int main(void)
{
    int n;
    scanf("%d", &n);
    double **a = (double **) calloc (n, sizeof(double *));
    double **b = (double **) calloc (n, sizeof(double *));
    double **c = (double **) calloc (n, sizeof(double *));
    for (int i = 0; i < n; i++) {
        a[i] = (double *) calloc (n, sizeof(double));
        b[i] = (double *) calloc (n, sizeof(double));
        c[i] = (double *) calloc (n, sizeof(double));
    }

    a = input(a, n);
    b = input(b, n);

    output(a, n);
    output(b, n);
    output(mul(a, b, c, n), n);
    output(add(a, b, c, n), n);
    output(mulonnum(a, c, n, 79), n);
    printf("%f\n", det(a, n));
    printf("%f\n", det(b, n));
    printf("%f\n", det(c, n));

    for (int i = 0; i < n; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);
    return 0;
}
