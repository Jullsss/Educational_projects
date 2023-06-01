#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define INC 10

int main(void)
{
    char **words = NULL;
    char c;
    int flag = 1, commas = 0;

    int size = INC;
    int i = 0, j = 0, max = 0, k = 0, lenmax = 0;

    int n = INC;
    words = (char**) malloc(n * sizeof(char*));

    pid_t pid;
    int status;

    while (1) {
        char *buf = (char*) calloc(size, sizeof(char));
        while ((c = getchar()) != '\n' && c != EOF && c != ' ' && c != '"') {
            flag = 0;
            if (i > size - 1) {
                size += INC;
                buf = (char*) realloc(buf, size * sizeof(char*));
            }
            buf[i++] = c;
        }
        if (c == '"') {
            commas = 1;
            while ((c = getchar()) != '\n' && c != EOF && c != '"') {
                if (i > size - 1) {
                    size += INC;
                    buf = (char*) realloc(buf, size * sizeof(char*));
                }
                buf[i++] = c;
            }
            if (c == '"') {
                commas = 0;
            } else if (c == '\n' || c == EOF) {
                printf("ERROR: one quote\n");
            }
        }
        if (strlen(buf)) {
            flag = 0;
            if (j + 1 >= n) {
                n += INC;
                words = (char**) realloc(words, n * sizeof(char*));
            }
            words[j] = (char*) calloc(i + 1, sizeof(char));
            buf[i] = '\0';
            strcpy(words[j], buf);
            if (i + 1 > lenmax) {
                lenmax = i + 1;
            }
            j++;
            i = 0;
            size = INC;
        }
        free(buf);
        if (c == ' ' && flag == 0) {
            flag = 1;
        } else if (c == '\n' && flag == 0) {
            flag = 1;
            if (commas == 0) {
                char **array = (char **) calloc ((j - max + 1), sizeof(char *));
                for (k = max; k < j; k++) {
                    array[k - max] = (char *) calloc (lenmax, sizeof (char));
                    //if (strcmp(words[k], "") != 0) {
                        strcpy(array[k - max], words[k]);

                    //}
                }
                if (strcmp(array[0], "exit") == 0) {
                    break;
                } else if (strcmp(array[0], "cd") == 0) {
                    if (k - max > 2) {
                        printf("ERROR: too many argument\n");
                    } else if (k - max == 2) {
                        if (chdir(array[1]) == -1) {
                            printf("ERROR\n");
                            exit (1);
                        }
                    } else if (k - max == 1) {
                        if (chdir(getenv("HOME")) == -1) {
                            exit (1);
                        }
                    }
                } else {
                    if (!(pid = fork())) {
                        array[j - max] = NULL;
                        execvp(array[0], array);
                        printf("ERROR: not executed execvp\n");
                        exit(1);
                    } else if (pid == -1) {
                        printf("ERROR: no process created\n");
                        exit (1);
                    }
                    while (wait(&status) != pid);
                }
                for (k = max; k < j; k++) {
                    free(array[k - max]);
                }
                free(array);
            }
            max = j;
            commas = 0;
        } else if (c == EOF) {
            break;
        }
    }

    for (k = 0; k < j; k++) {
        free(words[k]);
    }
    free(words);
    return 0;
}

