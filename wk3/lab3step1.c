// Name: Nicholas Fotinakes
// Date: 2022-03-22
// Title: Lab3 - Step 1
// Description: This program is for Step 1 of Lab 3 which demonstrates a pipe within a 
// C program. The parent program forks twice, for each child process to
// use execlp to execute either the downstream or upstream of the pipe. Essentially
// this is like running "ls | more" from the command line

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
    /*child 1 duplicates downstream into stdin */ 
    if (fork() == 0) { 
        dup2(fds[0], 0); 
        close(fds[1]); 
        execlp("more", "more", (char *) NULL); // Downstream exectues more 
    } 
    /*child 2 duplicates upstream into stdout */ 
    else if (fork() == 0) { 
        dup2(fds[1], 1); 
        close(fds[0]); 
        execlp("ls", "ls", (char *) NULL); // Upstream executes ls 
    } 
    else { /*parent closes both ends and wait for children*/ 
        close(fds[0]); 
        close(fds[1]); 
        wait(0); 
        wait(0); 
    } 
return 0; 
} 
