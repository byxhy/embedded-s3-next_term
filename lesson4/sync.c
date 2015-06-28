/*
 ********************************************************************************
 *      Copyright (C), 2015-2115, Xhy Tech. Stu.
 *
 *      FileName   : sync.c
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
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_t thread[2];
pthread_mutex_t mut;
pthread_cond_t cond_ready = PTHREAD_COND_INITIALIZER;

int num = 0;

void *student_a(void *arg)
{
    int i = 0;

    for (i=0; i<5; i++) {
        /* sweep the floor one time */
        num++;

        printf("Times = %d\n", num);

        if (num >= 5) {
            printf("A has finished his work !\n");
            /* send signal to a */
            pthread_cond_signal(&cond_ready);
        }

        /* sleep 1 seconds*/
        sleep(1);
    }

    /* exit */
    pthread_exit(NULL);
}

void *student_b(void *arg)
{  
    pthread_mutex_lock(&mut);

    if (num < 5) {
        pthread_cond_wait(&cond_ready, &mut);
    }
    
    /* mop the floor */
    num = 0;

    pthread_mutex_unlock(&mut);
    printf("B has finished his work !\n");

    /* exit */
    pthread_exit(NULL);
}

/**
 * \brief main entry
 */      
 
int main(void)
{
    /* init the  thread lock*/
    pthread_mutex_init(&mut, NULL);

    /* create A thread */
    pthread_create(&thread[0], NULL, student_a, NULL);
    
    /* create B thread */
    pthread_create(&thread[1], NULL, student_b, NULL);

    /* wait A thread end */
    pthread_join(thread[0], NULL);

    /* wait B thread end */ 
    pthread_join(thread[1], NULL);

    return 0;
}

/* end of file */