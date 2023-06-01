#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define INC 10

void free_memory(char **array, int start, int end) {
    int q;
    for (q = start; q < end; q++) {
        free(array[q - start]);
    }
    free(array);
}

void exe(char **array, char **words, int start, int end) {
    array[end - start] = NULL;
    execvp(array[0], array);
    printf("ERROR: not executed execvp\n");
    free_memory(array, start, end);
    free_memory(words, 0, end);
    exit(1);
}

int main(void)
{
    int flag = 1, commas = 0, red = 0, blue = 0;

    int size = INC, n = INC;
    int i = 0, j = 0, max = 0, k = 0, lenmax = 0;
    int file1 = 0, filedop1 = -1;
    int file2 = 0, filedop2 = -1;

    char c;
    char **words = (char**) malloc(n * sizeof(char*));

    pid_t pid, pid1, pid2;
    int fd, status/*, st1*/;

    while (1) {
        char *buf = (char*) calloc(size, sizeof(char));
        while ((c = getchar()) != '\n' && c != EOF && c != ' ' && c != '"' && c != '|' && c != '<' && c  != '>') {
            flag = 0;
            if (i > size - 1) {
                size += INC;
                buf = (char*) realloc(buf, size * sizeof(char*));
            }
            buf[i++] = c;
        }
        if (c == '|') {
            blue = 1;
        }
        if (c == '>') {
            if ((c = getchar()) == '>') {
                red = 2;
            } else {
                ungetc(c, stdin);
                red = 1;
            }
            c = ' ';
        }
        if (c == '<') {
            red = 3;
            //c = ' ';
            //ungetc(c, stdin);
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
            //printf("%s\n", words[j]);
            if (red != 0) {
                file1 = j - max;
                filedop1++;
            }
            if (blue != 0) {
                file2 = j - max;
                filedop2++;
            }
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
            if (commas == 0 && red == 0 && blue == 0) {
                char **array = (char **) calloc ((j - max + 1), sizeof(char *));
                for (k = max; k < j; k++) {
                    array[k - max] = (char *) calloc (lenmax, sizeof (char));
                    strcpy(array[k - max], words[k]);
                    //printf("%s\n", array[k - max]);
                }
                if (strcmp(array[0], "exit") == 0) {
                    break;
                } else if (strcmp(array[0], "cd") == 0) {
                    if (k - max > 2) {
                        printf("ERROR: too many argument\n");
                    } else if (k - max == 2) {
                        if (chdir(array[1]) == -1) {
                            printf("ERROR\n");
                            free_memory(array, max, j);
                            free_memory(words, 0, j);
                            exit (1);
                        }
                    } else if (k - max == 1) {
                        if (chdir(getenv("HOME")) == -1) {
                            free_memory(array, max, j);
                            free_memory(words, 0, j);
                            exit (1);
                        }
                    }
                } else {
                    if (!(pid = fork())) {
                        exe(array, words, max, j);
                    } else if (pid == -1) {
                        printf("ERROR: no process created\n");
                        free_memory(array, max, j);
                        free_memory(words, 0, j);
                        exit (1);
                    }
                    while (wait(&status) != pid);
                }
                free_memory(array, max, j);
            } else if (commas == 0 && blue == 0) {
                char **array = (char **) calloc ((j - max + 1), sizeof(char *));
                for (k = max; k < j; k++) {
                    array[k - max] = (char *) calloc (lenmax, sizeof (char));
                    strcpy(array[k - max], words[k]);
                    //printf("%s\n", array[k - max]);
                }
                //printf("file: %s[%d]\n", array[file1 - filedop1], file1 - filedop1);
                //printf("j %d\nmax %d\n", j, max);
                int potok;
                if (red == 3) {
                    potok = 0;
                    if ((fd = open(array[file1 - filedop1], O_RDONLY)) == -1) {
                        printf("ERROR: I couldn't open the file for reading\n");
                    }
                } else if (red == 1) {
                    potok = 1;
                    if ((fd = open(array[file1 - filedop1], O_WRONLY | O_TRUNC | O_CREAT)) == -1) {
                        printf("ERROR: I couldn't open the file for writing\n");
                    }
                } else if (red == 2) {
                    potok = 1;
                    if ((fd = open(array[file1 - filedop1], O_WRONLY | O_APPEND | O_CREAT)) == -1) {
                        printf("ERROR: I couldn't open the file for writing\n");
                    }
                }
                if (!(pid = fork())) {
                    dup2 (fd, potok);
                    close (fd);
                    exe(array, words, max, j);
                } else if (pid == -1) {
                    printf("ERROR: no process created for writing\n");
                    free_memory(array, max, j);
                    free_memory(words, 0, j);
                    exit (1);
                } else {
                    while (wait(&status) != pid);
                }
            } else if (commas == 0) {
                char **array1 = (char **) calloc ((file2 - filedop2 + max + 1), sizeof(char *));
                char **array2 = (char **) calloc ((j - (file2 - filedop2 + max) + 1), sizeof(char *));
                for (k = max; k < j; k++) {
                    if (k < file2 - filedop2 + max) {
                        array1[k - max] = (char *) calloc (lenmax, sizeof (char));
                        strcpy(array1[k - max], words[k]);
                        //printf("%s\n", array[k - max]);
                    } else {
                        array2[k - max - (file2 - filedop2)] = (char *) calloc (lenmax, sizeof (char));
                        strcpy(array2[k - max - (file2 - filedop2)], words[k]);
                    }
                }
                if (blue == 1) {
                    int fidi[2];
                    if (pipe(fidi) < 0) {
                        printf("ERROR: pipe\n");
                        free_memory(array1, max, file2 - filedop2 + max);
                        free_memory(array2, file2 - filedop2 + max, j);
                        free_memory(words, 0, j);
                        exit(1);
                    }
                    if (!(pid1 = fork())) {
                        dup2 (fidi[1], 1);
                        close (fidi[0]);
                        close (fidi[1]);
                        array1[file2 - filedop2] = NULL;
                        execvp(array1[0], array1);
                        printf("ERROR: not executed execvp\n");
                        free_memory(array1, max, file2 - filedop2 + max);
                        free_memory(array2, file2 - filedop2 + max, j);
                        free_memory(words, 0, j);
                        exit(1);
                    } else if (pid1 == -1) {
                        printf("ERROR: no process created for writing\n");
                        free_memory(array1, max, file2 - filedop2 + max);
                        free_memory(array2, file2 - filedop2 + max, j);
                        free_memory(words, 0, j);
                        exit (1);
                    }
                    if (!(pid2 = fork())) {
                        dup2 (fidi[0], 0);
                        close (fidi[0]);
                        close (fidi[1]);
                        array2[j - file2 + filedop2 - max] = NULL;
                        execvp(array2[0], array2);
                        printf("ERROR: not executed execvp\n");
                        free_memory(array1, max, file2 - filedop2 + max);
                        free_memory(array2, file2 - filedop2 + max, j);
                        free_memory(words, 0, j);
                        exit (1);
                    } else if (pid2 == -1) {
                        printf("ERROR: no process created for writing\n");
                        free_memory(array1, max, file2 - filedop2 + max);
                        free_memory(array2, file2 - filedop2 + max, j);
                        free_memory(words, 0, j);
                        exit (1);
                    }
                    close(fidi[0]); close(fidi[1]);
                    wait(NULL); wait(NULL);
                    free_memory(array1, max, file2 - filedop2 + max);
                    free_memory(array2, file2 - filedop2 + max, j);
                }
            }

            max = j;
            commas = 0;
            red = 0;
            filedop1 = -1;
        } else if (c == EOF) {
            break;
        }
    }
    free_memory(words, 0, j);
    return 0;
}
