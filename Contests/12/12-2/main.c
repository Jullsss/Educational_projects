#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int count, modulo;
    count = atoi(argv[1]);
    modulo = atoi(argv[2]);
    unsigned long long sqr = 1;
    int tmp;
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    if (!fork()) {
        close(fd2[0]);
        if (!fork()) {
            dup2(fd1[0], 0);
            dup2(fd2[1], 1);
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[1]);
            execlp(argv[3], argv[3], NULL);
            _exit(1);
        }
        dup2(fd1[1], 1);
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[1]);
        for (unsigned long long i = 1; i <= count; i++) {
            sqr = ((i % modulo) * i) % modulo;
            printf ("%u ", (unsigned) sqr);
            fflush (stdout);
        }
        close(1);
        wait(NULL);
        _exit(1);
    }
    close(fd1[0]);
    close(fd1[1]);
    if (!fork()) {
        if (!fork()) {
            dup2(fd2[0], 0);
            close(fd2[0]);
            close(fd2[1]);
            while (scanf("%u", &tmp) == 1) {
                printf("%u\n", (unsigned) tmp);
                fflush (stdout);
            }
            _exit(1);
        }
        close(fd2[0]);
        close(fd2[1]);
        wait(NULL);
        _exit(1);
    }
    close(fd2[0]);
    close(fd2[1]);
    wait(NULL);
    wait(NULL);
    printf("0\n");
    return 0;
}
