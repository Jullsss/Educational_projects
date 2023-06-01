#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int f = open(argv[1], O_WRONLY|O_TRUNC|O_CREAT, 0600);
    unsigned int a;
    unsigned int bit[sizeof(a)] = {0};
    int tmp = 0;
    while (scanf("%d", &a) == 1) {
        for (int i = 0; i < sizeof(a); i++) {
            tmp = sizeof(a) - i - 1;
            bit[i] = a & (0xFF << (tmp * 2)) >> (8 * tmp);
            a += bit[i] << (8 * i);
        }
        write(f, &a, sizeof(a));
    }
    return 0;
}
