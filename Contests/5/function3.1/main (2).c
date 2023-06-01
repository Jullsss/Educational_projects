#include <stdio.h>
#include <stdlib.h>

enum
{
    M = 255,
    NUM = 10,
    FIRST_SYMBOL = '0',
    LAST_SYMBOL = '9'
};

int
main(void)
{
    unsigned char s[M + 1], c = getchar();
    unsigned i = 0;
    while (c != '\n' && i < M)
    {
        s[i] = c;
        i++;
        c = getchar();
    }
    unsigned mas[NUM] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned const char *s1 = s;
    FILE *file = fopen(s1, "r");
    if (file)
    {
        while (fscanf(file, "%255s", s) != EOF) {
            for (int i = 0; s[i]; i++) {
                if (s[i] <= LAST_SYMBOL && s[i] >= FIRST_SYMBOL) {
                    mas[s[i] - '0']++;
                }
            }
        }
    }
    fclose(file);
    for (int i = 0; i < NUM; i++) {
        printf("%d %d\n", i, mas[i]);
    }
    return 0;
}
