#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int
main (int argc, char **argv) {
    int count, modulo;
    int fd1[2], fd2[2];
    pipe (fd1); // 1-> 2
    pipe (fd2); // 2-> 4
    sscanf (argv[1], "%d", &count);
    sscanf (argv[2], "%d", &modulo);
    if (!fork ()) { //p1
        close (fd2[0]);
        if (!fork ()){ //p2
            dup2 (fd1[0], 0);
            dup2 (fd2[1], 1);
            close (fd1[0]);
            close (fd1[1]);
            close (fd2[1]);
            execlp (argv[3], argv[3], NULL);
            _exit(1);
        }
        unsigned long long number, i = 0;
        dup2 (fd1[1], 1);
        close (fd1[0]);
        close (fd1[1]);
        close (fd2[1]);
        for (i = 1; i <= count; i++) {
            number = ((i % modulo) * i) % modulo;
            printf ("%u ", (unsigned) number);
            fflush (stdout);
        }
        close (1);
        wait (NULL);
        _exit (1);
    }
    if (!fork ()) { //p3
        if (!fork ()){ //p4
            int number;
            dup2 (fd2[0], 0);
            close (fd1[0]);
            close (fd1[1]);
            close (fd2[0]);
            close (fd2[1]);
            while (scanf ("%u", &number) == 1) {
                printf ("%u\n", number);
                fflush (stdout);
            }
            _exit (1);
        }
        close (fd1[0]);
        close (fd1[1]);
        close (fd2[0]);
        close (fd2[1]);
        wait (NULL);
        _exit (1);
    }
    close (fd1[0]);
    close (fd1[1]);
    close (fd2[0]);
    close (fd2[1]);
    while (wait (NULL) != -1);
    printf ("0\n");
    return 0;
}
