/*
 ********************************************************************************
 *      Copyright (C), 2015-2115, Xhy Tech. Stu.
 *
 *      FileName   : read.c
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
 * \brief read data from memory segment
 */

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
    
#define TEXT_SIZE  2048 

struct shared_use_at
{
    int writen_by_you;
    char some_text[TEXT_SIZE];
};

/**
 * \brief main entry
 */      

int main(int argc, char *argv[])
{
    int shmid;
    key_t key;

    int running = 1;

    struct shared_use_at *shared_stuff;

    if (argc < 2) {
        printf("usage: ./read shmid \n");
        exit(EXIT_FAILURE);
    }
            
    /* find the shared memory's shmid */
    shmid = atoi(argv[1]);

    /* attaches the shared memory segment */
    shared_stuff = (struct shared_use_at *) shmat(shmid, NULL, 0);
    shared_stuff-> writen_by_you = 0;

    printf("Wait the write process !\n");
    /* circulation */
    while (running) {
        while (1 == shared_stuff-> writen_by_you) {
            /**
             * \brief check the exit flag first
             *  if (0 == strncmp(buffer, "end", 3))
             *  there is is no buffer       
             */        
            if (0 == strncmp(shared_stuff-> some_text, 
                "end", 
                3)) {
                running = 0;
                printf("end process\n" );
                break;
            }

            /* printf the string from write process */
            printf("Write process write : %s", 
                shared_stuff-> some_text);
            shared_stuff-> writen_by_you = 0;
        }       
    }

    /* detaches the shared memory segment */
    shmdt((const void *)(shared_stuff));

    /* destroy the shared memory */
    shmctl(shmid, IPC_RMID, 0);

    return 1;

    exit(EXIT_SUCCESS);
}

/* end of file */