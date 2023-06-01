#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/* ��������� ���������� �����.
�������� ���������-��������� ���������� �����, �������
�������� ������������������ �� n ���������� �������� c (n <= 128) �� ���� ������ (-n �).
���� ������ ���������, �� ��������� ��� ��� ����.
�������, ��� ���� �������� � �������� ����� �� ��������� 127.
����� ��������� ����� � �����-���������� - � ��������� ������.
����� �� ������ � ������������ ����� ������ ���� ����� ��, ��� � � ��������� �����.
� ������ ������ (������� ������, �������� � ��������� � �.�.) �������� �� ������ � ���������. */

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
