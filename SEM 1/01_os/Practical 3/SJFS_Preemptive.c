// SJFS - Preemptive algorithm
#include<stdio.h>
#include<string.h>

struct Process
{
    int p_id ,p_at,p_bt,p_rem_bt,p_ct,p_tat,p_wt , p_response_time;

};

struct Process input(int pr_id)
{
    struct Process p;
    p.p_id  = pr_id;

    printf("Enter Process %d Arrival Time :",p.p_id);
    scanf("%d",&p.p_at);

    printf("Enter Process %d Burst Time :",p.p_id);
    scanf("%d",&p.p_bt);

    // set burt time = rem burst time
    p.p_rem_bt = p.p_bt;

    // set response time as -ve and if it is -ve then you set its value when process arrive 
    p.p_response_time = -99;


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
    printf("\nID | Arr_time | Burst_time | Rem Burst_time| Comp_time | Turn_time | Waiting_time | Response time\n");


    for(int i = 0 ; i < process_count ; i++)
    {
        printf("\n%d       %d           %d           %d            %d              %d              %d               %d\n",p[i].p_id,p[i].p_at,p[i].p_bt,p[i].p_rem_bt,p[i].p_ct,p[i].p_tat,p[i].p_wt ,p[i].p_response_time );
    }
    
}

void sortAccAtBt(struct Process p[],int process_count)
{
    int isSwapped  = 1;

    while (isSwapped)
    {
        isSwapped = 0;
        for(int i = 0 ; i < process_count - 1 ; i++)
        {
            if( (p[i].p_at > p[i+1].p_at) ||  ( (p[i].p_at == p[i+1].p_at) && (p[i].p_bt > p[i+1].p_bt) ) )
            {
                // swap process
                swapProcess( &p[i], &p[i+1]);
                isSwapped = 1;
            }
        }
    }
}

// function to sort acc to rem_burst_time - if 2 process have same rem_burst_time then sorting takes place acc to arr_time
void sortAccRemBtAt(struct Process p[],int ready_process_count)
{
    int isSwapped = 1;
    while(isSwapped)
    {
        isSwapped = 0;
        for(int i = 0 ; i < ready_process_count -1 ; i++)
        {
            if(  (p[i].p_rem_bt > p[i+1].p_rem_bt) || ( (p[i].p_rem_bt == p[i+1].p_rem_bt) && (p[i].p_at > p[i+1].p_at) )  )
            {
                // swap them
                swapProcess(&p[i],&p[i+1]);
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

int main()
{
    int no_of_process , current_time = 0 ,arrived_process,sum_wt=0,sum_tat=0;
    printf("Enter no of process :");
    scanf("%d",&no_of_process);

    struct Process process[no_of_process];

    // take input of p_id, process arrival time , process burst time
    for(int i = 0 ; i < no_of_process ; i++)
    {
        process[i] = input(i+1);
    }
    printf("\nEntered data -\n");
    display(process,no_of_process);

    // sort acc to arrival time and then burst time to get 1st process to execute.
    sortAccAtBt(process,no_of_process);
    //////display(process,no_of_process);



    for(current_time = 0  ; 1 ; current_time++)
    {
        //////printf("\n-----current time = %d",current_time);
        arrived_process = getArivedProcess(process,current_time,no_of_process);
        //////printf("\n--Arrived Process = %d",arrived_process);

        if(arrived_process)         // if there are process which can be executed
        {
            sortAccRemBtAt(process,arrived_process);
            //////printf("Displaying arr sorted acc to rem burst time");
            //////display(process,no_of_process);

            
            for(int i = 0 ; i < arrived_process ; i++)
            {
                if(process[i].p_rem_bt != 0)
                {
                    process[i].p_rem_bt--;

                    // check if it is first time the process is coming and if yes then assign response time
                    // RESPONSE TIME = CPU 1st Time - ARRIVAL TIME
                    if(process[i].p_response_time < 0)
                    {
                        process[i].p_response_time = current_time - process[i].p_at;
                    }

                    // if remaininig burst time  = 0 now then current time will be process's completion time.
                    if(process[i].p_rem_bt == 0)
                    {
                        process[i].p_ct = current_time + 1;
                    }

                    break;
                }
            }

        }

        // check if all process are executed or not
        if(checkIfAllProcessExecuted(process,no_of_process) == 1)
        {
            // all process are executed
            break;
        }
        
    }

    // cal tat and wt
    for(int k=0 ; k < no_of_process ; k++)
    {
        process[k].p_tat = process[k].p_ct - process[k].p_at;
        process[k].p_wt = process[k].p_tat - process[k].p_bt;

    }

    // display table with values calculated
    display(process,no_of_process);

    // cal avg waiting time and avg turn around time
    printf("Average TAT  = %f  | Average WT = %f",getAvgTAT(process,no_of_process),getAvgWT(process,no_of_process));

    return 0;
}