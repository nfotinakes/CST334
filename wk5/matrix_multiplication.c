// Name: Nicholas Fotinakes
// Date: 2022-04-05
// Title: Lab 5 - Multi-Threaded Applications: Step 3 Matrix Multiplication
// Description: This program uses multi threading to do multiplication on
// two matrices and print results


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

void *multiply(void *); // Declare multiply
// Values for matrices size (and thread count based on N)
#define N 1024
#define M 1024
#define L 1024

double matrixA[N][M], matrixB[M][L], matrixC[N][L]; // Initialize matrices
pthread_t threads[N]; // Initialize array for threads

int main() {

    // Populate MatrixA with random numbers between 0 and 2
    srand(time(NULL)); 
    for (int i = 0; i < N; i++){
    	for (int j = 0; j < M; j++){
    		matrixA[i][j] = 2.0 * ((double)rand() / RAND_MAX); 
    	} 
    } 
    
    // Populate MatrixB with random numbers between 0 and 2
    for (int i = 0; i < M; i++){
    	for (int j = 0; j < L; j++){
    		matrixB[i][j] = 2.0 * ((double)rand() / RAND_MAX); 
    	} 
    } 
     
    // Print matrixA (rounded to 3 decimals)
    printf("MatrixA:\n");
    for(int i = 0; i < N; i++) {
        for(int j=0; j<M; j++) {
            printf("%.3f\t", matrixA[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // Print Matrix B (rounded to 3 decimals)
    printf("MatrixB:\n");
    for(int i = 0; i < M; i++) {
        for(int j=0; j<L; j++) {
            printf("%.3f\t", matrixB[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // Create threads, using separate array to hold 'i' value
    // Send each thread to perform specific multiplication for matrix based on iteration
    int id[N];
    for (int i = 0; i < N; i++) {
    	id[i] = i;
        pthread_create(&threads[i], NULL, multiply, &id[i]); 
    }
    
    // Display threads returning and join
     for (int i = 0; i < N; i++) { 
        printf("Thread %d returned\n", i); 
        pthread_join(threads[i],NULL); 
    } 
    printf("Thread multiplication complete.\n"); 
    
    // Add a little blank space before for looks
    printf("\n");
    printf("\n");
   
    // Print MatrixC produced by multi-thread multiplication (rounded to 3 decimal places)
    printf("MatrixC:\n");
    for(int i = 0; i < N; i++) {
        for(int j=0; j<L; j++) {
            printf("%.3f\t", matrixC[i][j]);
        }
        printf("\n");
    }
    return 0;
}


// Multiply function for thread to perfrom multiplication based
// on the passed iteration value of 'i'
void *multiply(void *arg) { 
	int i = *(int *)arg;
	for (int j = 0; j < L; j++){ 
		double temp = 0; 
		for (int k = 0; k < M; k++){ 
			temp += matrixA[i][k] * matrixB[k][j]; 
		} 
		matrixC[i][j] = temp; 
	}  
    return 0; 
} 
