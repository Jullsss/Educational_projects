#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INC 10

 /*Íàïèñàòü ïðîãðàììó, îïðåäåëÿþùóþ, êàêàÿ èç ñòðîê ÷àùå äðóãèõ
âñòðå÷àåòñÿ â äàííîì ôàéëå. */

int main(int argc, char **argv)
{
    if (argc < 2) {
        exit (1);
    }
    FILE *f;
    if ((f = fopen(argv[1], "r")) == NULL) {
        exit (1);
    }
    char  **text = NULL;
    char c;
    int flag = 1;

    int size = INC;
    int i = 0, j = 0, k = 0;

    int n = INC;

    text = (char**) malloc(n * sizeof(char*));

    while (1) {
        char *buf = (char*) calloc(size, sizeof(char));
        while ((c = fgetc(f)) != '\n' && c != EOF && c != ' ') {
            flag = 0;
            if (i > size - 1) {
                size += INC;
                buf = (char*) realloc(buf, size*sizeof(char*));
            }
            buf[i++] = c;
        }
        if (j + 1 >= n) {
            n += INC;
            text = (char**) realloc(text, n * sizeof(char*));
        }
        text[j] = (char*) calloc(i + 1, sizeof(char));
        strcpy(text[j], buf);
        j++;
        i = 0;
        size = INC;
        if (c == '\n' && flag != 1) {
            flag = 1;
        } else if (c == EOF) {
            free(buf);
            break;
        }
        free(buf);
    }

    int l;
    for (k = 0; k < j; k++) {
        for (l = 0; l < j - 1; l++) {
            if (strcmp(text[l],text[l + 1]) > 0) {
                char *tmp = text[l];
                text[l] = text[l + 1];
                text[l + 1] = tmp;
            }
        }
    }
    char *s;
    k = 1;
    int t = 0;
    for (i = 0; i < j - 1; i++) {
        if (strcmp(text[i], text[i + 1]) == 0) {
            t++;
        } else {
            t = 0;
        }
        if (t > k) {
            s = text[i];
            k = t;
        }
    }
    fputs(s, stdout);
    printf("\n");
    for (i = 0; i < j; i++) {
        free(text[i]);
    }
    free(text);
    fclose(f);
    return 0;
}

