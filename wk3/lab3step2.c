// Name: Nicholas Fotinakes
// Date: 2022-03-22
// Title: Lab3 - Step 2
// Description: This program is Step 2 of Lab 3 which demonstrates using pipe() and write(). 
// This program again forks twice for child processes to handle either side of pipe to
// write the arguments from argc, argv and stdin.

#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/wait.h> 
#include <sys/types.h>
#include <sys/ipc.h>
// main 
int main(int argc,char *argv[]){ 
 
    int fds[2]; 
    char buff[60]; 
    int count; 
    int i; 
    pipe(fds); 
    // First child to write the writer of upstream 
    if (fork()==0){ 
        printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc); 
        close(fds[0]); 
        for(i=0;i<argc;i++){ 
            write(fds[1],argv[i],strlen(argv[i])); 
        } 
    	exit(0); 
    } 
    // Second child writing reader on downstream end
    else if(fork()==0){ 
        printf("\nReader on the downstream end of the pipe \n"); 
        close(fds[1]); 
        while((count=read(fds[0],buff,60))>0){ 
            for(i=0;i<count;i++){ 
                write(1,buff+i,1); 
                write(1," ",1); 
            } 
            printf("\n"); 
        } 
        exit(0); 
    } 
    // Parent closes both ends and waits for children
    else{ 
        close(fds[0]); 
        close(fds[1]); 
        wait(0); 
        wait(0); 
    } 
    return 0; 
} 
