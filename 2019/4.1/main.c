#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double s = 0.0;

double trig(int n, double x) {
    if (n == 0) {
        return s;
    }
    s += sin(x);
    return trig(n - 1, sin(x));
}

int main(void)
{
    double x;
    int n;
    scanf("%d %lf", &n, &x);
    printf("%.10f\n", trig(n, x));
    return 0;
}
