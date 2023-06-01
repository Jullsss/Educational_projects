#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>

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
    for (int i = 0; i < n; i++) {
        if (!fork()) {
            struct ms msg;
            while(msgrcv(mes, &msg, sizeof(msg) - sizeof(msg.type), i + 1, 0) > 0) {
                long long x3 = msg.num1 + msg.num2;
                printf("%d %lld\n", i, x3);
                fflush(stdout);
                msg.type = x3 % n + 1;
                msg.num1 = msg.num2;
                msg.num2 = x3;
                if (msg.num2 > max) {
                    msgctl(mes, IPC_RMID, 0);
                    _exit(0);
                }
                msgsnd(mes, &msg, sizeof(msg) - sizeof(msg.type), 0);
            }
            msgctl(mes, IPC_RMID, 0);
            _exit(0);
        }
    }
    while(wait(NULL) != -1);
    struct ms msg;
    msg.num1 = x1;
    msg.num2 = x2;
    msg.type = 1;
    msgsnd(mes, &msg, sizeof(msg) - sizeof(msg.type), 0);
    return 0;
}
