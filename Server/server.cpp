#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cstring>
#include <netinet/in.h>
#include <memory.h>
#include <errno.h>
#define PORT 8080
#define BUFLEN 1024
#define EXIT_FAILURE 1

using namespace std;

class Server {
    int ServerSocket;
    socklen_t ServerLen;
    sockaddr_in ServerAddress;
    int port;
public:
    Server (int port = PORT) {
        if ((ServerSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }
        ServerAddress.sin_family = AF_INET;
        ServerAddress.sin_port = htons(port);
        ServerAddress.sin_addr.s_addr = inet_addr ("127.0.0.1");
        this->port = port;
        ServerLen = sizeof(ServerAddress);
    }
    void set_port (int port) {
        ServerAddress.sin_port = htons(port);
    }
    int get_port () const {
        return port;
    }
    int get_socket () const {
        return ServerSocket;
    }
    void socket_bind () const {
        if (bind(ServerSocket, (struct sockaddr*) &ServerAddress, ServerLen) < 0) {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
    }
    void socket_listen () const {
        if ((listen(ServerSocket, 5)) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }
    }
};

class Client {
    sockaddr_in ClientAddress;
    int ClientSocket;
    socklen_t ClientAddrLen;
public:
    Client () {
        ClientAddrLen = sizeof(ClientAddress);
    }
    int socket_accept (int ServerSocket) {
        ClientSocket = accept(ServerSocket, (struct sockaddr*) &ClientAddress, &ClientAddrLen);
        if (ClientSocket < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        return ClientSocket;
    }
    int get_client () const {
        return ClientSocket;
    }
    void ProcessClientRequest(int ClientSocket) {
        char buf[BUFLEN];
        for (int i = 0; i < BUFLEN; i++) {
            buf[i] = 0;
        }
        int rc = recv(ClientSocket, buf, BUFLEN, 0);
        if (rc < 0) {
            if (shutdown(ClientSocket, 1) < 0) {
                perror("Error calling shutdown");
                exit(EXIT_FAILURE);
            }
            close (ClientSocket);
            perror("Can't receive data.");
            exit(EXIT_FAILURE);
        }
        int i = 5, len = 0;
        int flag = 0;
        while (buf[i] && buf[i++] != ' ') {
            if (buf[i] == '.') {
                if (strncmp (buf + i, ".txt", 4) == 0 ) {
                    flag = 1;
                } else if (strncmp (buf + i, ".cpp", 4) == 0 ){
                    flag = 1;
                } else {
                    flag = 0;
                }
            }
        }
        buf[i - 1] = 0;
        cout << buf << endl;
        int fd;

        if ((fd = open(buf + 5, O_RDONLY)) < 0) {
            perror("Error 404");
            fd = open ("Error.txt", O_RDONLY);
            len = lseek(fd, 0, SEEK_END);
            lseek(fd, 0, 0);
            strcpy(buf, "HTTP/1.1 404 PageNotFound\nAllow: GET\nServer: Yulia/0.1\nConnection: keep-alive\nContent-type:text/html\nContent-length: ");
        } else if (flag == 1) {
            len = lseek(fd, 0, SEEK_END);
            lseek(fd, 0, 0);
            strcpy(buf, "HTTP/1.1 200 ServerYulia\nAllow: GET\nServer: Yulia/0.1\nConnection: keep-alive\nContent-type:text/plain\nContent-length: ");
        } else {
            len = lseek(fd, 0, SEEK_END);
            lseek(fd, 0, 0);
            strcpy(buf, "HTTP/1.1 200 ServerYulia\nAllow: GET\nServer: Yulia/0.1\nConnection: keep-alive\nContent-type:text/html\nContent-length: ");
        }
        char *s = new char[11];
        sprintf (s, "%d", len);
        strcat (buf, s);
        strcat (buf, "\n\n");
        delete [] s;
        len = strlen(buf);
        cout << buf << endl;
        send(ClientSocket, &buf, len, 0);
        while ((len = read(fd, buf, BUFLEN)) > 0) {
            send(ClientSocket, &buf, len, 0);
        }
        if (shutdown(ClientSocket, 1) < 0) {
            perror("Error calling shutdown");
            exit(EXIT_FAILURE);
        }
        close (ClientSocket);
    }
};

int main()
{
    Server server(8900);
    server.socket_bind();
    server.socket_listen();
    Client client;
    while (1) {
        int fd = client.socket_accept(server.get_socket());
        client.ProcessClientRequest(fd);
    }
    return 0;
}


