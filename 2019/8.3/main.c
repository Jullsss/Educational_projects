#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/* Упаковщик текстового файла.
Написать программу-упаковщик текстового файла, который
заменяет последовательность из n одинаковых символов c (n <= 128) на пару байтов (-n с).
Если символ одиночный, то оставляем его как есть.
Считаем, что коды символов в пакуемом файле не превышают 127.
Имена пакуемого файла и файла-результата - в командной строке.
Права на доступ к создаваемому файлу должны быть такие же, как и у исходного файла.
В случае ошибок (большой символ, проблемы с открытием и т.п.) сообщить об ошибке и завершить. */

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("ERROR\n");
        return 0;
    }
    int fd1, fd2;
    if ((fd1 = open(argv[1], O_RDONLY)) == -1) {
        printf("ERROR\n");
        return 0;
    }
    if ((fd2 = open(argv[2], O_WRONLY | O_TRUNC)) == -1) {
        printf("ERROR\n");
        return 0;
    }
    char c, let;
    int n = 1;
    if (read(fd1, &let, 1) == -1) {
        printf("ERROR\n");
        return 0;
    }
    while (1) {
        int k;
        if ((k = read(fd1, &c, 1)) == -1) {
            printf("ERROR\n");
            return 0;
        }
        if (k == 0) {
            break;
        }
        if (c == '\n') {
            break;
        }
        if (c == let) {
            n++;
        } else {
            char x;
            while (n != 0) {
                if (n > 9) {

                }

            }
            if (write(fd2, &x, 1) == -1) {
                printf("ERROR\n");
                return 0;
            }
            if (write(fd2, &let, 1) == -1) {
                printf("ERROR\n");
                return 0;
            }
            n = 1;
            let = c;
        }
    }
    close (fd1);
    close (fd2);
    return 0;
}
