#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

#define INC 10

//server

int main(int argc, char **argv)
{
    struct { //описание структуры сообщения
        long mestype;
        char mes[100];
    } messageto;
    struct { //описание структуры сообщения
        long mestype;
        long mes;
    } messagefrom;

    key_t key;
    int mesid;

    key = ftok("example", 'r');
    mesid = msgget (key, 0666 | IPC_CREAT);

    while (1) {
        //проверка поступления новых сообщений в неблокирующем режиме
        if (msgrcv(mesid, &messagefrom, sizeof(messagefrom) - sizeof(long), 1, IPC_NOWAIT) <= 0) continue;
        //обработка запроса
        messageto.mestype = messagefrom.mes;

        int i = 0, n = INC;

        char c;
        char *str = (char *) calloc (n, sizeof(char));

         while ((c = getchar()) != '\n') {
            if (i >= n - 1) {
                n += INC;
                str = (char *) realloc (str, n * sizeof(char));
            }
            str[i++] = c;
        }

        str[i] = '\0';

        strcpy (messageto.mes, str);
        //отправка ответа
        msgsnd(mesid, &messageto, sizeof(messageto) - sizeof(long), 0);
        if (strcmp (messageto.mes, "END") == 0) {
            break;
        }
        free (str);
    }
    msgctl (mesid, IPC_RMID, 0);
    return 0;
}
