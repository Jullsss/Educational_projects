#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
    unsigned int count, seed;
    int low, high;
    sscanf(argv[1], "%u", &count);
    sscanf(argv[2], "%d", &low);
    sscanf(argv[3], "%d", &high);
    sscanf(argv[4], "%u", &seed);
    double r;
    srand(seed);
    for (int i = 0; i < count; i++) {
        r = rand() / (RAND_MAX * 1.0 + 1);
        r = r * (high - low) + low;
        r = floor(r);
        printf("%d\n", (int)r);
    }
    return 0;
}
