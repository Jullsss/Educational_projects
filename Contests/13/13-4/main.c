#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <wait.h>

int main(int argc, char **argv)
{
    setvbuf(stdin, NULL, _IONBF, 0);
    int nproc = atoi(argv[1]);
    int key = ftok(argv[0], 0);
    int semid = semget(key, nproc, 0600 | IPC_CREAT | IPC_EXCL);
    int x;
    struct sembuf up_mas = {0, 1, 0};
    semop(semid, &up_mas, 1);
    for (int i = 0; i < nproc; i++){
        if (!fork()) {
            while (1) {
                struct sembuf down = {i, -1, 0};
                semop(semid, &down, 1);
                if (scanf("%d", &x) == EOF) {
                    semctl(semid, 0, IPC_RMID);
                    _exit(0);
                }
                printf("%d %d\n", i, x);
                fflush(stdout);
                if (x % nproc >= 0) {
                    struct sembuf up = {x % nproc, 1, 0};
                    semop(semid, &up, 1);
                } else {
                    struct sembuf up = {(x % nproc) + nproc, 1, 0};
                    semop(semid, &up, 1);
                }
            }
            semctl(semid, 0, IPC_RMID);
            _exit(0);
        }
    }
    while (wait(NULL) != -1);
    return 0;
}
