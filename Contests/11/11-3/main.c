#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

void func(char *str) {
    FILE *fd;
    if ((fd = fopen(str, "r")) == NULL) {
        exit(1);
    }
    char s[PATH_MAX];
    fgets(s, PATH_MAX, fd);
    s[strlen(s) - 1] = 0;
    fclose(fd);
    if (execlp(s, s, NULL) == -1) {
        _exit(1);
    }
}

int main(int argc, char **argv)
{
    int status;
    int n = atoi(argv[1]);
    if (n > argc - 2) {
        n = argc - 2;
    }
    int count = 0;
    for (int i = 2; i < n + 2; i++) {
        if (!fork()) {
            func(argv[i]);
        }
    }
    while (wait(&status) != -1) {
        if (WIFEXITED(status) != 0 && WEXITSTATUS(status) == 0) {
            count++;
        }
    }
    for (int i = n + 2; i < argc; i++) {
        if (!fork()) {
            func(argv[i]);
        }
        wait(&status);
        if (WIFEXITED(status) != 0 && WEXITSTATUS(status) == 0) {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}
