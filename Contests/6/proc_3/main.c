#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    char s[8];
    unsigned int num = 0;
    for (int i = 1; i <= 3; i++) {
        int pid = fork();
        if (!pid) {
            scanf("%s", s);
            num = atoi(s);
            printf("%d %u\n", i, num * num);
            exit(1);
        }
    }
    while (wait(NULL) != -1);
    return 0;
}
