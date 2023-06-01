#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void normalize_path(char *buf) {
    char *str = buf;
    char *line = buf;
    while (*str != '\0') {
        if (*str == '/') {
            while (*str == '/') {
                str++;
            }
            str--;
        }
        *line = *str;
        line++;
        str++;
    }
    *line = '\0';
}
