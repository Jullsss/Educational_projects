#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    double n1, n2, n3;
    double i1, i2;
    printf("n1: ");
    scanf("%lf", &n1);
    printf("i1: ");
    scanf("%lf", &i1);
    printf("i2: ");
    scanf("%lf", &i2);
    n2 = n1 / i1;
    n3 = n2 / i2;
    printf("n2: %.3f\nn3: %.3f\n", n2, n3);
    return 0;
}
