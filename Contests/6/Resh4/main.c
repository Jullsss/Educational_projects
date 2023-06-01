#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int fd[2];
    int *mas_pid = (int *)calloc(argc + 1, sizeof(int));
    int i, j;
    if (argc == 1) {
        return 0;
    }
    for (i = 1; i < argc - 1; i++) {
        if (pipe(fd) < 0) {
            for (j = 1; j < i; j++) {
                kill(mas_pid[j], SIGKILL);
            }
            free(mas_pid);
            _exit(1);
        }
        mas_pid[i] = fork();
        if (!mas_pid[i]) {
            dup2(fd[1], 1);
            close(fd[0]);
            close(fd[1]);
            execlp(argv[i], argv[i], NULL);
            _exit(1);
        }
        if (mas_pid[i] < 0) {
            for (j = 1; j < i; j++) {
                kill(mas_pid[j], SIGKILL);
            }
            free(mas_pid);
            _exit(1);
        }
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
    }
    mas_pid[argc - 1] = fork();
    if (!mas_pid[argc - 1]) {
        execlp(argv[argc - 1], argv[argc - 1], NULL);
        _exit(1);
    }
    if (mas_pid[argc - 1] < 0) {
        for (j = 1; j < argc - 1; j++) {
            kill(mas_pid[j], SIGKILL);
        }
        free(mas_pid);
        _exit(1);
    }
    close(fd[0]);
    close(fd[1]);
    close(0);
    while (wait(NULL) != -1);
    free(mas_pid);
    return 0;
}
