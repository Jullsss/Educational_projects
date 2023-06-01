#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>

#define INC 10
#define MAX 128

void free_memory(char **words, int end) {
    int q;
    for (q = 0; q < end; q++) {
        free(words[q]);
    }
}

void exit_pr(char **words, char *str, int j) {
    free_memory(words, j);
    free(str);
    free(words);
}

void exe(char **words, char *str, int j) {
    execvp(words[0], words);
    printf("ERROR: not executed execvp\n");
    exit_pr (words, str, j);
    exit (1);
}

void cd_pr(char **words, char *str, int j) {
    if (j > 2) {
        printf("ERROR: too many argument\n");
    } else if (j == 2) {
        if (chdir(words[1]) == -1) {
            printf("ERROR\n");
            exit_pr (words, str, j);
            exit (1);
        }
    } else if (j == 1) {
        if (chdir(getenv("HOME")) == -1) {
            exit_pr (words, str, j);
            exit (1);
        }
    }
}

void check_pid (char **words, char *str, int j) {
    printf("ERROR: no process created\n");
    exit_pr (words, str, j);
    exit (1);
}

void check_pr (char **words, int l, int r, int d, int fd1, int fd2) {
    if (l != 0) {
        dup2 (fd1, 0);
        close (fd1);
        words[l] = NULL;
    }
    if (d != 0) {
        dup2 (fd2, 1);
        close (fd2);
        words[d] = NULL;
    }
    if (r != 0) {
        dup2 (fd2, 1);
        close (fd2);
        words[r] = NULL;
    }
}

void dup_pr (char **words, char *str, int j, int l, int r, int d) {
    int fd1 = 0, fd2 = 0;
    int op = 0;
    if (l != 0) {
        if ((fd1 = open(words[l], O_RDONLY)) == -1) {
            printf("ERROR: I couldn't open the file for reading\n");
            free_memory(words, j);
            op = 1;
        }
    }
    if (r != 0 && op != 1) {
        if ((fd2 = open(words[r], O_WRONLY | O_TRUNC | O_CREAT)) == -1) {
            printf("ERROR: I couldn't open the file\n");
            free_memory(words, j);
            op = 1;
        }
    }
    if (d != 0 && op != 1) {
        if ((fd2 = open(words[d], O_WRONLY | O_APPEND | O_CREAT)) == -1) {
            printf("ERROR: I couldn't open the file\n");
            free_memory(words, j);
            op = 1;
        }
    }
    if (op != 1) {
        pid_t pid;
        int status;
        if (!(pid = fork())) {
            check_pr (words, l, r, d, fd1, fd2);
            words[j] = NULL;
            exe(words, str, j);
        } else if (pid == -1) {
            check_pid(words, str, j);
        }
        while (wait(&status) != pid);
    }
}

void cmp_pr(char **words, char *str, int j, int l, int r, int d) {
    if (strcmp(words[0], "exit") == 0) {
        exit_pr(words, str, j);
        exit (0);
    } else if (strcmp(words[0], "cd") == 0) {
        cd_pr(words, str, j);
    } else {
        dup_pr (words, str, j, l, r, d);
    }
}

void conv_pr (char **words, int j, char *str, int l, int r, int d) {
    int fd[2];
    int i = 0, k = 0;
    pid_t pid;
    if (j <= 2 || words[0] == NULL) {
        printf ("ERROR\n");
        exit_pr(words, str, j);
        exit (1);
    }
    while (i < j) {
        pipe(fd);
        while (words[k] != NULL) k++;
        if ((pid = fork())) {
            if (pid == -1) {
                check_pid(words, str, j);
            }
            dup2 (fd[0], 0);
            close (fd[0]);
            close (fd[1]);
            i = ++k;
        } else {
            if (k < j - 1) dup2 (fd [1], 1);
            int fd1 = 0, fd2 = 0;
            int op = 0;
            if (l != 0) {
                if ((fd1 = open(words[l], O_RDONLY)) == -1) {
                    printf("ERROR: I couldn't open the file for reading\n");
                    free_memory(words, j);
                    op = 1;
                }
            }
            if (r != 0 && op != 1) {
                if ((fd2 = open(words[r], O_WRONLY | O_TRUNC | O_CREAT)) == -1) {
                    printf("ERROR: I couldn't open the file\n");
                    free_memory(words, j);
                    op = 1;
                }
            }
            if (d != 0 && op != 1) {
                if ((fd2 = open(words[d], O_WRONLY | O_APPEND | O_CREAT)) == -1) {
                    printf("ERROR: I couldn't open the file\n");
                    free_memory(words, j);
                    op = 1;
                }
            }
            check_pr (words, l, r, d, fd1, fd2);
            words[j] = NULL;
            close(fd[0]);
            close(fd[1]);
            exe(words + i, str, j);
        }
    }
    while (wait(NULL) != -1);
}

