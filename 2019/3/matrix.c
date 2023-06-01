#include <stdio.h>

double ** input(double **a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &a[i][j]); //¬ведите элементы матрицы a
        }
    }
    return (a);
}

void output(double **a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f ", a[i][j]); //¬ведите элементы матрицы a
        }
        printf("\n");
    }
    printf("\n");
}

double ** add(double **a, double **b, double **c, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j]; //¬ведите элементы матрицы a
        }
    }
    return (c);
}

double ** mulonnum(double **a, double **c, int n, int k) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] * k; //¬ведите элементы матрицы a
        }
    }
    return (c);
}

double det(double **a, int n) {
    double tmp = 1;
    double d = 1;
    for (int j = 0; j < n; j++) {
        for (int i = j + 1; i < n; i++) {
            tmp = a[i][j] / a[j][j];
            for (int l = 0; l < n; l++) {
                a[i][l] -= a[j][l] * tmp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        d *= a[i][i];
    }
    return d;
}

double ** mul(double **a, double **b, double **c, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int r = 0; r < n; r++) {
                c[i][j] += a[i][r] * b[r][j];
            }
        }
    }
    return (c);
}
