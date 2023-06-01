#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    const char s[] = "rwxrwxrwx";
    int tmp;
    for (int i = 1; i < argc; i++) {
        sscanf(argv[i], "%o", &tmp);
        int byte, len;
        len = sizeof(s) - 1;
        for (int j = 0; j < sizeof(s) - 1; j++) {
            byte = (tmp & (1 << (len - 1))) >> (len - 1);
            if (byte == 1) {
                printf("%c", s[j]);
            } else {
                printf("-");
            }
            len--;
        }
        printf("\n");
    }
    return 0;
}
