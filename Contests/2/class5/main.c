#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <fcntl.h>

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

int recursion(int fd)
{
    struct Node Node;
    if (read(fd, &Node, sizeof(Node)) < sizeof(Node)) {
        return 0;
    }
    if (lseek(fd, 0, 0) == -1) {
        return 0;
    }
    if (Node.right_idx != 0) {
        if (lseek(fd, Node.right_idx * sizeof(Node), 0) == -1) {
            return 0;
        }
        recursion(fd);
    }
    printf("%"PRId32" ", Node.key);
    if (Node.left_idx != 0) {
        if (lseek(fd, Node.left_idx * sizeof(Node), 0) == -1) {
            return 0;
        }
        recursion(fd);
    }
    return 0;
}

int main(int argc, char **argv)
{
    int fd;
    fd = open(argv[1], O_RDONLY);
    recursion(fd);
    close(fd);
    printf("\n");
    return 0;
}
