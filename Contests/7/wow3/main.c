#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char line[] = "rwxrwxrwx";

int
parse_rwx_permissions(const char *str)
{
    if (str == NULL) {
        return -1;
    }
    int len = strlen(str);
    if (len != sizeof(line) - 1) {
        return -1;
    }
    int k = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] != line[i] && str[i] != '-') {
            return -1;
        }
        k = k << 1;
        if (str[i] == line[i]) {
            k++;
        }
    }
    return k;
}
