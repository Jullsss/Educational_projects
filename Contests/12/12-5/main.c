#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

volatile int flag = 0;

void func1()
{
    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    sigaddset(&mask, SIGIO);
    sigprocmask(SIG_BLOCK, &mask, &oldmask);
    flag = 1;
    sigprocmask(SIG_UNBLOCK, &mask, &oldmask);
}

void func2()
{
    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    sigaddset(&mask, SIGIO);
    sigprocmask(SIG_BLOCK, &mask, &oldmask);
    flag = 2;
    sigprocmask(SIG_UNBLOCK, &mask, &oldmask);
}

void func3()
{
    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    sigaddset(&mask, SIGIO);
    sigprocmask(SIG_BLOCK, &mask, &oldmask);
    flag = 3;
    sigprocmask(SIG_UNBLOCK, &mask, &oldmask);
}

int main(int argc, char **argv)
{
    struct sigaction sa1 = {.sa_flags = SA_RESTART, .sa_handler = func1};
    struct sigaction sa2 = {.sa_flags = SA_RESTART, .sa_handler = func2};
    struct sigaction sa3 = {.sa_flags = SA_RESTART, .sa_handler = func3};
    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    sigaddset(&mask, SIGIO);
    sigaddset(&mask, SIGALRM);
    int pid = getpid();
    int pid1 = fork();
    int fd;
    char x, tmp;
    if (!pid1) {
        pid1 = getpid();
        while (!flag) {
            sigsuspend(&oldmask);
        }
        if (flag == 1) {
            flag = 0;
            printf("0");
            sigaction(SIGALRM, &sa1, NULL);
            kill(pid, SIGALRM);
        }
        if (flag == 2) {
            flag = 0;
            printf("1");
            sigaction(SIGALRM, &sa1, NULL);
            kill(pid, SIGALRM);
        }
        if (flag == 3) {
            flag = 0;
            kill(pid, SIGIO);
        }
        exit(0);
    }
    int pid2 = fork();
    if (!pid2) {
        pid2 = getpid();
        fd = open(argv[1], O_RDONLY);
        while (!flag) {
            sigsuspend(&oldmask);
        }
        if (flag == 1) {
            flag = 0;
        }
        while (read(fd, &x, sizeof(x)) == sizeof(x)) {
            for (int i = 0; i < 8 * sizeof(x); i++) {
                tmp = (x >> (8 * sizeof(x) - i - 1)) & 1;
                if (tmp == 0) {
                    sigaction(SIGUSR1, &sa1, NULL);
                    kill(pid1, SIGUSR1);
                }
                if (tmp == 1) {
                    sigaction(SIGUSR2, &sa2, NULL);
                    kill(pid1, SIGUSR2);
                }
            }
        }
        sigaction(SIGIO, &sa3, NULL);
        kill(pid1, SIGIO);
        exit(0);
    }
    while (!flag) {
        sigsuspend(&oldmask);
    }
    if (flag == 1) {
        sigaction(SIGALRM, &sa1, NULL);
        kill(pid2, SIGALRM);
    }
    while (wait(NULL) != -1);
}
