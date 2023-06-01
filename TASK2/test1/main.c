#include <stdio.h>

/* a first program */
int main(void)
{
    int a, b;
    int c;
    while (scanf("%d%d", &b, &c) == 2) {
        if (b <= 0 || c <= 0) {
            printf("Invalid parameters\n");
        } else {
            // invariant: GCD(a,b)==GCD(b,a%b)
            do {
                a = b;
                b = c;
                c = a % b;
            } while (c != 0);
        printf("%d\n", b);
        }
    }
    return 0;
}
