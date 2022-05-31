#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <signal.h>
#include <pthread.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define MAXLEN 1024

#define ERR -1
#define SERVER_IP_ADDRESS "127.0.0.1"

bool connectStatus; // check the status connection
int sockD;          // global sock id for using in send & recive func

void *pollsend(void *args)
{
    char buff[MAXLEN];
    bzero(buff, MAXLEN);

    while (connectStatus)
    {
        scanf("%s", buff);
        printf("send: %s\n", buff);
        if (send(sockD, buff, strlen(buff) + 1, 0) == ERR)
        {
            printf("send failed\n");
        }
        if (!strcmp(buff, "exit"))
        {
            send(sockD, "exit", 4, 0);
            connectStatus = false;
            break;
        }

        bzero(buff, 1024);
    }
    return NULL;
}

void *pollrecv(void *args)
{
    char buff[MAXLEN];
    bzero(buff, MAXLEN);
    connectStatus = true;
    int bytes = 0;
    while ((bytes = recv(sockD, buff, MAXLEN, 0)) != ERR)
    {
        if (!bytes)
        {
            connectStatus = false;
            break;
        }
        printf("recived: %s\n", buff);
        if (!strcmp(buff, "exit"))
        {
            connectStatus = false;
            break;
        }
        bzero(buff, MAXLEN);
    }
    return NULL;
}

int main()
{
    sockD = socket(AF_INET, SOCK_STREAM, 0);
    if (sockD == -1)
    {
        printf("create socket failed\n");
        exit(1);
    }
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(3490);
    servAddr.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);

    int check_connect = connect(sockD, (struct sockaddr *)&servAddr, sizeof(servAddr));

    if (check_connect == ERR)
    {
        printf("connected failed\n");
        exit(1);
    }
    connectStatus = true;
    pthread_t _recv;
    pthread_t _send;
    pthread_create(&_recv, NULL, pollrecv, NULL);
    pthread_create(&_send, NULL, pollsend, NULL);
    pthread_join(_send, NULL); // until the recive finish
    pthread_kill(_send, 0);

    close(sockD);
    printf("exit\n");

    return 0;
}