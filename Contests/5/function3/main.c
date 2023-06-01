#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

enum { MAX_NUM = 10 };

void
print_mas(long long int *mas) {
    for (int i = 0; i < MAX_NUM; i++) {
        printf("%d %lld\n", i, mas[i]);
    }
}

int
main(void)
{
    char line[PATH_MAX + 4];
    memset(line, 0, sizeof(line));
    int i;
    long long num[MAX_NUM] = {0};
    if (!(fgets(line, sizeof(line), stdin))) {
        print_mas(num);
        return 0;
    }
    if (line == NULL) {
        print_mas(num);
        return 0;
    }
    for (i = 0; i < sizeof(line); i++) {
        if (line[i] == '\n' || line[i] == '\r' || line[i] == '\0') {
            break;
        }
    }
    line[i] = '\0';
    FILE *file = fopen(line, "r");
    if (file != NULL) {
        int x;
        while ((x = getc_unlocked(file)) != EOF) {
            if (x >= '0' && x <= '9') {
                num[x - '0']++;
            }
        }
    } else {
        print_mas(num);
        return 0;
    }
    fclose(file);
    print_mas(num);
    return 0;
}
