#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char c;
    int len = 0, max = 0, flag = 0;
    while ((c = getchar()) != EOF) {
        len++;
        if (c == '\n') {
            if (len > max && flag == 1) {
                max = len;
            }
            len = 0;
            max = 0;
            flag = 0;
        }
        if (c == ' ') {
            flag = 1;
        }
    }
    if (len > max && flag == 1) {
        max = len;
    }
    printf("%d\n", max);
    return 0;
}
