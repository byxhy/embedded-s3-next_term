/*
 ********************************************************************************
 *      Copyright (C), 2015-2115, Xhy Tech. Stu.
 *
 *      FileName   : udp_client.c
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
 * \brief  tcp client
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
 
int main(int argc, char *argv[])
{
    if (2 != argc) {
        printf("Usage: %s server_ip\n", argv[0]);
        exit(1);
    }

    int sockfd;
    
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    char buffer[MSG_SIZE];

    char running = 1;

    /* create socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (-1 == sockfd) {
        printf("Create socket error !\n");
        exit(1);
    }

    /* init server address */
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port   = htons(PORTNUM);
    inet_aton(argv[1], &server_addr.sin_addr);

    /* send data */
    while (running)
    {
        printf("\nMessage:");
        fgets(buffer, MSG_SIZE, stdin);
        sendto(sockfd, 
               buffer, 
               strlen(buffer), 
               0, 
               (struct sockaddr *)(&server_addr),
               sizeof(struct sockaddr));

        /* check the exit flag */
        if(0 == strncmp(buffer, "end", 3)) { 
            running = 0;
            printf("Client stop !\n");
        } else {
            bzero(buffer, MSG_SIZE);
        }   
    }

    /* end the socket */
    close(sockfd);

    return 0;
}

/* end of file */