#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024

int main(int argc, char **argv)
{
    if (argc != 4) {
        exit(1);
    }
    FILE *f1, *f2;
    if ((f1 = fopen(argv[1], "r")) == NULL) {
        exit(1);
    }
    if ((f2 = fopen(argv[2], "w")) == NULL) {
        exit(1);
    }
    char str[MAX];
    while ((fgets(str, MAX, f1)) != NULL) {
        if (strcmp(str, argv[3]) != 0) {
            fputs(str, stdout);
        }
    }
    fclose(f1);
    fclose(f2);
    return 0;
}
