/*
 ********************************************************************************
 *      Copyright (C), 2015-2115, Xhy Tech. Stu.
 *
 *      FileName   : tcp_server.c
 *
 *      Author     : X h y
 *
 *      Version    : 2.0
 *
 *      Date       : 05-14-2015
 *
 *      Description:
 ********************************************************************************
 */
 
/**
 * \file
 * \brief  tcp server
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define PORTNUM 1234
#define MSG_SIZE 128

/**
 * \brief main entry
 */      
 
int main(void)
{
    int sockfd;
    int newfd;

    pid_t pid;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    char buffer[MSG_SIZE];
    int  nbyte;
    int  addrlen;

    char running = 1;
    char flag   = 1;

    /* create socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (-1 == sockfd) {
        printf("Create socket error !\n");
        exit(1);
    }

    /* init address */
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(PORTNUM);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* bind address */
    bind(sockfd, 
         (struct sockaddr *)(&server_addr), 
         sizeof(struct sockaddr));

    /* listen port */
    listen(sockfd, 5);

    while (running) {
        /* wait connection request */
        printf("Wait client connection request !\n");
        addrlen = sizeof(struct sockaddr);
        newfd   = accept(sockfd, 
                         (struct sockaddr *)(&client_addr), 
                         &addrlen);
        
        if (-1 == newfd) {
            printf("Accept socket error !\n");
            exit(1);
        }
    
        printf("Server get connection from %s\n", 
               inet_ntoa(client_addr.sin_addr));

        /* creat child */
        if (0 == (pid = fork())) {
            flag = 1;

            while (flag) {
            /* receive data */
            nbyte = recv(newfd, buffer, MSG_SIZE, 0);
            buffer[nbyte] = '\0';

            if (0 == strncmp(buffer, "end", 3)) {
                flag = 0;
                printf("Disconnect with client !\n");

                /* close the connection */
                close(newfd);
            } else {
                printf("Server received : %s\n", buffer);
                bzero(buffer, MSG_SIZE);
            }  
            }    
        } else if (pid < 0) {
            printf("Fork error !\n");
        }
    }
    
    /* close the socket */
    close(sockfd);

    return 0;
}

/* end of file */
