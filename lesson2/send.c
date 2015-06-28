/*
 ********************************************************************************
 *      Copyright (C), 2015-2115, Xhy Tech. Stu.
 *
 *      FileName   : send.c
 *
 *      Author     : X h y
 *
 *      Version    : 2.0
 *
 *      Date       : 05-10-2015
 *
 *      Description:
 ********************************************************************************
 */
 
/**
 * \file
 * \brief send messages to
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

struct msgt {
    long msgtype;
    char msgtext[1024];
    };

/**
 * \brief main entry
 */      
 
int main(void)
{
    int msgid;

    char str[1024];

    int running = 1;

    key_t key;
    struct msgt msgs;

    key = ftok("/home", 1);

    /* create message queue */
    msgid = msgget(key, IPC_CREAT | 0666);

    /* check is very important */ 
    if (-1 == msgid) {
        printf("msgget is failed !\n");
        exit(EXIT_FAILURE);
    }

    printf("please input the message.\n");  
    while (running) {
        printf("msgsnd:");
        /* input the message */
        fgets(str, 1024, stdin);
        
        msgs.msgtype = 1;
        strcpy(msgs.msgtext, str);

        /* send the message */
        msgsnd(msgid, &msgs, sizeof(struct msgt), 0);

        /* check the exit flag */
        if (0 == strncmp(str, "end", 3)) { 
            running = 0;
        }
    }

    /* delete the message queue */  
    msgctl(msgid, IPC_RMID, 0);

    return 0;   
}

/* end of file */