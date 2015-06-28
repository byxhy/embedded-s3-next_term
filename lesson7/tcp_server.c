/*
 ********************************************************************************
 *      Copyright (C), 2015-2115, Xhy Tech. Stu.   
 *
 *      FileName   : tcp_server.c
 *
 *      Author     : X h y       
 *
 *      Version    : 2.0       
 *   
 *      Date       : 05-13-2015  
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

#define portnum 1234

/**
 * \brief main entry
 */      
 
int main(void)
{
    int sockfd;
    int newfd;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    char buffer[128];
    int  nbyte;
    int  addrlen;

    char runing = 1;

    /* create socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (-1 == sockfd) {
        printf("Create socket error !\n");
        exit(1);
    }

    /* init address */
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(portnum);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* bind address */
    bind(sockfd, (struct sockaddr *)(&server_addr), 
         sizeof(struct sockaddr));

    /* listen port */
    listen(sockfd, 5);

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
    while (runing) {
        /* receive data */
        nbyte = recv(newfd, buffer, 128, 0);
        buffer[nbyte] = '\0';

        if (0 == strncmp(buffer, "end", 3)) {
            runing = 0;
            printf("Server stop !\n");
        } else {
            printf("Server received : %s\n", buffer);
        }      
    }
    
    /* close the connection */
    close(newfd);
    
    /* close the socket */
    close(sockfd);

    return 0;
}

/* end of file */