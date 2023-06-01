#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

int flag = 0;
int count = 0;
int i = 1;

void handler_int (int sig) {
    if (i == 2) {
        signal (SIGINT, SIG_DFL);
    }
    i++;
}

void handler_alarm (int sig) {
    if (flag == 0) {
        flag++;
        alarm(2);
    }
    if (flag == 1) {
        flag++;
        alarm(2);
    }
    if (flag == 2) {
        flag--;
        alarm(2);
    }
}

int main(void)
{
    signal (SIGINT, handler_int);
    signal (SIGALRM, handler_alrm);

    alarm(5);

    while(1) {
        if (!fork()) {
            if ((flag == 0 && count % 2 == 0) || flag == 2){
                if (flag == 0 && count % 2 == 0) {
                    count ++;
                }
                printf("son ");
            }
        } else {
            if ((flag == 0 && count % 2 == 1) || flag == 1){
                    if (flag == 0 && count % 2 == 1) {
                    count ++;
                }
                printf("Father ");
            }
        }
    }
    return 0;
}
