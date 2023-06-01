#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int f1, f2;
int per;

int send(int N){
    int c;
    int fl = 0;
    int count = 0;
    while ((c = fgetc(stdin)) != EOF) {
        if((count < N) && (!(fl % 2)))
            fputc(c, stdout);
        count ++;
        if (count == N) {
            fl = fl + 1;
            count = 0;
        }
    }
    return 0;
}

int main(int argc,char **argv)
{
    int t;
    int fd[2];
    pipe(fd);
    if (!fork()){
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        f2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);
        dup2(f2, 1);
        close(f2);
        execlp("wc", "wc", NULL);
        return -1;
    }
    f1 = open(argv[1], O_RDONLY);
    dup2(f1, 0);
    close(f1);
    dup2(fd[1], 1);
    close(fd[0]);
    close(fd[1]);
    per = argv[3][0] - '0';
    send(per);
    return 0;
}
