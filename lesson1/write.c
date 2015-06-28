/*
 ********************************************************************************
 *      Copyright (C), 2015-2115, Xhy Tech. Stu.
 *
 *      FileName   : wtite.c
 *
 *      Author     : X h y
 *
 *      Version    : 2.0
 *
 *      Date       : 05-08-2015
 *
 *      Description:
 ********************************************************************************
 */
 
/**
 * \file
 * \brief allocates a shared memory segment
 */

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
    
#define TEXT_SIZE  2048 

struct shared_use_at
{
    int written_by_you;
    char some_text[TEXT_SIZE];
};

/**
 * \brief main entry
 */      
 
int main(void)
{
    int shmid;
    key_t key;

    int running = 1;

    struct shared_use_at *shared_stuff;

    char buffer[TEXT_SIZE];

    /* allocates a shared memory */
    key = ftok("/home", 1);
    shmid = shmget(key, 
               sizeof(struct shared_use_at), 
               IPC_CREAT | 0664);

    if (-1 == shmid) {
        printf("Create shared memory failed !\n");
        exit(EXIT_FAILURE);
    }

    printf("shmid = %d\n", shmid);

    /* attaches the shared memory segment */
    shared_stuff = (struct shared_use_at *) shmat(shmid, NULL, 0);
    
    /* circulation */
    while (running) {
        while (1 == shared_stuff-> written_by_you) {
            sleep(1);
            printf("Wait the read process !\n");
        }
        
        printf("input string:");

        /* read data from keyboard */
        fgets(buffer, TEXT_SIZE, stdin);

        /* write the data to shared memory */
        strncpy(shared_stuff-> some_text, buffer, TEXT_SIZE);
        shared_stuff-> written_by_you = 1;

        /* check the exit flag */
        if (0 == strncmp(buffer, "end", 3)) { 
            running = 0;
        }
    }

    /* detaches the shared memory segment */
    shmdt((const void *)(shared_stuff));

    return 1;

    exit(EXIT_SUCCESS);
}

/* end of file */