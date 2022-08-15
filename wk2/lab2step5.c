// Name: Nicholas Fotinakes
// Date: 2022-03-15
// Title: Lab2 - task
// Description: This program is for step 5 of Lab 2 which creates a new process
// using fork() and utilizes the execlp() to have the child run a new program
// and the parent process to wait using wait() for the child process to finish

#include <stdio.h>	// printf, stderr
#include <sys/wait.h>	// wait
#include <sys/types.h>	// pid_t
#include <unistd.h>	// fork
#include <stdlib.h>	// aoti, exit
#include <errno.h>	// errno

int main(int argc, char *argv[]) {
	pid_t pid;	// To hold process transaction
	printf("\n Before forking.\n");
	pid = fork();
	// If error occurs when forking, print error
	if (pid == -1) {
		fprintf(stderr, "can't fork, error %d\n", errno);
	} else if (pid == 0) {
		// If child process, use execlp() to run ls
		execlp("/bin/ls", "ls", NULL);
	} else {
		// If parent process, wait for child process and then print
		wait(NULL);
		printf("Child Complete\n");
		exit(0);
	}
	return 0;
}
