#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <wait.h>

int main(int argc, char **argv)
{
    int nproc, key;
    unsigned long long maxval;
    sscanf(argv[1], "%d", &nproc);
    sscanf(argv[2], "%d", &key);
    sscanf(argv[3], "%llu", &maxval);
    int semid = semget(key, nproc, 0600 | IPC_CREAT);
    int *p = NULL;
    int shmid = shmget(key, 2 * sizeof(int), 0600 | IPC_CREAT);
    p = shmat(shmid, NULL, 0);
    p[0] = 0;
    p[1] = 0;
    for (int i = 0; i < nproc; i++){
        if (!fork()){
            while (semop(semid, (struct sembuf[]){{i, -1, 0}}, 1) >= 0){
                if (p[0] > maxval){
                    semctl(semid, 0, IPC_RMID);
                    shmctl(shmid, IPC_RMID, NULL);
                    break;
                } else {
                    printf("%d %d %d\n", i + 1, p[0], p[1]);
                    fflush(stdout);
                    p[1] = i + 1;
                    p[0]++;
                    unsigned long long val;
                    val = ((((p[0] % nproc) * (p[0] % nproc)) % nproc) * (p[0] % nproc) % nproc) * (p[0] % nproc);
                    semop(semid,(struct sembuf[]){{val % nproc, 1, 0}}, 1);
                }
            }
            exit(0);
        }
    }
    semop(semid,(struct sembuf[]){{0, 1, 0}}, 1);
    while (wait(NULL) != -1);
    return 0;
}
