#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

int func(const char *str)
{
    int status;
    if (!fork()) {
        if (execlp(str, str, NULL) == -1) {
            exit(1);
        }
    }
    wait(&status);
    if (WIFEXITED(status) != 0 && WEXITSTATUS(status) == 0) {
        return 0;
    }
    return 1;
}

int main(int argc, char **argv)
{
    int out1, out2, out3;
    out1 = func(argv[1]);
    if (out1 != 0) {
        out2 = func(argv[2]);
        if (out2 != 0) {
            return 1;
        }
    }
    out3 = func(argv[3]);
    if (out3 == 0) {
        return 0;
    } else {
        return 1;
    }
}
