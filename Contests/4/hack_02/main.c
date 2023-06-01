#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    enum { MAX = 100 };
    int count, m, seed;
    scanf("%d", &count);
    int num[MAX + 1], chance[MAX + 1];
    for (int i = 1; i < count + 1; i++) {
        scanf("%d%d", &num[i], &chance[i]);
    }
    scanf("%d%d", &m, &seed);
    double r;
    srand(seed);
    chance[0] = 0;
    for (int i = 1; i < count + 1; i++) {
        chance[i] += chance[i - 1];
    }
    for (int i = 0; i < m; i++) {
        r = rand() / (RAND_MAX * 1.0 + 1) * MAX;
        for (int j = 0; j < count; j++) {
            if (r > chance[j] && r <= chance[j + 1]) {
                printf("%d\n", num[j + 1]);
                break;
            }
        }
    }
    return 0;
}
