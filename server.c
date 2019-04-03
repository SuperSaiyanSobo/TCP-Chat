/*
 * Protocoale de comunicatii
 * Laborator 7 - TCP
 * Echo Server
 * server.c
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#include "helpers.h"

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    char buf[BUFLEN];
    struct sockaddr_in serv_addr;
    socklen_t x = sizeof(struct sockaddr);
    if(argc != 3)
    {
        printf("\n Usage: %s <ip> <port>\n", argv[0]);
        return 1;
    }

    // deschidere socket
    int server1 = socket(AF_INET | PF_INET,SOCK_STREAM,0);

    // completare informatii despre adresa serverului
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // legare proprietati de socket
    bind(server1,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr));
   
    
    // ascultare de conexiuni
    listen(server1,2);

    // acceptarea unei conexiuni, primirea datelor, trimiterea raspunsului
    int csock1 = accept(server1,(struct sockaddr*)&serv_addr,&x);
    strcpy(buf,"1");
    send(csock1,buf,BUFLEN,0);
    
    int csock2 = accept(server1,(struct sockaddr*)&serv_addr,&x);
    strcpy(buf,"2");
    send(csock2,buf,BUFLEN,0);

    strcpy(buf,"");
    
    while(strcmp(buf,"stop") != 0) {

        recv(csock1,buf,BUFLEN,0);
        //printf("%s\n",buf);
        send(csock2,buf,BUFLEN,0);
        recv(csock2,buf,BUFLEN,0);
        //printf("%s\n",buf);
        send(csock1,buf,BUFLEN,0);
    }

    printf("Server stop\n");

    // inchidere socket(i)
    close(server1);
    return 0;
}
