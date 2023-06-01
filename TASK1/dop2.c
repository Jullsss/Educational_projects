#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    const double q = 0.995;
    double eps;
    double norma;
    double w;

    double **a, *b, *x, *xn;
    int n = 30;
    printf("The number of equations: 30\n");

    a = (double **) calloc (n + 1, sizeof(double *));
    for (int i = 0; i < n + 1; i++) {
        a[i] = (double *) calloc (n + 1, sizeof(double));
    }

    b = (double *) calloc (n + 1, sizeof(double));
    x = (double *) calloc (n + 1, sizeof(double));
    xn = (double *) calloc (n + 1, sizeof(double));

    double t;
    printf("Enter x: ");
    scanf("%lf", &t);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                a[i][j] = pow(q - 1, i + j);
            } else {
                a[i][j] = pow(q, i + j) + 0.1 * (j - i);
            }
        }
        b[i] = t * exp (t / i) * cos (t / i);
    }

    printf("Enter the precision: ");
    scanf("%lf", &eps);

    printf("Enter relaxation option w: ");
    scanf("%lf", &w);

    int count = 0; //Количество итераций
    norma = 1;

    for (int i = 1; i <= n; i++) {
        xn[i] = 1;
        x[i] = xn[i];
    }
    while (norma > eps) {
        count++;
        norma = 0;
        for (int i = 1; i <= n; i++) {
            x[i] = b[i];
            for (int j = 1; j <= n; j++) {
                if (i != j) {
                    x[i] = x[i] - a[i][j] * x[j];
                }
            }
            x[i] /= a[i][i];

            x[i] = w * x[i] + (1 - w) * xn[i];

            if (fabs(x[i] - xn[i]) > norma) {
                norma = fabs(x[i] - xn[i]);
            }
            xn[i] = x[i];
        }
    }
    printf("Number of iterations: ");
    printf("%d\n", count);

    for (int i = 1; i <= n; i++) {
        printf("x[%d] = %f\n", i, x[i]);
    }

    for (int i = 0; i < n + 1; i++) {
        free(a[i]);
    }
    free(a);
    free(b);
    free(x);
    return 0;
}
