#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int f1, f2;
int buf[256], sim[256];

void rec()
{
    int c;
    if ((c = fgetc(stdin)) != EOF) {
        rec();
        fputc(c, stdout);
    }
}

void out()
{
    int c;
    while ((c = fgetc(stdin)) != EOF) {
        fputc(c, stdout);
    }
}

int main(int argc, char **argv){
    int fd[2];
    pipe (fd);
    if (!fork()){ // сын
        if (!fork()){ // внук
            if (!fork()) { //правнук
                dup2(fd[0], 0);
                close(fd[0]);
                close(fd[1]);
                f2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);
                dup2(f2, 1);
                close(f2);
                out();
                return 0;
            }
            dup2(fd[1], 1);
            close(fd[0]);
            close(fd[1]);
            f1 = open(argv[1], O_RDONLY);
            dup2(f1, 0);
            close(f1);
            rec();
            return 0;
        }
        close(fd[0]);
        close(fd[1]);
        return 0;
    }
    close(fd[0]);
    close(fd[1]);
    return 0;
}
