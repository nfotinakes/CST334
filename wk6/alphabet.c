// Name: Nicholas Fotinakes
// Date: 2022-04-12
// Title: Lab 6 - Step 2
// Description: This program is for Step 2 of Lab 6 to demonstrate the usage
// of semaphores to solve the producer/consumer problem with the alphabet

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 2  	// Constant for num of threads to use (2 in this case)
#define MAX 1		// Constant for max size of buffer
#define ALPHABET 26	// Constant for size of alphabet
pthread_t threads[NTHREADS]; // Array to hold producer and consumer thread

// Semaphores for full, empty, and mutex
sem_t full;
sem_t empty;
sem_t mutex;
char buffer[MAX];	// Array to simulate buffer of MAX size

// fill and use for buffer put and get functions
int fill = 0;		
int use = 0;

// Declare functions
void put(char value);
char get();
void *producer(void *arg);
void *consumer(void *arg);


int main()
{
   // Create letter to start at 
   char start = 'A';
   int i;
   // Populate buffer with * to represent blank space 
   for (i=0; i<MAX; i++){
   	buffer[i] = '*';
   }
   printf("Buffer size: %d\t Buffer status: %s\n", MAX, buffer); // Print buffer size and empty buffer that we filled with *
   	
   sem_init(&mutex, 0, 1);	// Binary semaphore for lock
   sem_init(&full, 0, 0);	// Semaphore for full buffer signaling
   sem_init(&empty, 0, MAX);	// Semaphore for empty buffer signaling
   
   pthread_create(&threads[0], NULL, producer, &start); // Producer thread, send starting letter 'A' 
   pthread_create(&threads[1], NULL, consumer, NULL);   // Consumer thread
   
   // Join producer and consumer threads when finished
   pthread_join(threads[0], NULL);
   pthread_join(threads[1], NULL);
   
   // Main thread finish and destroy semaphores
   printf("Main thread done.\n");
   sem_destroy(&mutex);
   sem_destroy(&full);
   sem_destroy(&empty);

   return 0;
}

// Put function to put letter into buffer
void put(char value) {
   buffer[fill] = value;
   fill++;
   if(fill == MAX) {
   fill = 0;
   }
}

// Get function to retrieve letter from buffer and clear space
char get() {
   char letter = buffer[use];
   buffer[use] = '*'; // set consumed spot back to *
   use++;
   if(use == MAX) {
   	use = 0;
   }
   return letter;
}

// Producer function to produce letter using semaphores
void *producer(void *arg) {
	
   char letter = *(char *)arg; // Starting 'A' letter passed
   int i;
   
   // Loop for all 26 letters
   for(i = 0; i < ALPHABET; i++){
   
      sem_wait(&empty); // Semaphore to check if buffer is empty (will start producing right away as buffer is intially empty/set to MAX)
      sem_wait(&mutex); // If buffer available, lock
      
      put(letter); // Produce and put letter into buffer
      
      printf("Producer letter: %c\t BUFFER STATUS: %s\n", letter, buffer); // Print produced letter and status of buffer
      usleep(500000);  // sleep for 1/2 second
      letter++; // increment letter for next production
     
      sem_post(&mutex); // signal mutex (unlock)
      sem_post(&full);	 // signal full (increment the full semaphore)
   }
   return NULL;
}

// Consumer function to consumer letter from buffer
void *consumer(void *arg) {
   char letter;
   int i;
   
   // Loop to consume amount of alphabet 
   for(i = 0; i < ALPHABET; i++){
   
      sem_wait(&full);  // Check full semaphore, wait if buffer not full
      sem_wait(&mutex); // When buffer full, obtain lock 
      letter = get();	 // Get letter from buffer to consume
      
      printf("Consumer letter: %c\t BUFFER STATUS: %s\n", letter, buffer); // Print consumed letter and buffer status
      usleep(500000); // Sleep for 1/2 second
      
      
      sem_post(&mutex); // signal mutex (unlock)
      sem_post(&empty); // signal empty (increment empty as one buffer slot has opened)
   }
   return NULL;
}
