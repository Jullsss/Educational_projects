#include <stdio.h>
#include <stdlib.h>

enum { MAX = 0x1000000 };

int
check_float(unsigned int x)
{
    if (x == 0) {
        return 1;
    }
    while ((x & 1) == 0) {
        x >>= 1;
    }
    if (x < MAX) {
        return 1;
    } else {
        return 0;
    }
}

int
main(void)
{
    unsigned int x;
    while (scanf("%u", &x) == 1) {
        printf("%d\n", check_float(x));
    }
    return 0;
}
