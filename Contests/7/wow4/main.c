#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv)
{
    unsigned long long maxsize = 0;
    DIR *d;
    struct dirent *entry;
    if ((d = opendir(argv[1])) == NULL) {
        return 1;
    }
    struct stat buf;
    char s[PATH_MAX];
    while ((entry = readdir(d))) {
        if (strlen(entry->d_name) + strlen(argv[1]) + 1 < PATH_MAX) {
            snprintf(s, PATH_MAX + 1, "%s/%s", argv[1], entry->d_name);
            if (stat(s, &buf) == 0) {
                if (S_ISREG(buf.st_mode) && (getuid() == buf.st_uid) &&
                    entry->d_name[0] <= 'Z' && entry->d_name[0] >= 'A') {
                        maxsize +=  buf.st_size;
                }
            }
        }
    }
    printf("%llu\n", maxsize);
    closedir(d);
    return 0;
}
