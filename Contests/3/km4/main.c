#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

FILE *f1;
FILE *f2;

void rec()
{
    if (!feof(f1)) {
        char c;
        c = fgetc(f1);
        rec();
        fputc(c, f2);
    }
}

int main(int argc, char **argv)
{
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[2], "w");
    rec();
    return 0;
}
