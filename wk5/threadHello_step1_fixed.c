// Name: Nicholas Fotinakes
// Date: 2022-04-05
// Title: Lab 5 - Multi-Threaded Applications: Step 2
// Description: This program is for Step 2 of Lab 5 that fixes the bugs of Step 1.
// In step 1, each thread had access to the "i" variable address in the for loop 
// creating a type of race condition. One way to solve this is to use separate id array 
// to store the iteration number and pass this upon thread creation to demonstrate a unique
// id per thread and avoid unwanted shared data. pthread_self() also could return a negative 
// number so that has been fixed by casting as pthread_t with %lu for more accuracy. 

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h> 

void *go(void *); 		// Declare go function
#define NTHREADS 10 		// Num of threads to create
pthread_t threads[NTHREADS]; 	// Array to hold created thread IDs

int main() { 
    int i; 
    int id[NTHREADS]; // Array to hold thread iteration ids (avoid race condition)
    for (i = 0; i < NTHREADS; i++) {
    	id[i] = i;	// assign 'i' value to array
        pthread_create(&threads[i], NULL, go, &id[i]); // Create thread with protected 'i' value
    }
    
    // Threads return and join
    for (i = 0; i < NTHREADS; i++) { 
        printf("Thread %d returned\n", i); 
        pthread_join(threads[i],NULL); 
    } 
    
    // Main thread prints when other threads complete
    printf("Main thread done.\n"); 
    return 0; 
} 

// Print thread with iteration passed from id array, pthread_self fixed to always return positive value
void *go(void *arg) { 
    printf("Hello from thread %lu with iteration %d\n",  (pthread_t)pthread_self(), *(int *)arg); 
    return 0; 
} 
