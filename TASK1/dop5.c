#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    double **a, **b, **x;
    int n;
    printf("Enter the number of equations: "); //������� ���������� ���������
    scanf("%d", &n);
    a = (double **) calloc (n, sizeof(double *));
    b = (double **) calloc (n, sizeof(double *));
    x = (double **) calloc (n, sizeof(double *));
    for (int i = 0; i < 2 * n; i++) {
        a[i] = (double *) calloc (n, sizeof(double));
        b[i] = (double *) calloc (n, sizeof(double));
        x[i] = (double *) calloc (n, sizeof(double));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &a[i][j]); //������� �������� ������� a
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            x[i][j] = a[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = n; j < 2 * n; j++) {
            if (i == (j - n)) {
                a[i][j] = 1;
            } else {
                a[i][j] = 0;
            }
        }
    }
    double tmp = 1;
    for (int j = 0; j < n; j++) {
        for (int i = j + 1; i < n;i++) {
            tmp = a[i][j] / a[j][j];
            for (int l = 0; l < 2 * n; l++) {
                a[i][l] -= a[j][l] * tmp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        tmp = a[i][i];
        for (int j = 0; j < 2 * n; j++){
            a[i][j] /= tmp;
        }
    }
    for (int j = n - 1; j >= 1; j--) {
        for (int i = j - 1; i >= 0; i--) {
            tmp = a[i][j];
            for (int k = 0; k < 2 * n; k++) {
                a[i][k] -= a[j][k] * tmp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = n; j < 2 * n; j++) {
            b[i][j - n] = a[i][j];
        }
    }

    double max1 = 0, max2 = 0;
    for (int i = 0; i < n; i++) {
        tmp = 0;
        for (int j = 0; j < n; j++) {
            tmp += fabs(x[i][j]);
        }
        if (tmp > max1) {
            max1 = tmp;
        }
    }
    for (int i = 0; i < n; i++) {
        tmp = 0;
        for (int j = 0; j < n; j++) {
            tmp += fabs(b[i][j]);
        }
        if (tmp > max2) {
            max2 = tmp;
        }
    }
    tmp = max1 * max2;
    printf("%f\n", tmp);

    for (int i = 0; i <= n; i++) {
        free(a[i]);
        free(b[i]);
        free(x[i]);
    }
    free(a);
    free(b);
    free(x);
    return 0;
}
