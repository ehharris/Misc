#include <stdio.h>
#include <stdlib.h>

struct Process{
    int Process_ID;
    int Arrival_Time;
    int Burst_Duration;
    int Priority;
    int TurnAroundTime;
    int WaitTime;
};
//**********************************************************
struct Gantt
{
  int Process_ID;
  int Arrival_Time;
  int End_Time;
};

void File_Content(struct  Process Processes[], int number);
void FCFS(struct Process Processes[], int number);
void SJFP(struct Process Processes[], int number);
void PRIORITY(struct Process Processes[], int number);
void RR(struct Process Processes[], int number, int quantum);
void Display_Output(struct  Process Processes[],int number,struct Gantt Rows[],int count, char* filename);

int main(int argc, char **argv)
{

    int number_of_pross = 0;

    	if (argc != 2)
    	{
       		printf("Incorrect number of arguments.\n");
       	 	return -1;
    	}

		FILE* file1 = fopen(argv[1], "r");

  while(!feof(file1))
  {
  char  ch = fgetc(file1);
    if(ch == '\n')
    {
      number_of_pross++;
    }
  }
        struct Process Processes[number_of_pross];

        fseek(file1, 0, SEEK_SET);


        number_of_pross=0;


		while(fscanf(file1, "%d,%d,%d,%d",&Processes[number_of_pross].Process_ID,&Processes[number_of_pross].Arrival_Time,&Processes[number_of_pross].Burst_Duration,&Processes[number_of_pross].Priority) != EOF	)
       {
			number_of_pross++;
        }
        fclose(file1);

            //File_Content(Processes,number_of_pross);
            FCFS(Processes,number_of_pross);
            SJFP(Processes,number_of_pross);
            PRIORITY(Processes,number_of_pross);
	
        return 0;
}
//--------------------------------------------------------
void File_Content(struct Process Processes[], int number)
{
    int i;
    printf("PROCESS ID\tARRIVAL TIME\tBURST DURATION\tPRIORITY\n");
    for(i=0;i<number;i++)
    {

        printf("%d\t\t%d\t\t%d\t\t%d\n",Processes[i].Process_ID,Processes[i].Arrival_Time,Processes[i].Burst_Duration,Processes[i].Priority);

    }
}
//---------------------------------------------------------------
void Display_Output(struct  Process Processes[],int number,struct Gantt Rows[],int count, char *filename)
{
      FILE* file;
      int i;
      file=fopen(filename,"w");
      fprintf(file,"PROCESS ID\tARRIVAL TIME\tEND TIME\n");

      for(i=0;i<count;i++)
      {
        fprintf(file,"%10d%10d%10d\n",Rows[i].Process_ID,Rows[i].Arrival_Time,Rows[i].End_Time);
      }

      float avgWait=0;
      float avgTurnAround=0;
      for(i=0;i<number;i++)
      {
          avgWait+=Processes[i].WaitTime;
          avgTurnAround+=Processes[i].TurnAroundTime;
      }
      fprintf(file,"Average Wait Time=%f\n",avgWait/number);
      fprintf(file,"TurnAround Time=%f\n",avgTurnAround/number);
      // Assumption: the value of count recieved is greater than exact number of rows in the Gantt chart by 1. Dont forget to adjust the value if yours is not so.
      fprintf(file,"Throughput=%f\n",((float)number/Rows[count-1].End_Time));
      fclose(file);

}
//------------------------------------------------------------


/*
 Note: Use function Display_Output to display the result. The Processes is the
 updated Processes with their respective waittime, turnAround time.
 Use the array of Gantt Struct to mimic the behaviour of Gantt Chart. Rows is the base name of the same array.
 number is the number of processes which if not changed during processing, is taken care. count is the number of rows in the Gantt chart. 
 
 Number of Processes will not exceed 1000. Create and array of Gantt chart which can accomodate atleast 1000 process.
 */
