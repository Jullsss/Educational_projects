#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Ïðîãðàììà. Â äàííîì ôàéëå óïîðÿäî÷èòü âñå ñòðîêè ïî âîçðàñòàíèþ èõ äëèí.
Èìÿ ôàéëà è ìàêñèìàëüíàÿ äëèíà ñòðîêè çàäàþòñÿ â êîìàíäíîé
ñòðîêå. */

int main(int argc, char **argv)
{
    if (argc < 3) {
        exit (1);
    }
    FILE *f1, *f2;
    if ((f1 = fopen(argv[1], "r")) == NULL) {
        exit (1);
    }
    int flag = 0;
    int MAX = 0;
    char *s = argv[2];
    while (*s) {
        int x = *s - '0';
        if (x >= 0 && x <= 9) {
            MAX *= 10;
            MAX += x;
            s++;
        } else {
            flag = 1;
            break;
        }
    }
    if (flag == 1) {
        return 0;
    }
    char  **text = NULL;
    int sz = 0;
    char buf[MAX];
    while (fgets(buf, MAX - 1, f1)) {
        text = (char **) realloc(text, (sz + 1) * sizeof(char *));
        text[sz] = (char *) malloc (MAX * sizeof(char));
        strcpy(text[sz], buf);
        sz++;
    }
    if (text[sz - 1][strlen(text[sz - 1]) - 1] != '\n') {
        text[sz - 1][strlen(text[sz - 1]) - 1] = '\n';
    }
    int i, j;
    for (i = 0; i < sz - 1; i++) {
        for (j = i + 1; j < sz; j++) {
            if (strlen(text[i]) > strlen(text[j])) {
                char *tmp = text[i];
                text[i] = text[j];
                text[j] = tmp;
            }
        }
    }
    if ((f2 = fopen("b.txt", "w")) == NULL) {
        exit (1);
    }
    i = 0;
    while (fprintf(f2, "%s", text[i])) {
        if (i++ == sz - 1) {
            break;
        }
    }
    for (i = 0; i < sz; i++) {
        free(text[i]);
    }
    free(text);
    fclose(f1);
    fclose(f2);
    return 0;
}