int main(void)
{
    int i = 0, n = INC, j = 0, m = 1;
    int commas = 0;

    int k = 0;

    int left = 0, right = 0, doght = 0;
    int flag = 0, sign = 0;
    int d = 0, r = 0, l = 0;

    int con = 0;
    int and = 0, or = 0;
    int back = 0;

    char c;
    char **words = (char**) calloc(m, sizeof(char*));

    printf ("Enter command: ");

    while (1) {
        char *str = (char *) calloc (n, sizeof(char));

        while ((c = getchar()) != '\n' && c != '<' && c != '>' && c != '|' && c != '&' && c != ';') {
            if (c == '"') {
                commas = (commas == 0) ? 1 : 0;
            } else {
                if (commas == 0) {
                    if (c == ' ') {
                        break;
                    }
                }
                if (i >= n - 1) {
                    n += INC;
                    str = (char *) realloc (str, n * sizeof(char));
                }
                str[i++] = c;
            }
        }

        if (c == '\n') {
            and = 0; or = 0;
            sign = 0;
        }

        if (c == '<') {
            left++; flag = 1;
            c = ' ';
        }
        if (c == '>') {
            if ((c = getchar()) == '>') {
                doght++; flag = 3;
            } else {
                ungetc(c, stdin);
                right++; flag = 2;
            }
            c = ' ';
        }

        if (c == '|') {
            if ((c = getchar()) == '|') {
                if (or != -1) or ++;
                c = '\n'; sign = 1;
            } else {
                ungetc(c, stdin);
                con++;
                if (j + 1 >= m) {
                    m += 1;
                    words = (char**) realloc(words, m * sizeof(char*));
                }
                words[j] = NULL;
                j++;
            }
        }

        if (c == '&') {
            if ((c = getchar()) == '&') {
                if (and != -1) and++;
                c = '\n'; sign = 1;
            } else {
                ungetc(c, stdin);
                back = 1;
            }
        }

        if (c == ';') {
            c = '\n'; sign = 1;
        }

        if (c == ' ' && strlen(str))  {
            if (i >= n - 1) {
                n += INC;
                str = (char *) realloc (str, n * sizeof(char));
            }
            str[i] = '\0';
            if (j + 1 >= m) {
                m += 1;
                words = (char**) realloc(words, m * sizeof(char*));
            }
            words[j] = (char*) calloc(i + 3, sizeof(char));

            if (back == 1) {
                printf ("ERROR: background process\n");
                exit_pr(words, str, j);
                exit (1);
            }
            if (flag == 1) {
                strcpy(words[j], "<\0");
            } else if (flag == 2) {
                strcpy(words[j], ">\0");
            } else if (flag == 3) {
                strcpy(words[j], ">>\0");
            }
            strcat(words[j], str);
            flag = 0;

            j++;
            i = 0; n = INC;
        } else if (c == '\n') {
            if (commas == 1) {
                printf("ERROR: one quote\n");
                free_memory(words, j);

            } else {
                if (strlen(str)) {
                    if (i >= n - 1) {
                        n += INC;
                        str = (char *) realloc (str, n * sizeof(char));
                    }
                    str[i] = '\0';
                    if (j + 1 >= m) {
                        m += 2;
                        words = (char**) realloc(words, m * sizeof(char*));
                    }
                    words[j] = (char*) calloc(i + 3, sizeof(char));

                    if (back == 1) {
                        printf ("ERROR: background process\n");
                        exit_pr(words, str, j);
                        exit (1);
                    }

                    if (flag == 1) {
                        strcpy(words[j], "<\0");
                    } else if (flag == 2) {
                        strcpy(words[j], ">\0");
                    } else if (flag == 3) {
                        strcpy(words[j], ">>\0");
                    }
                    strcat(words[j], str);
                    flag = 0;
                } else {
                    if (flag) {
                        printf ("ERROR: wrong\n");
                        exit_pr(words, str, j);
                        exit (1);
                    }
                    if (con == 0 && back == 0) {
                        flag = 0;
                    }
                    j--;
                }

                /*printf ("1. j %d\n", j);
                for (k = 0; k < j + 1; k++) {
                    printf ("%d %s\n", k, words[k]);
                }*/

                    if (left && strcmp(words[j], "<")) {
                        int left_dop = left;
                        for (k = 1; k <= j; k++) {
                            int tmp = strncmp(words[k], "<", 1);
                            if (left_dop > 1) {
                                if (tmp == 0) {
                                    words[k] = NULL;
                                    free(words[k]);
                                    left_dop--;
                                }
                            } else if (tmp == 0) {
                                l = k;
                            }
                        }
                        if (left != j && right == 0 && doght == 0) {
                            if (strncmp(words[l], "<", 1) == 0) {
                                words[l] = NULL;
                            }
                            left = 0;
                        }
                        if (left) {
                            for (k = 0; k < strlen(words[l]); k++) {
                                words[l][k] = words[l][k + 1];
                            }
                            words[l][k] = '\0';
                        }
                    }
                    //printf ("j %d\n", j);
                    if ((right + doght) && strcmp(words[j], ">>") && strcmp(words[j], ">")) {
                        for (k = 1; k < j + 1; k++) {
                            if (words[k] != NULL) {
                                if (right + doght > 1) {
                                    if (strncmp(words[k], ">>", 2) == 0) {
                                        words[k] = NULL;
                                        free(words[k]);
                                        doght--;
                                    } else if (strncmp(words[k], ">", 1) == 0) {
                                        words[k] = NULL;
                                        free(words[k]);
                                        right--;
                                    }
                                } else {
                                    if (strncmp(words[k], ">>", 2) == 0) {
                                        d = k;
                                    } else if ((strncmp(words[k], ">", 1)) == 0) {
                                        r = k;
                                    }
                                }
                            }
                        }
                        if (r > 0) {
                            for (k = 0; k < strlen(words[r]); k++) {
                                words[r][k] = words[r][k + 1];
                            }
                            words[r][k] = '\0';
                        }
                        if (d > 0) {
                            for (k = 0; k < strlen(words[d]) - 2; k++) {
                                words[d][k] = words[d][k + 2];
                            }
                            words[d][k] = '\0';
                        }
                    }
                if (j + 1 > 0) {
                    int status;
                    if (con == 0 && back == 0 && or == 0 && and == 0) {
                        cmp_pr (words, str, j + 1, l, r, d);
                    } else if (con > 0 && back == 0 && or == 0 && and == 0) {
                        pid_t pid;
                        if (!(pid = fork())) {
                            if (j + 1 >= m) {
                                m += 2;
                                words = (char**) realloc(words, m * sizeof(char*));
                            }
                            words[j + 1] = NULL;
                            conv_pr(words, j + 1, str, l, r, d);
                            exit_pr (words, str, j + 2);
                            exit(0);
                        } else if (pid == -1) {
                            check_pid(words, str, j + 1);
                        }
                        while (wait (&status) != pid);
                    } else if (back == 0 && or >= 0 && and >= 0) {
                        pid_t pid;
                        if (!(pid = fork())) {
                            //printf ("2. and %d sign %d\n", and, sign);
                            if (j + 1 >= m) {
                                m += 2;
                                words = (char**) realloc(words, m * sizeof(char*));
                            }
                            words[j + 1] = NULL;
                            execvp(words[0], words);
                            printf("ERROR: execvp\n");
                            exit_pr (words, str, j + 2);
                            exit (1);
                        } else if (pid == -1) {
                            check_pid(words, str, j + 1);
                        }
                        //printf ("1. and %d sign %d\n", and, sign);
                        waitpid (pid, &status, 0);
                        if (and) {
                            if (status) {
                                and = -1;
                                exit_pr (words, str, j + 1);
                                exit(1);
                            }
                        }
                        if (or) {
                            if (!status) {
                                //exit (0);
                                or = -1;
                                exit_pr (words, str, j + 1);
                                exit (0);
                            }
                        }
                    }
                    //printf ("11. and %d sign %d\n", and, sign);
                    if (back) {
                        pid_t pid;
                        if (!(pid = fork())) {
                            int fd = open("/dev/null", O_RDONLY);
                            dup2 (fd, 0);
                            close (fd);
                            sigset_t block_int;
                            sigemptyset (&block_int);
                            sigaddset (&block_int, SIGINT);
                            sigprocmask(SIG_BLOCK, &block_int, NULL);
                            if (con == 0) {
                                printf("pid %d\n", getpid());
                                cmp_pr (words, str, j + 1, l, r, d);
                            } else if (con > 0) {
                                if (j + 1 >= m) {
                                    m += 2;
                                    words = (char**) realloc(words, m * sizeof(char*));
                                }
                                words[j + 1] = NULL;
                                conv_pr(words, j + 1, str, l, r, d);
                            }
                            sigprocmask(SIG_UNBLOCK, &block_int, NULL);
                            printf ("pid = %d END\n", getpid());
                            exit_pr (words, str, j + 1);
                            exit(0);
                        } else if (pid != -1) {
                            waitpid(-1, &status, WNOHANG);
                        }
                    }
                }

            }
            free_memory(words, j + 1);

            j = 0; m = 1;
            i = 0; n = INC;
            commas = 0;
            left = 0; right = 0; doght = 0;
            l = 0; r = 0; d = 0;
            con = 0; back = 0;
            if (sign == 0)
                printf ("Enter command: ");
        }
        free (str);
    }
    free (words);
    return 0;
}
