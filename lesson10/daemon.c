/*
 ********************************************************************************
 *      Copyright (C), 2015-2115, Xhy Tech. Stu.
 *
 *      FileName   : daemon.c
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
 * \brief  daemon process
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
     
#define MAXFILE 65535

/**
 * \brief main entry
 */ 
 
int main(void)
{
    pid_t pid;

    int fd;
    int i;

    char flag = 1;
    
    char *buf = "I am daemon !\n";

    /* create child process */
    pid = fork();

    if (pid < 0) {
        printf("Create child process error !\n");
        exit(1);
    } else if (pid > 0) {
        exit(0);
    } 

    /* get away from the teminal */
    setsid();

    /* change work directory */
    chdir("/");

    /* clear mask */
    umask(0);

    /* close file id */
    for (i=0; i<MAXFILE; i++) {
        close(i);
    }

    while (1) {
        fd = open("/tmp/daemon.log", 
                  O_CREAT|O_WRONLY|O_APPEND, 
                  0664);

        if ((1 == flag) && (fd < 0)) {
            printf("Open file error !\n");
            flag = 0;
            exit(0);
        }

        write(fd, buf, strlen(buf));
        close(fd);
        sleep(1);
    }

    return 0;
}

/* end of file */