#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <limits.h>

int main(int argc, char **argv)
{
    int fd;
    if ((fd = open(argv[1], O_RDWR)) < 0) {
        return 1;
    }
    long long x;
    int n;
    if ((n = read(fd, &x, sizeof(x))) == 0) {
        return 0;
    }
    long long min = x;
    int pos = 0, count = 0;
    while ((n = read(fd, &x, sizeof(x)))) {
        if (x == LLONG_MIN) {
            return 0;
        }
        count++;
        if (x < min) {
            min = x;
            pos = count;
        }

    }
    min *= -1;
    lseek(fd, pos * sizeof(min), 0);
    write(fd, &min, sizeof(min));
    close(fd);
    return 0;
}
