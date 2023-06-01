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

//client

int main(int argc, char **argv)
{
    struct { //описание структуры сообщения
        long mestype;
        char mes[100];
    } messagefrom;

    struct { //описание структуры сообщения
        long mestype;
        long mes;
    } messageto;

    key_t key;
    int mesid;

    long pid = getpid();
    key = ftok("example", 'r');
    mesid = msgget (key, 0); //присоединение к очереди сообщений

    messageto.mestype = 1;
    messageto.mes = pid;

    while (1) {
        msgsnd(mesid, &messageto, sizeof(messageto) - sizeof(long), 0); //отправка запроса
        //ожидаем поступления ответного сообщения в неблокирующнм режиме (активное ожидание)
        while (msgrcv(mesid, &messagefrom, sizeof(messagefrom) - sizeof(long), pid, IPC_NOWAIT) <= 0);
        //сообщение получено
        printf ("%s\n", messagefrom.mes);
        if (strcmp (messagefrom.mes, "END") == 0) {
            break;
        }
    }

    return 0;
}
