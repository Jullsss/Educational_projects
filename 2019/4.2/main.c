#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n, int x, int y) {
    if (n <= 1) {
        (x > y) ? x : (x = y);
        return x;
    }
    (x > y) ? (y += x):(x += y);
    return fibonacci(n - 1, x, y);
}

int main(void)
{
    int n;
    scanf("%d", &n);
    if (n == 0 || n == 1) {
        printf("1\n");
        return 0;
    }
    printf("%d\n", fibonacci(n, 1, 1));
    return 0;
}
