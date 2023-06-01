#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

struct ms
{
    long type;
    long long num1;
    long long num2;
};

int main(int argc, char **argv)
{
    int key, n;
    long long x1, x2, max;
    sscanf(argv[1], "%d", &key);
    int mes = msgget(key, IPC_CREAT|0666);
    sscanf(argv[2], "%d", &n);
    sscanf(argv[3], "%lld", &x1);
    sscanf(argv[4], "%lld", &x2);
    sscanf(argv[5], "%lld", &max);
    int *wr = calloc(n, sizeof(int));
    int now = 0;
    for (int i = 0; i < n; i++) {
        int pid = fork();
        if (!pid) {
            while(1) {
                struct ms msg;
                if(msgrcv(mes, &msg, sizeof(msg) - sizeof(msg.type), i + 1, 0) > 0) {
                    long long x3 = msg.num1 + msg.num2;
                    msg.type = x3 % n + 1;
                    msg.num1 = msg.num2;
                    msg.num2 = x3;
                    printf("%d %lld\n", i, x3);
                    fflush(stdout);
                    if (msg.num2 > max) {
                        break;
                    }
                    msgsnd(mes, &msg, sizeof(msg) - sizeof(msg.type), 0);
                } else {
                    break;
                }
            }
            msgctl(mes, IPC_RMID, 0);
            _exit(0);
        } else if (pid != -1) {
            wr[now++] = pid;
        } else {
            for (int i = 0; i < now; i++) {
                kill(wr[i], SIGTERM);
            }
            free(wr);
            return 1;
        }
    }
    while(wait(NULL) != -1);
    struct ms msg;
    msg.num1 = x1;
    msg.num2 = x2;
    msg.type = 1;
    msgsnd(mes, &msg, sizeof(msg) - sizeof(msg.type), 0);
    free(wr);
    return 0;
}
