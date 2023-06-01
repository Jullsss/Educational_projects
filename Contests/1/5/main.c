#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    int num;
    int status;
    int pid = fork();
    if (!pid) {
        while (scanf("%d", &num) != EOF) {
            pid = fork();
            if (pid != -1 && pid) {
                wait(&status);
                if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                    printf("%d\n", num);
                    break;
                } else {
                    exit(1);
                }
            } else if (pid == -1) {
                printf("-1\n");
                exit(1);
            }
        }
    } else if (pid != -1) {
        wait(&status);
    } else if (pid == -1) {
        printf("-1\n");
    }
    exit(0);
    return 0;
}
