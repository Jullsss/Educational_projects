#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int mysys(const char *str)
{
    int pid, status;
    if ((pid = fork()) < 0) {
        return -1;
    } else if (!pid) {
        if (execl("/bin/sh", "sh", "-c", str, NULL) == -1) {
            _exit(127);
        }
    }
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status)) {
        return WTERMSIG(status) + 128;
    }
    return WEXITSTATUS(status);
}
