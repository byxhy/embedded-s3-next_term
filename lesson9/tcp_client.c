/*
 ********************************************************************************
 *      Copyright (C), 2015-2115, Xhy Tech. Stu.
 *
 *      FileName   : tcp_client.c
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

    char buffer[MSG_SIZE];

    char running = 1;
    
    /* create socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (-1 == sockfd) {
        printf("Create socket error !\n");
        exit(1);
    }

    
    /* init server address */
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(PORTNUM);
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    /* connect the server */
    if (-1 == connect(sockfd, 
                      (struct sockaddr *)(&server_addr), 
                      sizeof(struct sockaddr))) {
        printf("Connect server error !\n");
        exit(1);
    }

    while (running) {
        /* send data to server */
        printf("\nPlease input string: ");
        fgets(buffer, 128, stdin);
        send(sockfd, buffer, strlen(buffer), 0);

        if (0 == strncmp(buffer, "end", 3)) {
            running = 0;
            printf("\nClient stop !\n");
        } else {
            bzero(buffer, MSG_SIZE);
        }   
    }
 
    /* close the socket */
    close(sockfd);

    return 0;
}

/* end of file */