#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    double **a, *b, *x;
    double eps;  // ��������
    int n;
    printf("Enter the number of equations: "); //������� ���������� ���������
    scanf("%d", &n);
    a = (double **) calloc (n + 1, sizeof(double *));
    for (int i = 0; i < n + 1; i++) {
        a[i] = (double *) calloc (n + 1, sizeof(double));
    }

    b = (double *) calloc (n + 1, sizeof(double));
    x = (double *) calloc (n + 1, sizeof(double));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%lf", &a[i][j]); //������� �������� ������� a
        }
        scanf("%lf", &b[i]); //������� ������� ��������
    }

    printf("Enter the precision: "); //������� ��������
    scanf("%lf", &eps);

    printf("\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%.0f * x[%d]", a[i][j], j);
            if (j < n) {
                printf(" + ");
            }
        }
        printf(" = %.0f\n", b[i]);
    }
    printf("\n");

    double max;
    int k = 1, index;

    while (k <= n)
    {
        // ������������ ���������
        for (int i = k; i <= n; i++) {
            double temp = a[i][k];
            if (fabs(temp) < eps) {
                continue; // ��� �������� ������������ ����������
            }
            for (int j = 1; j <= n; j++) {
                a[i][j] /= temp;
            }
            b[i] /= temp;

            if (i == k) {
                continue;
            }

            for (int j = 1; j <= n; j++) {
                a[i][j] -= a[k][j];
            }
            b[i] -= b[k];
        }
        k++;
    }

    // �������� �����������
    for (k = n; k >= 1; k--) {
        x[k] = b[k];
        for (int i = 1; i <= k; i++) {
            b[i] -= a[i][k] * x[k];
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("x[%d] = %f\n", i, x[i]);
    }

    for (int i = 0; i <= n; i++) {
        free(a[i]);
    }
    free(a);
    free(b);
    free(x);
    return 0;
}
