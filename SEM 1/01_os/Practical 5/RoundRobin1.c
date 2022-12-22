// Round Robin algorithm
#include<stdio.h>
#include<string.h>

struct Process
{
    int p_id ,p_at,p_bt,p_rem_bt,p_ct,p_tat,p_wt ,p_arrived;

};

struct Process input(int pr_id)
{
    struct Process p;
    p.p_id  = pr_id;

    printf("Enter Process %d Arrival Time and Burst Time:",p.p_id);
    scanf("%d %d",&p.p_at , &p.p_bt);

    // set burt time = rem burst time
    p.p_rem_bt = p.p_bt;

    // set p_arrived to 0 .
    p.p_arrived = 0 ;   // 0=> the process has not arrived yet => current_time < process_ArrivalTime

    return p;

}

void swapProcess(struct Process *p1 , struct Process *p2)
{
    struct Process temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void display(struct Process p[],int process_count)
{
    printf("\nID | Arr_time | Burst_time | Rem Burst_time| Comp_time | Turn_time | Waiting_time \n");


    for(int i = 0 ; i < process_count ; i++)
    {
        printf("\n%d       %d           %d           %d            %d              %d              %d\n",p[i].p_id,p[i].p_at,p[i].p_bt,p[i].p_rem_bt,p[i].p_ct,p[i].p_tat,p[i].p_wt );
    }
    
}

void sortAccAt(struct Process p[],int process_count)
{
    int isSwapped  = 1;

    while (isSwapped)
    {
        isSwapped = 0;
        for(int i = 0 ; i < process_count - 1 ; i++)
        {
            if( p[i].p_at > p[i+1].p_at )
            {
                // swap process
                swapProcess( &p[i], &p[i+1]);
                isSwapped = 1;
            }
        }
    }
}

int getArivedProcess(struct Process p[] , int current_time,int total_process)
{
    int count = 0 ; 
    for(int m = 0 ; m < total_process; m++)
    {
        if( p[m].p_at <= current_time )
            count++;
    }

    return count;
}

float getAvgTAT(struct Process p[],int process_count)
{
    float sum_tat =0;
    for(int i = 0  ; i < process_count ;i++)
    {
        sum_tat += p[i].p_tat;
    }
    return sum_tat/process_count;

}

float getAvgWT(struct Process p[],int process_count)
{
    float sum_wt =0;
    for(int i = 0  ; i < process_count ;i++)
    {
        sum_wt += p[i].p_wt;
    }
    return sum_wt/process_count;

}

int checkIfAllProcessExecuted(struct Process p[],int process_count)
{
    for(int i  = 0 ; i < process_count; i++)
    {
        if(p[i].p_rem_bt != 0)
        {
            return 0;   // process are remaining to be executed
        }
    }

    return 1;   // => all process are executed
}

int removeProcessFromReadyQueue(struct Process readyQ[],int indexLastProcess)
{
    struct Process temp;
    for(int i = 1 ; i <= indexLastProcess ; i++)
    {
        readyQ[i-1] = readyQ[i];
    }

    indexLastProcess--; // decrease the index of last process in the array.
    return indexLastProcess;
} 

int addProcessInReadyQueue(struct Process readyQ[],int indexLastProcess , struct Process p)
{
    indexLastProcess++;
    readyQ[indexLastProcess] = p;

    return indexLastProcess;
}

int putFirstProcessBackInReadyQueue(struct Process readyQ[],int indexLastProcess)
{
    struct Process temp;
    temp = readyQ[0];
    indexLastProcess = removeProcessFromReadyQueue(readyQ,indexLastProcess);
    indexLastProcess = addProcessInReadyQueue(readyQ,indexLastProcess,temp);

    // readyQ[indexLastProcess + 1] = {0};


    return indexLastProcess;
}

int getOriginalProcessArrIndexIdGiven(struct Process p[],int id,int total_process)
{
    for(int m = 0 ; m < total_process ; m++ )
    {
        if(p[m].p_id == id)
            return m;   // return index so you can change the CT at that index.
    }
}

int main()
{
    int total_process , current_time = 0 ,arrived_process,sum_wt=0 ,sum_tat=0 , timeQuantum ,tq_temp;
    // So when we have new Process to be added in Ready Queue then we would 1st Increase the this counter and then add the Process.
    // -1 => that Ready Queue is EMPTY.
    int readyQ_lastProcessIndex=-1; // it would point to the last process which is in the array. 

    printf("Enter no of process :");
    scanf("%d",&total_process);

    struct Process process[total_process] , readyQueue[total_process];

    // initialize all elements of readyQueue as 0
    // for(int i = 0 ; i < total_process ; i++)
    //     readyQueue[i] = null;

    // take input of p_id, process arrival time , process burst time
    for(int i = 0 ; i < total_process ; i++)
    {
        process[i] = input(i+1);
    }
    printf("Enter the Time Quantum - ");
    scanf("%d",&timeQuantum);
    tq_temp = timeQuantum;

    printf("\nEntered data -\n");
    display(process,total_process);

    // sort acc to arrival time and then burst time to get 1st process to execute.
    sortAccAt(process,total_process);
    //////display(process,total_process);

    for(current_time = 0  ; 1 ; current_time++)
    {
        // code to check if a process has arrived or not and if 
        for(int k = 0 ; k < total_process ; k++)
        {
            if( (process[k].p_at <= current_time) && (process[k].p_arrived == 0)) // Means process has arrived 1st time so you need to add it in the ready queue
            {
                readyQ_lastProcessIndex = addProcessInReadyQueue(readyQueue,readyQ_lastProcessIndex,process[k]);
                /*
                // Increase the index pos of ready Queue
                readyQ_lastProcessIndex++;
                readyQueue[readyQ_lastProcessIndex] = process[k]; //added a process to Ready Queue process.
                */
                process[k].p_arrived = 1; // set that this process has already arrived in the Ready Queue.
            }
        }

        // Now check if there is any process in the Ready Queue and if present then execute the 1st process for 1sec. Also reduce the TQ-- , BT--
        if(readyQ_lastProcessIndex > -1)    // => that there is atleast 1 process in Ready Queue.
        {
            // executing the 1st process in Ready Queue
            readyQueue[0].p_rem_bt--;
            process[getOriginalProcessArrIndexIdGiven(process,readyQueue[0].p_id,total_process)].p_rem_bt--;
            printf("P%d ",readyQueue[0].p_id);
            tq_temp--;
            if(readyQueue[0].p_rem_bt == 0) // => that process has finished execution so 1. Update Completion Time 2. RESET T.Q  3. Remove process from readyQueue
            {
                readyQueue[0].p_ct = current_time + 1;
                process[getOriginalProcessArrIndexIdGiven(process,readyQueue[0].p_id,total_process)].p_ct = current_time + 1;

                tq_temp = timeQuantum;  // RESETTING Time Quantum

                readyQ_lastProcessIndex = removeProcessFromReadyQueue(readyQueue,readyQ_lastProcessIndex);
            }
            else    // either T.Q may become 0 or T.Q != 0 and process rem_bt != 0
            {
                if(tq_temp == 0  && process[0].p_rem_bt != 0) 
                {
                    // put the 1st process in the back of the Ready Queue
                    readyQ_lastProcessIndex = putFirstProcessBackInReadyQueue(readyQueue,readyQ_lastProcessIndex);
                    // set temp_tq to default
                    tq_temp = timeQuantum;
                }
                // else
                // {
                //     // if T.Q != 0  and Burst Time != 0
                // }
                
            }
            
                                        

        }
        else
        {
            // 2 Cases - > 1st All process have been executed so Get Out from For loop
            //             2nd Some process are yet to come in Ready Queue so so just wait for process to come in Ready Queue.
            if(checkIfAllProcessExecuted(process,total_process) == 1)
            {
                // get out of the FOR LOOP of the current time
                break;
            }
            // else
            // {
            //     // code - when no process are in the Ready Queue.
            // }

        }
 
    }

    // cal tat and wt
    for(int k=0 ; k < total_process ; k++)
    {
        process[k].p_tat = process[k].p_ct - process[k].p_at;
        process[k].p_wt = process[k].p_tat - process[k].p_bt;

    }

    // display table with values calculated
    display(process,total_process);

    // cal avg waiting time and avg turn around time
    printf("Average TAT  = %f  | Average WT = %f",getAvgTAT(process,total_process),getAvgWT(process,total_process));

    return 0;
}