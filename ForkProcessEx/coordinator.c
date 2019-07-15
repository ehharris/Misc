#include <stdio.h>
#include "checker.h"
#include <stdlib.h>
#include <sys/types.h>      
#include <sys/wait.h>         
#include <unistd.h>         

// Author:Eli Harris
// eName: ehharris
// Date: 9/17/18
// Assingment: HW2
// Email: ehharris@rams.colostate.edu

int main(int argc, char **argv) 
{
    int status;
    int realstat;
    //check args number
    if (argc != 6){
        printf("Incorrect number of arguments.\n");
        return -1;
    }
    else {
        //loop to fork for all numbers
        for(int i = 1; i < 5; i++){
            //gets pid
            pid_t pid = fork();
            //if child
            if(pid == 0){
                //Run checker
                printf("Coordinator: forked process with ID %d.\n", getpid());  
                printf("Coordinator: waiting for process [%d].\n", getpid());
                execlp("./checker.out", "coordinator" , argv[1], argv[i+1], (char*) NULL);
                //shouldn't get here
                printf("exec failed\n");
            }
            //if parent
            else{
                //wait for child
                int cpid = wait(&status);
                realstat = WEXITSTATUS(status);
                printf("Coordinator: child process %d returned %d.\n", cpid, realstat);
            }
    
        }
        //end
        printf("Coordinator: exiting.\n");
        
    }
    
    
}
