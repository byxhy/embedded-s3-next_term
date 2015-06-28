/*
 ********************************************************************************
 *      Copyright (C), 2015-2115, Xhy Tech. Stu.
 *
 *      FileName   : receive.c
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
 * \brief  receive messages from
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

    char msgtext_last[1024];

    int running = 1;

    key_t key;
    struct msgt msgs;

    key = ftok("/home", 1);

    /* open message queue */
    msgid = msgget(key, IPC_EXCL);

    /* check is very important */ 
    if (-1 == msgid) {
        printf("Don't have message !\n");
        exit(EXIT_FAILURE);
    }

    while (running) {
        /* check the exit flag */
        if (0 == strncmp(msgs.msgtext, "end", 3)) { 
            running = 0;
            break;
        }

        /* receive message from message queue */
        msgrcv(msgid, &msgs, sizeof(struct msgt), 4, 0);

        /* 
         *  if the message is same 
         *  of the last message,
         *  do not print
         */
        if (0 == strncmp(msgs.msgtext, 
                msgtext_last, 
                sizeof(msgtext_last))) { 
            
        } else {
            strcpy(msgtext_last, msgs.msgtext);

            printf("msgrcv: %s", msgs.msgtext);
        }   
    }

    return 0;   
}

/* end of file */