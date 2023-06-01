#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct stat buffer1, buffer2;

int main(int argc, char **argv){
    int fd[2];
    if (argc == 3){
        if ((lstat (argv[1], &buffer1) != -1) || (lstat (argv[2], &buffer2) != -1)){
            pipe(fd);
            if (fork()){
                dup2(fd[1], 1);
                close(fd[1]);
                close(fd[0]);
                execlp(argv[1], argv[1], NULL);
            }
            dup2(fd[0], 0);
            close(fd[0]);
            close(fd[1]);
            execlp(argv[2], argv[2], NULL);
        } else
            exit(0);
    } else
        exit(0);
    return 0;
}
