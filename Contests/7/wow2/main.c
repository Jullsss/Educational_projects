#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum
{
    STARTING_YEAR = 1900,
    ZERO_YEAR = 1925,
    ZERO_MONTH = 10,
    ZERO_DAY = 7,
    NUM_OF_SEC = 86400,
    NUM_OF_DAY = 30,
    NUM_OF_MON = 12
};

int main(void)
{
    int year, mon, day;
    unsigned long long diff, t;
    struct tm start_time;
    struct tm time;
    memset(&start_time, 0, sizeof(start_time));
    memset(&time, 0, sizeof(time));
    start_time.tm_year = ZERO_YEAR - STARTING_YEAR;
    start_time.tm_mon = ZERO_MONTH - 1;
    start_time.tm_mday = ZERO_DAY;
    start_time.tm_isdst = 1;
    while (scanf("%d%d%d", &year, &mon, &time.tm_mday) == 3) {
        time.tm_year = year - STARTING_YEAR;
        time.tm_mon = mon - 1;
        time.tm_isdst = -1;
        diff = (unsigned long long)difftime(mktime(&time), mktime(&start_time));
        t = diff / NUM_OF_SEC;
        year = t / NUM_OF_MON;
        year = year / NUM_OF_DAY;
        year += 1;
        t %= (NUM_OF_MON * NUM_OF_DAY);
        mon = t / NUM_OF_DAY + 1;
        t %= NUM_OF_DAY;
        day = t + 1;
        printf("%d %d %d\n", year, mon, day);
    }
    return 0;
}
