#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>

volatile int count = 0;

void test(int c) {
    printf("%d %d\n", c, count);
    fflush(stdout);
    if (count < 0) {
        _exit(0);
    }
}

void func1(int sig) {
    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    sigprocmask(SIG_BLOCK, &mask, &oldmask);
    count += 5;
    test(SIGUSR1);
    sigprocmask(SIG_UNBLOCK, &mask, &oldmask);
}

void func2(int sig) {
    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    sigprocmask(SIG_BLOCK, &mask, &oldmask);
    count -= 4;
    test(SIGUSR2);
    sigprocmask(SIG_UNBLOCK, &mask, &oldmask);
}

int main(void)
{
    struct sigaction sa1 = {.sa_flags = SA_RESTART, .sa_handler = func1};
    struct sigaction sa2 = {.sa_flags = SA_RESTART, .sa_handler = func2};
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    sigaction(SIGUSR1, &sa1, NULL);
    sigaction(SIGUSR2, &sa2, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while(1) {
        pause();
    }
    return 0;
}
