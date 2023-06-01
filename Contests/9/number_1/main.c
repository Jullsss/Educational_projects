#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int fd1, fd2, fd3;
    if (!fork()) {
        if ((fd1 = open(argv[2], O_RDONLY)) == -1){
            exit(42);
        }
        if ((fd2 = open(argv[3], O_WRONLY|O_CREAT|O_APPEND, 0660)) == -1){
            exit(42);
        }
        if ((fd3 = open(argv[4], O_WRONLY|O_CREAT|O_TRUNC, 0660)) == -1){
            exit(42);
        }
        if (dup2(fd1, 0) < 0) {
            exit(42);
        }
        if (dup2(fd2, 1) < 0) {
            exit(42);
        }
        if (dup2(fd3, 2) < 0) {
            exit(42);
        }
        if (close(fd1) != 0) {
            exit(42);
        }
        if (close(fd2) != 0) {
            exit(42);
        }
        if (close(fd3) != 0) {
            exit(42);
        }
        if (execlp(argv[1], argv[1], NULL) == -1) {
            exit(42);
        }
    }
    int status;
    wait(&status);
    printf("%d\n", status);
    return 0;
}
