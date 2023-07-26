/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: s364pate
 *
 * Created on March 3, 2023
 */

#include <stdio.h> /* printf */
#include <stdlib.h> /* exit, EXIT_FAILURE */
#include <pthread.h>
#include <unistd.h> /* getpid, usleep */

/*
 * 
 */
void * count(void *);

int globalNumber = 0;
//Create a mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int main(void) {
    int i;
    pthread_t counterThread[5];

    // Create the 5 threads
    for (i = 0; i < 5; i++) {
        if (pthread_create(&counterThread[i], NULL, count, NULL) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (i = 0; i < 5; i++) {
        if (pthread_join(counterThread[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }
    // Print the final value of the global variable after all threads have finished executing
    printf("globalNumber = %d\n", globalNumber);

    return (0);
}

void * count(void * junk) {
    int loopCount = 0;
    pthread_mutex_lock(&mutex1);
    while (loopCount < 10) {
        int tmpNumber = globalNumber;
        printf("counter: %d, Thread: %ld, PID: %d\n",
               tmpNumber, pthread_self(), getpid());
        tmpNumber = globalNumber;
        tmpNumber++;
        usleep(random() % 2);
        globalNumber = tmpNumber;
        loopCount++;
    }
    pthread_mutex_unlock(&mutex1);
    return (0);
}