// -------------FCFS----------------------------------------
void FCFS(struct Process Processes[], int number){
    //---------Start Processing
    struct Process Pro2[number];
    
    for (int i = 0 ; i < number ; i++){
        Pro2[i].Process_ID = Processes[i].Process_ID;
        Pro2[i].Burst_Duration = Processes[i].Burst_Duration;
        Pro2[i].Arrival_Time = Processes[i].Arrival_Time;
    }
    for (int i = 0; i < number; i++){
        for (int j = 0; j < (number - i - 1); j++){
            if (Pro2[j].Arrival_Time > Pro2[j + 1].Arrival_Time){
                //printf("Process = %d\n", Processes[j].Process_ID);
                struct Process temp = Pro2[j];
                //printf("Temp Process = %d\n", temp.Process_ID)
                Pro2[j]= Pro2[j + 1];
                Pro2[j + 1] = temp;
            }
            if (Pro2[j].Arrival_Time == Pro2[j + 1].Arrival_Time){
                if (Pro2[j].Process_ID > Pro2[j + 1].Process_ID){
                    //printf("Process = %d\n", Processes[j].Process_ID);
                    struct Process temp = Pro2[j];
                    //printf("Temp Process = %d\n", temp.Process_ID)
                    Pro2[j]= Pro2[j + 1];
                    Pro2[j + 1] = temp;
                }
            }
        }
    }
    struct Gantt Rows[number];
    int WaitTime = 0;
    for (int i = 0; i < number; i++){
        //Initialize Gantt Row 
        Rows[i].Arrival_Time = WaitTime;
        Rows[i].End_Time = WaitTime + Pro2[i].Burst_Duration;
        Rows[i].Process_ID = Pro2[i].Process_ID;
        //Update Process
        Pro2[i].WaitTime = WaitTime - Pro2[i].Arrival_Time;
        Pro2[i].TurnAroundTime = Rows[i].End_Time - Pro2[i].Arrival_Time;
        //Update Waittime
        WaitTime = Rows[i].End_Time;
    }
    Display_Output(Pro2, number, Rows, number, "FCFS2");
    
    //---------End of Processing
   //Hint: Call function with arguments shown Display_Output(Processes,number,Rows,count,"FCFS");
}
//---------------------SJFP---------------------------------------
void SJFP(struct Process Processes[],int number)
{
    //---------Start Processing
    //Get time to complete
    int maxTime = 0;
    struct Process Pro2[number];
    int ey = (2 * number) - 1;
    struct Gantt Rows[ey];
    for (int i = 0 ; i < number ; i++){
        Pro2[i].Process_ID = Processes[i].Process_ID;
        Pro2[i].Burst_Duration = Processes[i].Burst_Duration;
        Pro2[i].Arrival_Time = Processes[i].Arrival_Time;
        maxTime += Pro2[i].Burst_Duration;
    }
    int current = -1;
    int ganttCurr = 0;
    //Checks on each passing tick if there's a process with a lower Burst Duration
    for (int waitTime = 0; waitTime <= maxTime; waitTime++){
        int past = current;
        if(current != -1){
            if(Pro2[current].Burst_Duration == 0){
                //printf("hey\n");
                Pro2[current].TurnAroundTime = waitTime - Pro2[current].Arrival_Time;
                current = -1;
            }
        }
        //Determine Shortest job
        for (int i = 0; i < number; i++){
            if(Pro2[i].Arrival_Time <= waitTime && Pro2[i].Burst_Duration > 0){
                if (current == -1){
                    current = i;
                } 
                else if(Pro2[current].Burst_Duration > Pro2[i].Burst_Duration){
                    current = i;
                }
                else if (Pro2[current].Burst_Duration == Pro2[i].Burst_Duration){
                    if (Pro2[i].Arrival_Time < Pro2[current].Arrival_Time){
                        current = i;
                    }
                }
                
            }
        }
        if(waitTime == 0){
            Rows[ganttCurr].Arrival_Time = waitTime;
            Rows[ganttCurr].Process_ID = Pro2[current].Process_ID;
            Pro2[current].WaitTime = waitTime - Pro2[current].Arrival_Time;
        } 
        else if(Pro2[past].Process_ID != Pro2[current].Process_ID){
            Rows[ganttCurr].End_Time = waitTime;
            Pro2[current].WaitTime = waitTime - Pro2[current].Arrival_Time;
            ganttCurr++;
            Rows[ganttCurr].Process_ID = Pro2[current].Process_ID;
            Rows[ganttCurr].Arrival_Time = waitTime;
        }
       // printf("curr %d\n", Pro2[current].Burst_Duration);
        //printf("Current %d, %d, %d\n", Processes[current].Process_ID, current, count);
        Pro2[current].Burst_Duration--;
   }
   Display_Output(Pro2, number, Rows, ganttCurr, "SJF2");
   
   

    //---------End of Processing
  

}
//------------------PRIORITY-------------------------------------
void PRIORITY(struct Process Processes[], int number)
{
     //---------Start Processing
    //Get time to complete
    int maxTime = 0;
    struct Process Pro2[number];
    int ey = (2 * number) - 1;
    struct Gantt Rows[ey];
    for (int i = 0 ; i < number ; i++){
        Pro2[i].Process_ID = Processes[i].Process_ID;
        Pro2[i].Burst_Duration = Processes[i].Burst_Duration;
        Pro2[i].Arrival_Time = Processes[i].Arrival_Time;
        Pro2[i].Priority = Processes[i].Priority;
        maxTime += Pro2[i].Burst_Duration;
    }
    int current = -1;
    int ganttCurr = 0;
    //Checks on each passing tick if there's a process with a lower Burst Duration
    for (int waitTime = 0; waitTime <= maxTime; waitTime++){
        int past = current;
        if(current != -1){
            if(Pro2[current].Burst_Duration == 0){
                //printf("hey\n");
                Pro2[current].TurnAroundTime = waitTime - Pro2[current].Arrival_Time;
                current = -1;
            }
        }
        //Determine highest Priority job
        for (int i = 0; i < number; i++){
            if(Pro2[i].Arrival_Time <= waitTime && Pro2[i].Burst_Duration > 0){
                if (current == -1){
                    current = i;
                } 
                if(Pro2[current].Priority > Pro2[i].Priority){
                    current = i;
                }
                else if (Pro2[current].Priority == Pro2[i].Priority){
                    if (Pro2[i].Arrival_Time < Pro2[current].Arrival_Time){
                        current = i;
                    }
                    else if (Pro2[i].Arrival_Time == Pro2[current].Arrival_Time){
                        if (Pro2[i].Process_ID < Pro2[current].Process_ID){
                            current = i;
                        }
                    }
                }
                
            }
        }
        if(waitTime == 0){
            Rows[ganttCurr].Arrival_Time = waitTime;
            Rows[ganttCurr].Process_ID = Pro2[current].Process_ID;
            Pro2[current].WaitTime = waitTime - Pro2[current].Arrival_Time;
        } 
        else if(Pro2[past].Process_ID != Pro2[current].Process_ID){
            Rows[ganttCurr].End_Time = waitTime;
            Pro2[current].WaitTime = waitTime - Pro2[current].Arrival_Time;
            ganttCurr++;
            Rows[ganttCurr].Process_ID = Pro2[current].Process_ID;
            Rows[ganttCurr].Arrival_Time = waitTime;
        }
       // printf("curr %d\n", Pro2[current].Burst_Duration);
        //printf("Current %d, %d, %d\n", Processes[current].Process_ID, current, count);
        Pro2[current].Burst_Duration--;
   }
   Display_Output(Pro2, number, Rows, ganttCurr, "PRIORITY2");
    //---------End of Processing

}


