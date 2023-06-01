#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

int main(void)
{
    enum {
        CARDINALITY = 16,
        RADIX = 10
    };
    unsigned long long int sum = 0, x = 0;
    char buf[CARDINALITY] = {0}, c = '0';
    int fd = 0;
    ssize_t k = 0;
    while ((k = read(fd, buf, sizeof(buf))) > 0) {
        for (int i = 0; i < k; i++) {
            if (buf[i] == '+' || buf[i] == '-') {
                c = buf[i];
            } else if (isspace(buf[i])) {
                if (c == '-') {
                    sum -= x;
                } else {
                    sum += x;
                }
                c = '0';
                x = 0;
            } else {
                x *= RADIX;
                x += buf[i] - '0';
            }
        }
    }
    printf("%lld\n", (long long)sum);
    return 0;
}
