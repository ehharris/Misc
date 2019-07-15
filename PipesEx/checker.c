#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Author:Eli Harris
// eName: ehharris
// Date: 9/26/18
// Assingment: HW3
// Email: ehharris@rams.colostate.edu


//checks if number is divisible
int isDiv(int divBy, int div){
    const int pid = getpid();

    //checks is div by divisor
    if (div % divBy == 0){
        printf("Checker process [%d]: %d *IS* divisible by %d.\n" , pid, div, divBy);
        return 1;
    }
    else{
        printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n" , pid, div, divBy);
        return 0;
    }
    
}

int main(int argc, char **argv) {
    const int pid = getpid();
    printf("Checker process [%d]: starting.\n", pid);
        //read STDIN
    int shmId;
    read(STDIN_FILENO, &shmId, 4);
    printf("Checker process [%d]: read %d bytes containing shm ID %d\n", pid, (int) sizeof(shmId), shmId);
        //check if div
    int ans = isDiv(atoi(argv[1]), atoi(argv[2]));
        //access shm and err check
    int *shmPtr = (int *) shmat(shmId, NULL, 0);
    if (shmPtr == ((void *) -1)){
        printf("Checker: Error! Failed to access shm in pid %d\n", pid);
        exit(1);
    }
        //copy's to shm
    *shmPtr = ans;
    printf("Checker process [%d]: wrote result (%d) to shared memory.\n", pid, *shmPtr);
        //detach shared memory
    if(shmdt(shmPtr) != 0){
        printf("Checker: Error! Cannot detach memory in pid %d\n", pid);
    }
    return ans;
}
