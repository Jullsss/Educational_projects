#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    double **a, **b;
    int n;
    printf("Enter the number of equations: "); //������� ���������� ���������
    scanf("%d", &n);
    a = (double **) calloc (n, sizeof(double *));
    for (int i = 0; i < 2 * n; i++) {
        a[i] = (double *) calloc (n, sizeof(double));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &a[i][j]); //������� �������� ������� a
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
            printf("%f ", a[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i <= n; i++) {
        free(a[i]);
    }
    free(a);
    return 0;
}
