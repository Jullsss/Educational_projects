#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int mod = atoi(argv[2]);
    int fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0751);
    dprintf(fd, "#!/usr/bin/env python3\n");
    dprintf(fd, "count = int(input())\n count *= (count + 1) // 2\n");
    dprintf(fd, "print (count %% %d)\n", mod);
    close(fd);
    return 0;
}
