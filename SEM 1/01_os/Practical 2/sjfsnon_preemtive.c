#include<stdio.h>
#include<string.h>

struct Process
{
    int p_id ,p_at,p_bt,p_ct,p_tat,p_wt;

};

struct Process input()
{
    struct Process p;
    printf("\nEnter Process ID :");
    scanf("%d",&p.p_id);

    printf("Enter Process Arrival Time :");
    scanf("%d",&p.p_at);

    printf("Enter Process Burst Time :");
    scanf("%d",&p.p_bt);

    return p;

}

void swapProcess(struct Process *p1 , struct Process *p2)
{
    struct Process temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void sortAccAtBt(struct Process p[],int process_count)
{
    struct Process temp;
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

void display(struct Process p[],int process_count)
{
    printf("ID Arr_time Burst_time Comp_time Turn_time Waiting_time\n");


    for(int i = 0 ; i < process_count ; i++)
    {
        printf("\n%d    %d    %d    %d    %d     %d\n",p[i].p_id,p[i].p_at,p[i].p_bt,p[i].p_ct,p[i].p_tat,p[i].p_wt);
    }
    
}

void sortAccBt(struct Process p[],int start_index ,int process_count)
{
    struct Process temp;
    int isSwapped = 1;

    while(isSwapped)
    {
        isSwapped = 0;
        for(int i = start_index ; i <= start_index + process_count -1 ; i++)
        {
            if(p[i].p_bt > p[i+1].p_bt)
            {
                // swap them
                swapProcess(&p[i],&p[i+1]);

                isSwapped = 1;
            }
        }
    }

}

int main()
{
    int no_of_process , current_time = 0;
    printf("Enter no of process :");
    scanf("%d",&no_of_process);

    struct Process process[no_of_process];

    // take input of p_id, process arrival time , process burst time
    for(int i = 0 ; i < no_of_process ; i++)
    {
        process[i] = input();
    }

    // sort acc to arrival time and then burst time to get 1st process to execute.
    sortAccAtBt(process,no_of_process);

    // set current time to the start time of process which will be executed first
    current_time += process[0].p_at;
    process[0].p_ct = current_time + process[0].p_bt;
    process[0].p_tat = process[0].p_ct - process[0].p_at;
    process[0].p_wt = process[0].p_tat - process[0].p_bt;
    current_time += process[0].p_bt;
    
    // calculate the other valuues using for loop
    for(int i = 1 ; i < no_of_process ; i++)
    {
        // find how many process have arrived at current time 

        // sort data acc to burst time till 


        // data for current process
        process[i].p_ct = current_time + process[i].p_bt;
        process[i].p_tat = process[i].p_ct - process[i].p_at;
        process[i].p_wt = process[i].p_tat - process[i].p_bt;

        

        
    }

    // 
    display(process,no_of_process);



    return 0;
}