#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int main(void)
{
    enum { HALF = 2 };
    int n, w;
    scanf("%o%o", &n, &w);
    int32_t size = 1;
    size <<= n;
    for (int32_t i = 0; i < size / HALF; i++) {
        printf("|%*"PRIo32"|%*"PRId32"|%*"PRId32"|\n", w, i, w, i, w, i);
    }
    for (int32_t i = size / HALF; i < size; i++){
        printf("|%*"PRIo32"|%*"PRId32"|%*"PRId32"|\n", w, i, w, i, w, - i + size / HALF);
    }
    return 0;
}
