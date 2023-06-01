#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int pid1, pid2;
    int fd[2];
    pipe(fd); //
    if (!(pid2 = fork())) {
        dup2(fd[1], 1);
        execl("ls", "ls", NULL);
        exit (1);
    } else if (pid2 == -1) {
        exit (1);
    }
    if (!(pid1 = fork())) {
        dup2(fd[0], 0);
        execlp("grep", "grep", "*.c", NULL);
        exit (1);
    } else if (pid1 == -1) {
        exit (1);
    }
    wait (NULL);
    return 0;
}
