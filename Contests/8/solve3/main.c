#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv)
{
    enum { STARTING_YEAR = 1900};
    FILE *f;
    f = fopen(argv[1], "r");
    int year, mon;
    struct tm ttm1;
    struct tm ttm2;
    memset(&ttm1, 0, sizeof(ttm1));
    memset(&ttm2, 0, sizeof(ttm2));
    ttm1.tm_isdst = -1;
    ttm2.tm_isdst = -1;
    if (fscanf(f, "%d/%d/%d %d:%d:%d", &year, &mon,
        &ttm1.tm_mday, &ttm1.tm_hour, &ttm1.tm_min, &ttm1.tm_sec) != 6) {
            return 0;
    }
    ttm1.tm_year = year - STARTING_YEAR;
    ttm1.tm_mon = mon - 1;
    while (fscanf(f, "%d/%d/%d %d:%d:%d", &year, &mon,
        &ttm2.tm_mday, &ttm2.tm_hour, &ttm2.tm_min, &ttm2.tm_sec) == 6) {
            ttm2.tm_year = year - STARTING_YEAR;
            ttm2.tm_mon = mon - 1;
            printf("%0.f\n", difftime(mktime(&ttm2), mktime(&ttm1)));
            memset(&ttm1, 0, sizeof(ttm1));
            ttm1.tm_year = ttm2.tm_year;
            ttm1.tm_mon = ttm2.tm_mon;
            ttm1.tm_mday = ttm2.tm_mday;
            ttm1.tm_hour = ttm2.tm_hour;
            ttm1.tm_min = ttm2.tm_min;
            ttm1.tm_sec = ttm2.tm_sec;
            memset(&ttm2, 0, sizeof(ttm2));
            ttm1.tm_isdst = -1;
            ttm2.tm_isdst = -1;
    }
    return 0;
}
