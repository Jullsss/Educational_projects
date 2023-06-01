#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

volatile int flag = 0;

void handler_usr1(int sig) {
    flag = 1;
}

void handler_usr2(int sig) {
    flag = 2;
}

void handler_alrm(int sig) {
    flg = 3;
}

void handler_term(int sig) {
    flag = 4;
}

int main(int argc, char **argv)
{
    int cur_v = atoi(argv[1]);
    int v = cur_v;
    int tmp = cur_v;
    time_t start, end;
    unsigned long long  = 0;

    while (1) {
        if (flag == 1) {
            time(&end);
            int sec = difftime(end, start);
            s += v * sec;
            v++;
            flag = 0;
        } else if (flag == 2) {
            int sec = difftime(end, start);
            s += v * sec;
            v--;
            flag = 0;
        } else if (flag == 3) {
            time(&start);
            v = tmp;
            s = 0;
            flag = 0;
        } else if (flag == 4) {
            printf("%llu", s);
            fflush(stdout);
            flag = 0;
            return 0;
        }
    }

    return 0;
}
