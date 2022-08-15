// Name: Nicholas Fotinakes
// Date: 2022-03-22
// Title: Lab3 - Step 3
// Description: This program is Step 3 of Lab 3 which demonstrates a pipe/inter-process communication.
// In this program, the parent forks twice to create two child processes
// for the upstream and downstream of the pipe. This program executes a pipe equivalent to the
// command line "cat /etc/passwd | grep root" which searches for "root" in the passwd file.

#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/wait.h> 
#include <sys/types.h>
#include <sys/ipc.h>
//main 
int main() { 
    int fds[2]; 
    pipe(fds); 
    // Child one duplicates downstream into stdin for the grep root
    if (fork() == 0) { 
        dup2(fds[0], 0); 
        close(fds[1]); 
        execlp("grep", "grep", "root", (char *) NULL); 
    } 
    // Child two duplicates upstream into stdout for cat /etc/passwd 
    else if (fork() == 0) { 
        dup2(fds[1], 1); 
        close(fds[0]); 
        execlp("cat", "cat", "/etc/passwd", (char *) NULL); 
    } 
    else { // Parent closes both ends and waits for children
        close(fds[0]); 
        close(fds[1]); 
        wait(0); 
        wait(0); 
    } 
return 0; 
} 
