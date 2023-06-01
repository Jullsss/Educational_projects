#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double p(double x){
    return -3 * x;
}

double q(double x){
    return 2;
}

double f(double x){
    return 1.5;
}

void resh(double **a, double *b, double *x1, int n) {
    double d1[n], d2[n], d3[n], k;

    d1[0] = 0; d3[n] = 0;
    for (int i = 0; i < n; i++){
        d2[i] = a[i][i];
        if (i != n - 1) {
            d3[i] = a[i][i + 1];
        }
        if (i != 0) {
            d1[i] = a[i][i - 1];
        }
    }

    for (int i = 1; i < n; i++){
        k = d1[i] / d2[i - 1];
        d2[i] -= k * d3[i - 1];
        b[i] -= k * b[i - 1];
    }

    x1[n - 1] = b[n - 1] / d2[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        x1[i] = (b[i] - d3[i] * x1[i + 1]) / d2[i];
    }
}


int main(void) {
    double alpha0 = 0; double alpha1 = 1; double ac = 1.3;
    double beta0 = 0.5; double beta1 = 1; double bc = 2;
    double a0 = 0.7; double b0 = 1;

    int n;
    printf("Enter the number of equations: "); //Введите количество уравнений
    scanf("%d", &n);

    double **a = (double **) calloc (n + 1, sizeof(double *));
    for (int i = 0; i < n + 1; i++) {
        a[i] = (double *) calloc (n + 1, sizeof(double));
    }
    double *b = (double *) calloc (n + 1, sizeof(double));
    double *x = (double *) calloc (n + 1, sizeof(double));

    double h = (b0 - a0) / n;

    for (int i = 0; i <= n; i++){
        x[i] = a0 + i * h;
    }

    printf("h = %f\n", h);

    a[0][0] = alpha0 * h - alpha1;
    a[0][1] = alpha1;
    for(int i = 0; i <= n - 2; i++){
        a[i + 1][i] = h * h * q(x[i + 1]) - h * p(x[i + 1]) + 1;
        a[i + 1][i + 1] = h * p(x[i + 1]) - 2;
        a[i + 1][i + 2] = 1;
        b[i + 1] = h * h * f(x[i + 1]);
    }
    a[n][n - 1] = -beta1;
    a[n][n] = beta0 * h + beta1;
    b[n - 1] = h * ac;
    b[n] = h * bc;

    printf("\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%f ", a[i][j]);
        }
        printf("|| %f\n", b[i]);
    }
    printf("\n");

    double *x1 = (double *) calloc (n + 1, sizeof(double));
    resh(a, b, x1, n + 1);

    for (int i = 1; i <= n; i++) {
        printf("x[%d] = %f || y[%d] = %f\n", i, x[i], i, x1[i]);
    }
    return 0;
}


