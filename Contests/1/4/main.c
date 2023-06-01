#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    int num;
    scanf("%d", &num);
    for (int i = 1; i <= num; i++) {
        if (i != num) {
            printf("%d ", i);
        } else {
            printf("%d\n", i);
        }
        if (i != num && fork()) {
            wait(NULL);
            _exit(0);
        }
    }
    return 0;
}
