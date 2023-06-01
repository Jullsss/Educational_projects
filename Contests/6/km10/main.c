#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int fd1, fd2, n = atoi(argv[3]);
    char c;
    fd1 = open(argv[1], O_RDONLY);
    fd2 = open("out.txt", O_CREAT | O_WRONLY);
    read(fd1, &c, 1);
    while (c != NULL) {
        for(int i = 0; i < n; i++) {
            while (c != '\n') {
                write(fd2, &c, 1);
                if (c == argv[2]) {
                    write(fd2, &c, 1);
                }
                read(fd1, &c, 1);
            }
        }
        read(fd1, &c, 1);
    }
    return 0;
}
