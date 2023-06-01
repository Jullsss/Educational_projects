#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x, double y) {
    return (y - y * y) * x;
}

int main(void)
{
    double y0, x0;
    printf("x0: ");
    scanf("%lf", &x0);
    printf("y(x0) = y0: ");
    scanf("%lf", &y0);

    double a = x0;

    double b;
    printf("b: ");
    scanf("%lf", &b);

    double h;
    printf("h: ");
    scanf("%lf", &h);

    double n = (b - a) / h;

    double x[(int)n], y1[(int)n], y2[(int)n], y3[(int)n], y4[(int)n], y[(int)n];

    y[0] = y0;

    for(int i = 1; i <= n; i++){
        x[i] = a + i * h;
        y1[i] = h * f(x[i - 1], y[i - 1]);
        y2[i] = h * f(x[i - 1] + h / 2.0, y[i - 1] + y1[i] / 2.0);
        y3[i] = h * f(x[i - 1] + h / 2, y[i - 1] + y2[i] / 2);
        y4[i] = h * f(x[i - 1] + h, y[i - 1] + y3[i]);
        y[i] = y[i - 1] + (y1[i] + 2 * y2[i] + 2 * y3[i] + y4[i]) / 6;
    }

    for(int i = 0; i <= n; i++){
        printf("x[%d] = %f    ", i, x[i]);
        printf("y[%d] = %f\n", i, y[i]);
    }
    return 0;
}
