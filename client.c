/*
 * Protocoale de comunicatii
 * Laborator 7 - TCP
 * Echo Server
 * client.c
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include "helpers.h"

int main(int argc, char *argv[])
{
    int sockfd = 0;
    char buf[BUFLEN];
    struct sockaddr_in serv_addr; 

    if(argc != 3)
    {
        printf("\n Usage: %s <ip> <port>\n", argv[0]);
        return 1;
    }

    // deschidere socket
    int client = socket(AF_INET | PF_INET,SOCK_STREAM,0);

    // completare informatii despre adresa serverului
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // conectare la server
    connect(client,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr));

    // citire de la tastatura, trimitere de cereri catre server, asteptare raspuns
    char poz[BUFLEN];
    recv(client,poz,BUFLEN,0);
    int k1 = 0; k2 = 0
    while(strcmp(buf,"stop") != 0) {
        k1 = 0; k2 = 0;

        if(strcmp(poz,"1") == 0){
            scanf("%s", buf);
            send(client,buf,BUFLEN,0);
            recv(client,buf,BUFLEN,0);
            if(k2 == 0){
                printf("CLIENT got: %s\n",buf);
                k2 = 1;
            }
        }
        else{
            recv(client,buf,BUFLEN,0);
            if(k1 == 0){
                printf("CLIENT got: %s\n",buf);
                k1 = 1;
            }
            scanf("%s", buf);
            send(client,buf,BUFLEN,0);
        }
        
    }
    printf("CLIENT STOP\n");
    // inchidere socket
    close(socket);
    return 0;
}
