#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    int fd[2];
    pipe(fd);
    int num;
    long long sum = 0;
    if (!fork()) {
        if (!fork()) {
            close(fd[1]);
            while (read(fd[0], &num, sizeof(num)) == 4) {
                sum += num;
            }
            printf("%lld\n", sum);
            fflush(stdout);
            close(fd[0]);
            _exit(0);
        }
        close(fd[0]);
        close(fd[1]);
        wait(NULL);
        _exit(0);
    }
    while (scanf("%d", &num) == 1) {
        write(fd[1], &num, sizeof(num));
    }
    char sym = '*';
    write(fd[1], &sym, sizeof(sym));
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    return 0;
}
