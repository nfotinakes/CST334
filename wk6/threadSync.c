// Name: Nicholas Fotinakes
// Date: 2022-04-12
// Title: Lab 6 - Step 1
// Description: This program is for Step 1 of Lab 6 to demonstrate a multi-threaded
// program using a semaphore for thread synchronization 

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 10
pthread_t threads[NTHREADS];
sem_t mutex;

// go function protects critical print statement with semaphore to provide thread synchronization
void *go(void *arg)
{
   sem_wait(&mutex);
   printf("Thread %lu Entered Critical Section..\n", (size_t)arg);
   sleep(1);
   sem_post(&mutex);
   return (NULL);
}

int main()
{
   sem_init(&mutex, 0, 1); // binary semaphore for lock
   static int i;

   // Creates 10 threads and calls go function
   for (i = 0; i < NTHREADS; i++)
      pthread_create(&threads[i], NULL, go, (void *)(size_t)i);

   // join threads upon return
   for (i = 0; i < NTHREADS; i++)
   {
      pthread_join(threads[i], NULL);
      printf("Thread %d returned \n", i);
   }

   // Finish main and destory semaphore
   printf("Main thread done.\n");
   sem_destroy(&mutex);

   return 0;
}
