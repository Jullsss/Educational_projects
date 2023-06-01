#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_INCREMENT 10

int main(void) {
    char **words;
    char *buffer;
    unsigned wordCounter = 0;
    unsigned length;
    unsigned size = SIZE_INCREMENT;
    int i = 0, j;
    int n = 128;
    char c;

    words = (char**) malloc(size*sizeof(char*));

    do {
        buffer = (char*) calloc(n, sizeof(char));
        while ((c = getchar()) != '\n' && c != EOF) {
            if (i > n - 1) {
                n += SIZE_INCREMENT;
                buffer = (char*) realloc(buffer, n*sizeof(char*));
            }
            buffer[i++] = c;
        }
        length = strlen(buffer);
        if (wordCounter >= size) {
            size += SIZE_INCREMENT;
            words = (char**) realloc(words, size*sizeof(char*));
        }
        words[wordCounter] = (char*) malloc(length + 1);
        strcpy(words[wordCounter], buffer);
        wordCounter++;
        i = 0; n = 128;
        if (c == EOF) {
            break;
        }
        free(buffer);
    } while(1);

    for (i = 0; i < wordCounter; i++) {
        for (j = 0; j < wordCounter - 1; j++) {
            if (strcmp(words[j], words[j + 1]) > 0) {
                char *tmp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = tmp;
            }
        }
    }

    for (i = 0; i < wordCounter; i++) {
        printf("%s\n", words[i]);
    }
    getchar();

    for (i = 0; i < wordCounter; i++) {
        free(words[i]);
    }
    free(words);
    return 0;
}
