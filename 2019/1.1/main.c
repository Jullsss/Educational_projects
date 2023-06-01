#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int c, i = 0, count1 = 0, count2 = 0, count3 = 0;
    while ((c = getchar()) != '!') {
        if (c == ' ') {
            if (i == 0) {
                i = 1;
                count1++;
            }
        } else {
            i = 0;
        }
        if (c == '\n') {
            count2++;
            count1++;
        }
        count3++;
        putchar(c);
    }
    printf("\n");
    printf("%d\n", count1);
    printf("%d\n", count2);
    printf("%d\n", count3);
    return 0;
}
