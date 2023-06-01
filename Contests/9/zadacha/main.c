#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

int main(int argc, char **argv)
{
    enum { MODE = 0600 };
    int f;
    if ((f = open(argv[1], O_WRONLY|O_TRUNC|O_CREAT, MODE)) < 0) {
        return 0;
    }
    unsigned int a;
    unsigned int bit[4] = {0};
    while (scanf("%d", &a) == 1) {
        bit[0] = a >> 24;
        bit[1] = (a & 0xFFFFFF) >> 16;
        bit[2] = (a & 0xFFFF) >> 8;
        bit[3] = a & 0xFF;
        a = (bit[3] << 24) + (bit[2] << 16) + (bit[1] << 8) + bit[0];
        if (write(f, &a, sizeof(a)) < sizeof(a)) {
            close (f);
            return 0;
        }
    }
    return 0;
}
