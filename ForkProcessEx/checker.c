#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Author:Eli Harris
// eName: ehharris
// Date: 9/17/18
// Assingment: HW2
// Email: ehharris@rams.colostate.edu

//checks if number is divisible
int isDiv(int divBy, int div){
    
    int pid = getpid();
    printf("Checker process [%d]: Starting.\n", pid);
    //checks is div by divisor
    if (div % divBy == 0){
        printf("Checker process [%d]: %d *IS* divisible by %d.\n" , pid, div, divBy);
        printf("Checker process [%d]: Returning 1.\n", pid);
        return 1;
    }
    else{
        
        printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n" , pid, div, divBy);
        printf("Checker process [%d]: Returning 0.\n", pid);
        return 0;
    }
    
}

int main(int argc, char **argv) 
{
    return isDiv(atoi(argv[1]), atoi(argv[2]));
}
