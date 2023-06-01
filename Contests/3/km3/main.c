#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int fl = 0;

void SigHndlr(int s){
    signal(SIGINT, SigHndlr);
    int fd[2], fd2[2];
    ++fl;
    if (!(fl % 2)){
        printf("chet\n");
        pipe (fd);
        if (!fork()) {
            dup2(fd[1], 1);
            close(fd[0]);
            close(fd[1]);
            system("ls");
            exit(0);
        }

        if (!fork()) {
            dup2(fd[0], 0);
            close(fd[0]);
            close(fd[1]);
            system("wc");
            exit(0);
        }
        close(fd[0]);
        close(fd[1]);
    }
}

int main(int argc, char **argv)
{
    system("ls");
    signal(SIGINT, SigHndlr);
    while(1) sleep(1);
    return 0;
}
