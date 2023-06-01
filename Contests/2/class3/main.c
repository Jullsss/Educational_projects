#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

unsigned long long hash_function(unsigned long long value);

int main(int argc, char **argv)
{
    int fd;
    if ((fd = open(argv[1], O_WRONLY|O_CREAT, 0660)) < 0) {
        return 0;
    }
    int count = atoi(argv[3]);
    if (count == 0) {
        close(fd);
        return 0;
    }
    unsigned long long h0;
    sscanf(argv[2], "%llx", &h0);
    if (lseek(fd, (count - 1) * sizeof(unsigned long long), SEEK_END) == -1) {
        close(fd);
        return 0;
    }
    if (write(fd, &h0, sizeof(unsigned long long)) < sizeof(unsigned long long)) {
        close(fd);
        return 0;
    }
    for (int i = 1; i < count; i++) {
        if (lseek(fd, (- i - 1) * (long) sizeof(unsigned long long), SEEK_END) == -1) {
            close(fd);
            return 0;
        }
        h0 = hash_function(h0);
        if (write(fd, &h0, sizeof(unsigned long long)) < sizeof(unsigned long long)) {
            close(fd);
            return 0;
        }
    }
    close(fd);
    return 0;
}
