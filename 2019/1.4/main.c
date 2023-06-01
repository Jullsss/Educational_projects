#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n, x;
    scanf("%d", &n);
    char str[n];
    char *s = str;
    scanf("%s", str);
    while (*s) {
        x = *s - '0';
        if (x >= 0 && x <= 9) {
            printf("%d", x);
            *s++;
        } else {
            break;
        }
    }
    return 0;
}
