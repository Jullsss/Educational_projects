#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int f = open(argv[1], O_WRONLY|O_TRUNC|O_CREAT, 0600);
    unsigned int a;
    unsigned int bit[4] = {0};
    while (scanf("%d", &a) == 1) {
        bit[0] = a >> 24;
        bit[1] = (a & 0xFFFFFF) >> 16;
        bit[2] = (a & 0xFFFF) >> 8;
        bit[3] = a & 0xFF;
        a = (bit[3] << 24) + (bit[2] << 16) + (bit[1] << 8) + bit[0];
        write(f, &a, sizeof(a));
    }
    return 0;
}
