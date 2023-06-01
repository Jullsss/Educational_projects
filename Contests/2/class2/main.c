#include <stdio.h>
#include <stdlib.h>

enum
{
    RADIX = 8,
    SQUARE = 64,
    FIRST_MASK = 4,
    SEC_MASK = 2,
    THIRD_MASK = 1
};

void
print_letter(int x)
{
    if ((x & FIRST_MASK) == FIRST_MASK) {
        printf("r");
    } else {
        printf("-");
    }
    if ((x & SEC_MASK) == SEC_MASK) {
        printf("w");
    } else {
        printf("-");
    }
    if ((x & THIRD_MASK) == THIRD_MASK) {
        printf("x");
    } else {
        printf("-");
    }
}

int
main(int argc, char **argv)
{
    int x = 0, y = 0, z = 0, tmp;
    for (int i = 1; i < argc; i++) {
        sscanf(argv[i], "%o", &tmp);
        x = tmp / SQUARE;
        y = (tmp - x * SQUARE) / RADIX;
        z = tmp - x * SQUARE - y * RADIX;
        print_letter(x);
        print_letter(y);
        print_letter(z);
        printf("\n");
    }
    return 0;
}
