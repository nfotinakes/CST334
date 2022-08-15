// Name: Nicholas Fotinakes
// Date: 2022-03-15
// Title: Lab2 - task
// Description: This program is for steps 1-4 of Lab2 and demonstrates using 
// fork() to create a child process and then have both the parent and child process
// print a series of print statements using for loops and a usleep() amount passed as
// an argument

#include <stdio.h>	// printf, stderr
#include <sys/types.h> // pid_t
#include <unistd.h>	// fork
#include <stdlib.h>	// atoi
#include <errno.h>	// errno

int main(int argc, char *argv[]) {
	pid_t pid; // To hold process identification
	int i, n = atoi(argv[1]);	// n microseconds from argument
	printf("\n Before forking.\n");
	fflush(stdout);
	pid = fork();
	// If error occurs when forking, print error
	if (pid == -1) {
		fprintf(stderr, "can't fork, error %d\n", errno);
		fflush(stdout);
	}
	// If parent process (postive pid value) run the parent loops
	if (pid) {
		for (i = 0; i < 100; i++) {
			printf("\t \t \t Parent Process %d\n", i);
			fflush(stdout);
			usleep(n); // Sleep based on argument
		}
	} else {
		// If not parent, process runs the child loops
		for (i = 0; i < 100; i++) {
			printf("Child Process %d\n", i);
			fflush(stdout);
			usleep(n); // Sleep based on argument
		}
	}
	return 0;
}
