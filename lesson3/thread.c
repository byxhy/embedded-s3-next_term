/*
 ********************************************************************************
 *      Copyright (C), 2015-2115, Xhy Tech. Stu.
 *
 *      FileName   : thread.c
 *
 *      Author     : X h y
 *
 *      Version    : 2.0
 *
 *      Date       : 05-12-2015
 *
 *      Description:
 ********************************************************************************
 */
 
/**
 * \file
 * \brief  create a new thread
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t thread[2];

pthread_mutex_t mut;

int num = 0;

void *worker1(void *arg)
{
    int i = 0;

    printf("I am worker1 !\n");

    for (i=0; i<10; i++) {
        /* lock the  thread */
        pthread_mutex_lock(&mut);

        num++;

        /* unlock the  thread */
        pthread_mutex_unlock(&mut);

        printf("worker1 number is %d\n", num);
        sleep(1);
    }

    pthread_exit(NULL);
}

void *worker2(void *arg)
{
    int i = 0;

    printf("I am worker2 !\n");

    for (i=0; i<10; i++) {
        /* lock the  thread */
        pthread_mutex_lock(&mut);

        num++;

        /* unlock the thread */
        pthread_mutex_unlock(&mut);

        printf("worker2 number is %d\n", num);
        sleep(1);
    }

    pthread_exit(NULL);
}

/**
 * \brief main entry
 */      
 
int main(void)
{
    /* init the thread lock */
    pthread_mutex_init(&mut, NULL);

    /* create worker1 thread */
    pthread_create(&thread[0], NULL, worker1, NULL);

    /* create worker2 thread */
    pthread_create(&thread[1], NULL, worker2, NULL);

    /* wait worker1 thread  end */
    pthread_join(thread[0], NULL);

    /* wait worker2 thread  end */
    pthread_join(thread[1], NULL);

    return 0;
}

/* end of file */