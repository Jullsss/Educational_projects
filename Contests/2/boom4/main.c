#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

struct Task
{
    unsigned uid;
    int gid_count;
    unsigned *gids;
};

int myaccess(const struct stat *stb, const struct Task *task, int access)
{
    if (task->uid == 0) {
        return 1;
    }
    if (stb->st_uid == task->uid) {
        if (access == (((stb->st_mode) >> 6) & access)) {
            return 1;
        } else {
            return 0;
        }
    }
    for (int i = 0; i < task->gid_count; i++) {
        if (stb->st_gid == task->gids[i]) {
            if (access == (((stb->st_mode) >> 3) & access)) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    if (access == ((stb->st_mode) & access)) {
        return 1;
    }
    return 0;
}
