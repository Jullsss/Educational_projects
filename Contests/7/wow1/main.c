#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
    long long maxsize = 0;
    for (int i = 1; i < argc; i++) {
        struct stat file_stat;
        if (lstat(argv[i], &file_stat) == 0) {
            if (S_ISREG(file_stat.st_mode) && file_stat.st_nlink == 1) {
                maxsize +=  file_stat.st_size;
            }
        }
    }
    printf("%lld\n", maxsize);
    return 0;
}
