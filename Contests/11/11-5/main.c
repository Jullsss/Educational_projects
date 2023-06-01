#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int flag = 0;
volatile int i = 0;

void handler1(int sig)
{
    flag = 1;
    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGTERM);
    sigprocmask(SIG_BLOCK, &mask, &oldmask);
    i++;
    if (i == 4) {
        _exit(0);
    }
    sigprocmask(SIG_UNBLOCK, &mask, &oldmask);
}

void handler2(int sig)
{
    _exit(0);
}

int main(void)
{
    struct sigaction sa1 = {.sa_flags = SA_RESTART, .sa_handler = handler1};
    struct sigaction sa2 = {.sa_flags = SA_RESTART, .sa_handler = handler2};
    sigaction(SIGINT, &sa1, NULL);
    sigaction(SIGTERM, &sa2, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    int low, high;
    int num = 0, x = 0;
    scanf("%d%d", &low, &high);
    for (int k = low; k < high; k++) {
        if (flag == 1) {
            printf("%d\n", num);
            fflush(stdout);
            flag = 0;
        }
        for (int j = 2; j * j <= k; j++) {
            if (k % j == 0) {
                x = 1;
                break;
            }
        }
        if (x == 0) {
            num = k;
        }
        x = 0;
    }
    printf("-1\n");
    fflush(stdout);
    return 0;
}
