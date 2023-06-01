#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int flag = 0;

void handler1(int sig)
{
    flag = 0;
}

void handler2(int sig)
{
    flag = 1;
}

int main(void)
{
    int x;
    unsigned num = 0;
    signal(SIGINT, handler1);
    signal(SIGQUIT, handler2);
    printf("%d\n", getpid());
    fflush(stdout);
    while (scanf("%d", &x) == 1) {
        if (flag == 0) {
            num += x;
            printf("%d\n", num);
            fflush(stdout);
        } else if (flag == 1) {
            num *= x;
            printf("%d\n", num);
            fflush(stdout);
        }
    }
    return 0;
}
