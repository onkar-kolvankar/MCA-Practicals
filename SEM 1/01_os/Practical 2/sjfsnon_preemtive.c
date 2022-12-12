#include<stdio.h>
#include<string.h>

struct Process
{
    int p_id ,p_at,p_bt,p_ct,p_tat,p_wt;

};

struct Process input(int pr_id)
{
    struct Process p;
    p.p_id  = pr_id;

    printf("Enter Process %d Arrival Time :",p.p_id);
    scanf("%d",&p.p_at);

    printf("Enter Process %d Burst Time :",p.p_id);
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
    printf("ID | Arr_time | Burst_time | Comp_time | Turn_time | Waiting_time\n");


    for(int i = 0 ; i < process_count ; i++)
    {
        printf("\n%d     %d      %d      %d      %d          %d\n",p[i].p_id,p[i].p_at,p[i].p_bt,p[i].p_ct,p[i].p_tat,p[i].p_wt);
    }
    
}

void sortAccBt(struct Process p[],int start_index ,int ready_process_count)
{
    int isSwapped = 1;

    while(isSwapped)
    {
        isSwapped = 0;
        for(int i = start_index ; i < start_index + ready_process_count -1 ; i++)
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

int getArivedProcess(struct Process p[] , int current_process,int current_time)
{
    int count = 0 ; 
    for(int m = current_process ; p[m].p_at <= current_time ; m++)
    {
        count++;
    }

    return count;
}


int main()
{
    int no_of_process , current_time = 0 ,arrived_process;
    printf("Enter no of process :");
    scanf("%d",&no_of_process);

    struct Process process[no_of_process];

    // take input of p_id, process arrival time , process burst time
    for(int i = 0 ; i < no_of_process ; i++)
    {
        process[i] = input(i+1);
    }

    // sort acc to arrival time and then burst time to get 1st process to execute.
    sortAccAtBt(process,no_of_process);

    display(process,no_of_process);

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
        arrived_process = getArivedProcess(process,i,current_time);
        ////printf("\n--Arrived process from i = %d are %d",i,arrived_process);

        if(arrived_process)
        {
            // sort data acc to burst time till 
            ////printf("\n-----i = %d\n",i);
            sortAccBt(process,i,arrived_process);
            ////printf("\n");
            ////display(process,no_of_process);

            // set new current time
            current_time += process[i].p_bt;

            // data for current process
            process[i].p_ct = current_time /*+ process[i].p_bt;*/;
            process[i].p_tat = process[i].p_ct - process[i].p_at;
            process[i].p_wt = process[i].p_tat - process[i].p_bt;
        } 
        else
        {
            current_time = process[i].p_at;
            // no cal again how many process are there at current time
            arrived_process = getArivedProcess(process,i,current_time);

            // now cal. all data
            // sort data acc to burst time till 
            ////printf("\n-----i = %d\n",i);
            sortAccBt(process,i,arrived_process);
            ////printf("\n");
            ////display(process,no_of_process);

            // set new current time
            current_time += process[i].p_bt;

            // data for current process
            process[i].p_ct = current_time /*+ process[i].p_bt;*/;
            process[i].p_tat = process[i].p_ct - process[i].p_at;
            process[i].p_wt = process[i].p_tat - process[i].p_bt;

        }

    }

    // Now display final order of execution and complete data.
    display(process,no_of_process);

    return 0;
}