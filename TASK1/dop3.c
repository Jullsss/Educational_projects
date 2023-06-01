#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    double **a;
    int n;
    printf("Enter the number of equations: "); //¬ведите количество уравнений
    scanf("%d", &n);
    a = (double **) calloc (n + 1, sizeof(double *));
    for (int i = 0; i < n + 1; i++) {
        a[i] = (double *) calloc (n + 1, sizeof(double));
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%lf", &a[i][j]); //¬ведите элементы матрицы a
        }
    }

    double tmp = 1;
    double det = 1;
    for (int j = 1; j <= n; j++) {
        for (int i = j + 1; i <= n;i++) {
            tmp = a[i][j] / a[j][j];
            for (int l = 1; l <= n; l++) {
                a[i][l] -= a[j][l] * tmp;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        det *= a[i][i];
    }
    printf("%f", det);

    for (int i = 1; i <= n; i++) {
        free(a[i]);
    }
    free(a);
    return 0;
}

