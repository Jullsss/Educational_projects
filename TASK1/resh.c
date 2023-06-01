#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    double eps;
    double norma;
    double w;

    double **a, *b, *x, *xn;
    int n;
    printf("Enter the number of equations: "); //������� ���������� ���������
    scanf("%d", &n);
    a = (double **) calloc (n + 1, sizeof(double *));
    for (int i = 0; i < n + 1; i++) {
        a[i] = (double *) calloc (n + 1, sizeof(double));
    }

    b = (double *) calloc (n + 1, sizeof(double));
    x = (double *) calloc (n + 1, sizeof(double));
    xn = (double *) calloc (n + 1, sizeof(double));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%lf", &a[i][j]);
        }
        scanf("%lf", &b[i]);
    }

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

    printf("Enter the precision: ");
    scanf("%lf", &eps);

    printf("Enter relaxation option w: ");
    scanf("%lf", &w);

    int count = 0; //���������� ��������
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
