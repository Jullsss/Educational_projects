#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int fd[2];
    pipe(fd);
    if (!fork()) {
        int stat;
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        if (!fork()) {
            int fd_int = open(argv[4], O_RDONLY);
            dup2(fd_int, 0);
            close(fd_int);
            if (execlp(argv[1], argv[1], NULL) == -1) {
                _exit(1);
            }
        }
        wait(&stat);
        if (WIFEXITED(stat) == 0 || WEXITSTATUS(stat) != 0) {
            _exit(1);
        }
        if (execlp(argv[2], argv[2], NULL) == -1) {
            _exit(1);
        }
        _exit(0);
    }
    close(fd[1]);
    if (!fork()) {
        int fd_out = open(argv[5], O_WRONLY | O_APPEND | O_CREAT, 0666);
        dup2(fd[0], 0);
        dup2(fd_out, 1);
        close(fd[0]);
        close(fd_out);
        if (execlp(argv[3], argv[3], NULL) == -1) {
            _exit(1);
        }
    }
    close(fd[0]);
    wait(NULL);
    wait(NULL);
    return 0;
}
