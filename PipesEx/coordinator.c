#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>      
#include <sys/wait.h>         
#include <unistd.h>         
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <string.h>

// Author:Eli Harris
// eName: ehharris
// Date: 9/26/18
// Assingment: HW3
// Email: ehharris@rams.colostate.edu

int main(int argc, char **argv) 
{
        //necessary for waitpid to work
    int status;
        //initialize all shmPtr's shmId's 
    int *shmPtr[4];
    int shmId[4];
        //check args number
    if (argc != 6){
        printf("Incorrect number of arguments.\n");
        return -1;
    }
    else {
        
        //pipes storage
    int pipesRead[4];
    int pipesWrite[4];
    int pipeFD[2];
    pid_t pid[4];

        //loop to fork for all processes
        for(int i = 0; i < 4; i++){
                //initialize pipe, check if fail
            if (pipe(pipeFD)){
                printf("Coordinator: Pipe %d failed\n", i);
            }
            pipesRead[i] = pipeFD[0]; 
            pipesWrite[i] = pipeFD[1];
                //forks and stores pid
            pid[i]= fork();
                //if child
            if(pid[i] == 0){
                    //close write pipe
                close(pipesWrite[i]);
                    //connects pipe with STDIN
                dup2(pipesRead[i], STDIN_FILENO);
                    //closes OG pipe since already connected
                close(pipesRead[i]);
                    //start checker
                execl("checker", "checker" , argv[1], argv[i+2], STDIN_FILENO, (char*) NULL);
                    //shouldn't get here
                printf("exec failed\n");
            }
                //if parent
            else{
                printf("Coordinator: forked process with ID %d.\n", pid[i]);  
                    //close read pipe
                close(pipesRead[i]);
                    //initialize shared mem and check for error
                shmId[i] = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
                if (shmId[i] < 0) {
                    printf("Coordinator: Error! shmget in parent of pid %d\n", pid[i]);
                    exit(1);
                }
                    //store shmPtr and err check
                shmPtr[i] = (int *) shmat(shmId[i], NULL, 0);
                if (shmPtr[i] == ((void *) -1)) {
                    printf("Coordinator: Error! shmat in parent of pid %d \n", pid[i]);
                    exit(1);
                }

                    //write to pipe
                write(pipesWrite[i], &shmId[i], sizeof(shmId[i]));
                printf("Coordinator: wrote shm ID %d to pipe (%d bytes)\n", shmId[i], (int) sizeof(shmId[i]));
                    //close pipe to signal child
                close(pipesWrite[i]);
            }
        }
        //wait for all children
        for (int i = 0; i < 4; i++){ 
                //wait for child
            printf("Coordinator: waiting on child process ID %d...\n", pid[i]);
            waitpid(pid[i], &status, 0);
                //after child dies report result
            if (*shmPtr[i] == 1){
                printf("Coordinator: result %d read from shared memory: %d is divisible by %d.\n", *shmPtr[i], atoi(argv[i+2]), atoi(argv[1]));
            }
            else{
                printf("Coordinator: result %d read from shared memory: %d is not divisible by %d.\n", *shmPtr[i], atoi(argv[i+2]), atoi(argv[1]));
            }
                //cleanup mem and err check
            if (shmctl(shmId[i], IPC_RMID, NULL) != 0){
                printf("Coordinator: Error! Failure to close shmId %d\n", shmId[i]);
            }
        }
            //end
        printf("Coordinator: exiting.\n");
    }
    return 0;
    
    
}
