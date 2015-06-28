/*
 ********************************************************************************
 *      Copyright (C), 2015-2115, Xhy Tech. Stu.
 *
 *      FileName   : udp_server.c
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
 * \brief  udp client
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
    
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    char buffer[MSG_SIZE];
    int  addr_len;
    int  nbyte;

    char running = 1;

    /* create socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

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

    printf("Wait client connection request !\n");

    /* receive data */
    while (running) {
        addr_len = sizeof(struct sockaddr);
        bzero(buffer, sizeof(buffer));
        nbyte = recvfrom(sockfd, 
                         buffer, 
                         MSG_SIZE, 
                         0, 
                         (struct sockaddr *)(&client_addr),
                         &addr_len);
        buffer[nbyte] = '\0';

        if (0 == strncmp(buffer, "end", 3)) { 
            running = 0;
            printf("Server stop !\n");
        } else {
            printf("Server received : %s\n", buffer);
        }
    }

    /* end the socket */
    close(sockfd);

    return 0;
}

/* end of file */