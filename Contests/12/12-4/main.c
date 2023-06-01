#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int mod;
    sscanf(argv[2], "%d", &mod);
    int fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0751);
    dprintf(fd, "#!/usr/bin/env python3\n");
    dprintf(fd, "k = int(input())\n");
    dprintf(fd, "mod = %d\n", mod);
    dprintf(fd, "count = 1\n");
    dprintf(fd, "count = k * (k + 1) // 2\n");
    dprintf(fd, "print (count %% mod)\n");
    close(fd);
    return 0;
}
