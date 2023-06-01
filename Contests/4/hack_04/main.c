#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char c;
    int num = 0;;
    double r = 0;
    while (c != NULL) {
        c = getchar();
        if (c != '.') {
            if (c >= 'A') {
                num = c - 'A' + 36;
            } else if (c >= 'a') {
                num = c - 'a' + 10;
            } else {
                num = c - '0';
            }
            r = num / 62;
            r *= RAND_MAX + 1.0;

        }
    }
    return 0;
}
