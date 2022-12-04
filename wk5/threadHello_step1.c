// Name: Nicholas Fotinakes
// Date: 2022-04-05
// Title: Lab 5 - Multi-Threaded Applications: Step 1
// Description: This program is for Step 1 of Lab 5 and demonstrates a basic multi threaded 
// application. Bugs produced (shared i value and negative thread id) are fixed in threadHello_step1_fixed.c 

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h> 

void *go(void *); 		// Declare go function
#define NTHREADS 10 		// Num of threads to create
pthread_t threads[NTHREADS]; 	// Array to hold created thread IDs

int main() { 
    int i; 
    // Loop to create 10 threads
    for (i = 0; i < NTHREADS; i++) 
        pthread_create(&threads[i], NULL, go, &i); 
        
    // Threads return from go() and use pthread_join    
    for (i = 0; i < NTHREADS; i++) { 
        printf("Thread %d returned\n", i); 
        pthread_join(threads[i],NULL); 
    } 
    // After all created threads finish, main thread completes
    printf("Main thread done.\n"); 
    return 0; 
} 

// Print thread with the passed i pointer
void *go(void *arg) { 
    printf("Hello from thread %d with iteration %d\n",  (int)pthread_self(), *(int *)arg); 
    return 0; 
} 
