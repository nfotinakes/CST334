// Name: Nicholas Fotinakes
// Date: 2022-03-29
// Title: Lab4 - Memory Management
// Description: This program is for Lab 4 and simulates the FIFO page replacement algorithm.
// By passing a file of different integers per line, the user can designate a cache size to
// see the hit/miss rate of FIFO with different cache sizes. This program uses the package provided
// in the lab prompt to implement a queue.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "queue.h"
#include "node.h"

int main(int argc, char *argv[]){
    int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    char pageCache[100];        // Cache that holds the input from test file
    
    struct queue* q = queue_create();  // create queue to represent cache
    struct node* result; 		// initialize node, used to search queue for page
    int totalFaults = 0; 		// keeps track of the total page faults
    int totalHits = 0;   		// keeps track of the total page hits
    int pageRequests = 0; 		// track total page requests
    
    
    while (fgets(pageCache, 100, stdin)){
    
    	int page_num = atoi(pageCache); //Stores number read from file as int
    	pageRequests++; // every loop incremement page request
    
    	result = queue_find(q, page_num); // check cache (queue) for page
    	
    	// If page not found and cache not full, add to queue and incrememnt page fault
    	if (queue_length(q) < C_SIZE && result == NULL) {
    		enqueue(q, page_num);
    		printf("Page fault: %d\n", page_num);
    		totalFaults++;
    	} 
    	// If page not found and cache is full, remove oldest page, and add page to end of cache
    	// increment page fault
    	else if (queue_length(q) == C_SIZE && result == NULL) {
    		dequeue(q);
    		enqueue(q, page_num);
    		printf("Page fault: %d\n", page_num);
    		totalFaults++;
    	} 
    	// If page found in cache (result is not NULL) increment hit counter
    	// the queue remains the same
    	else {
    		totalHits++;
    	}
    }
    float missRatio = (float)totalFaults / pageRequests;		// calculate miss ratio
    float hitRatio = (float)totalHits / (totalHits + totalFaults);	// calculate hit ratio
    
    // Display all results
    printf("\nTotal Page Requests: %d\n", pageRequests);
    printf("Cache size used: %d\n", C_SIZE);
    printf("Total Page Faults: %d\n", totalFaults);
    printf("Total Page Hits: %d\n", totalHits);
    printf("Miss Ratio: %.2f%%\n", (100 * missRatio));
    printf("Hit Ratio: %.2f%%\n", (100 * hitRatio));
    
    queue_destroy(q); // clear queue to free memory
    
    return 0;

}
