#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x, double y, double z) {
    return sqrt(x * x + 1.1 * y * y) + z;
}

double g(double x, double y, double z) {
    return cos(2.1 * z) + y;
}

int main(void)
{
    double y0, x0, z0;
    printf("x0: ");
    scanf("%lf", &x0);
    printf("y(x0) = y0: ");
    scanf("%lf", &y0);
    printf("z(x0) = z0: ");
    scanf("%lf", &z0);

    double a = x0;

    double b;
    printf("b: ");
    scanf("%lf", &b);

    double h;
    printf("h: ");
    scanf("%lf", &h);

    double n = (b - a) / h;

    double x[(int)n], y1[(int)n], y2[(int)n], y3[(int)n], y4[(int)n], y[(int)n];
    double z1[(int)n], z2[(int)n], z3[(int)n], z4[(int)n], z[(int)n];

    y[0] = y0;
    z[0] = z0;

    for(int i = 1; i <= n; i++){
        x[i] = a + i * h;
        y1[i] = h * f(x[i - 1], y[i - 1], z[i - 1]);
        z1[i] = h * g(x[i - 1], y[i - 1], z[i - 1]);
        y2[i] = h * f(x[i - 1] + h / 2.0, y[i - 1] + y1[i] / 2.0,  z[i - 1] + z1[i] / 2.0);
        z2[i] = h * g(x[i - 1] + h / 2.0, y[i - 1] + y1[i] / 2.0,  z[i - 1] + z1[i] / 2.0);
        y3[i] = h * f(x[i - 1] + h / 2, y[i - 1] + y2[i] / 2, z[i - 1] + z2[i] / 2);
        z3[i] = h * g(x[i - 1] + h / 2, y[i - 1] + y2[i] / 2, z[i - 1] + z2[i] / 2);
        y4[i] = h * f(x[i - 1] + h, y[i - 1] + y3[i], y[i - 1] + z3[i]);
        z4[i] = h * g(x[i - 1] + h, y[i - 1] + y3[i], y[i - 1] + z3[i]);
        y[i] = y[i - 1] + (y1[i] + 2 * y2[i] + 2 * y3[i] + y4[i]) / 6;
        z[i] = z[i - 1] + (z1[i] + 2 * z2[i] + 2 * z3[i] + z4[i]) / 6;
    }

    for(int i = 0; i <= n; i++){
        printf("x[%d] = %f    ", i, x[i]);
        printf("y[%d] = %f    ", i, y[i]);
        printf("z[%d] = %f\n", i, z[i]);
    }
    return 0;
}
