#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd = open (argv[1], O_RDONLY);
    int max = 0;
    pid_t pid;
    //int status;
    int pipes[2];
    pipe (pipes);
    if (!(pid = fork())) {
        close(fd); close (pipes[1]);
        int y;
        while (read (pipes[0], &y, sizeof(y))) {
            if (y >= max) {
                max = y;
            }
        }
        printf ("%d\n", max);
    } else if (pid != -1) {
        int x = 0;
        char c;
        while (read (fd, &c, sizeof(c))) {
            x *= 10;
            x += c - '0';
            printf ("%c|", c);
            //printf ("%d\n", x);
            if (c == '\0' || c == '\n') {
                write (pipes[1], &x, sizeof(x));
                x = 0;
            }
        }
        printf ("END dad\n");
    }
    return 0;
}
