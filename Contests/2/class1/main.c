#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
    enum { HALF = 2 };
    int n, w;
    scanf("%o%o", &n, &w);
    intmax_t size = 1;
    size <<= n;
    for (intmax_t i = 0; i < size / HALF; i++) {
        printf("|%*jo|%*jd|%*jd|\n", w, i, w, i, w, i);
    }
    for (intmax_t i = size / HALF; i < size; i++){
        printf("|%*jo|%*jd|%*jd|\n", w, i, w, i, w, - i + size / HALF);
    }
    return 0;
}
