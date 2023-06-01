#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <wait.h>

int main(int argc, char **argv)
{
    int count;
    sscanf(argv[1], "%d", &count);
    int num;
    int k = ftok(argv[0], 1);
    int sem = semget(k, count, IPC_CREAT|IPC_EXCL|0600);
    struct sembuf u1 = {0, 1, SEM_UNDO};
    semop(sem, &u1, 1);
    setvbuf(stdin, NULL, _IONBF, 0);
    for (int i = 0; i < count; i++){
        if (!fork()) {
            while (1) {
                struct sembuf d = {i, -1, SEM_UNDO};
                semop(sem, &d, 1);
                if (scanf("%d", &num) == EOF) {
                    break;
                }
                int mod = num % count;
                if (mod < 0) {
                    mod += count;
                }
                struct sembuf u = {mod, 1, SEM_UNDO};
                printf("%d %d\n", i, num);
                fflush(stdout);
                semop(sem, &u, 1);
            }
            semctl(sem, 0, IPC_RMID);
            _exit(0);
        }
    }
    while(wait(NULL) != -1);
    return 0;
}
