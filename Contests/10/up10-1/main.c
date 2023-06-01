#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>



int main(void)
{
    int fd[2];
    pipe(fd);
    if (!fork()) {
        if (!fork()) {
            if (!fork()) {
                time_t t = time(NULL);
                write(fd[1], &t, sizeof(t));
                write(fd[1], &t, sizeof(t));
                write(fd[1], &t, sizeof(t));
                exit(0);
            } else {
                wait(NULL);
                time_t t;
                read(fd[0], &t, sizeof(t));
                struct tm *ts;
                ts = localtime(&t);
                printf("D:%d\n", ts->tm_mday);
                exit(0);
            }
        } else {
            wait(NULL);
            time_t t;
            read(fd[0], &t, sizeof(t));
            struct tm *ts;
            ts = localtime(&t);
            printf("M:%d\n", ts->tm_mon + 1);
            exit(0);
        }
    } else {
        wait(NULL);
        time_t t;
        read(fd[0], &t, sizeof(t));
        struct tm *ts;
        ts = localtime(&t);
        printf("Y:%d\n", ts->tm_year + 1900);
        exit(0);
    }
    return 0;
}
