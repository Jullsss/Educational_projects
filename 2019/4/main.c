#include <stdio.h>
#include <stdlib.h>

int factorial(int x, int fac) {
    if (x <= 1) {
        return fac;
    }
    fac *= x;
    x--;
    return factorial(x, fac);
}

int main(void)
{
    int n, fac = 1;
    scanf("%d", &n);
    if (n < 0) {
        printf ("incorrect data entry\n");
    } else {
        printf("%d\n", factorial(n, fac));
    }
    return 0;
}
