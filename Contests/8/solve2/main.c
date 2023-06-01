#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv)
{
    enum {
        STARTING_YEAR = 1900,
        NUM_OF_DAYS_OF_WEEK = 7
    };
    struct tm ttm;
    int year;
    memset(&ttm, 0, sizeof(ttm));
    sscanf(argv[1], "%d", &year);
    sscanf(argv[2], "%d", &ttm.tm_mday);
    ttm.tm_year = year - STARTING_YEAR;
    ttm.tm_isdst = -1;
    mktime(&ttm);
    if (ttm.tm_wday == 0) {
        ttm.tm_wday = NUM_OF_DAYS_OF_WEEK;
    }
    year = ttm.tm_year + STARTING_YEAR;
    printf("%d %d %d %d\n", year, ttm.tm_mon + 1, ttm.tm_mday, ttm.tm_wday);
    return 0;
}
