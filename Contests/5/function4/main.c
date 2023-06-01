#include <stdio.h>
#include <stdlib.h>

char
*memory_allocation(char *str, int size) {
    str = (char*) realloc(str, size * sizeof(char));
    if (str == NULL) {
        free(str);
        exit(1);
    } else {
        return str;
    }
}

char
*getline2(FILE *f) {
    enum { SIZE = 2 };
    char *str = NULL;
    str = (char*) calloc(SIZE, sizeof(char));
    if (str == NULL) {
        free(str);
        return NULL;
    }
    int c;
    int tmp = 0;
    int size = SIZE;
    if ((c = fgetc(f)) == EOF) {
        free(str);
        return NULL;
    }
    while (c != '\n' && (c != EOF)) {
        str[tmp++] = c;
        if (tmp == size) {
            size *= SIZE;
            str = memory_allocation(str, size + 1);
        }
        c = fgetc(f);
    }
    if (c == '\n') {
        str = memory_allocation(str, tmp + 2);
        str[tmp] = '\n';
        str[tmp + 1] = '\0';
    } else {
        str = memory_allocation(str, tmp + 1);
        str[tmp] = '\0';
    }
    return str;
}


