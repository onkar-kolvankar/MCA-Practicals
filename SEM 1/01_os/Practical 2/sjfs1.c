/*
    SJFS - Shortest Job First (NON PREEMPTIVE ALGO) 
    METHOD 1 - My way -
        - You need to sort input acc. to the Arrival time and Burst time also.
        - Pid     Arr_time      Bur_time      
            3          1             2                  
            1          1             3                   
            2          2             4                  
            4          4             4                
*/
#include<stdio.h>
void swap(int a , int b)
{
    int temp = a;
    a = b;
    b = temp;  
}
int main()
{
    int total_process;
    printf("Enter no of process :");
    scanf("%d",&total_process);

    int process_id[total_process],arrival_time[total_process],burst_time[total_process],completion_time[total_process],turnaround_time[total_process],waiting_time[total_process];

    for(int i = 0 ; i < total_process ; i++)
    {
        printf("Enter Process Id :");
        scanf("%d",&process_id[i]);

        printf("Enter Arrival Time :");
        scanf("%d",&arrival_time[i]);

        printf("Enter Burst Time :");
        scanf("%d",&burst_time[i]);
    }

    // Sort process on basis of arrival time first
    int swapped = 1,temp;
    while(swapped)
    {
        swapped = 0 ; // if swapping does not take place means that all are in ascending order i.e sorted
        for(int i= 0 ; i < total_process -1 ; i++)
        {
            if( (arrival_time[i] > arrival_time[i+1]) || (arrival_time[i] == arrival_time[i+1] && burst_time[i] > burst_time[i+1]))
            {
                // swap all data of that position 
                // swap arrival time
                // swap(arrival_time[i],arrival_time[i+1]);
                temp = arrival_time[i];
                arrival_time[i] = arrival_time[i+1];
                arrival_time[i+1] = temp;
                // swap process id
                // swap(process_id[i],process_id[i+1]);
                 temp = process_id[i];
                process_id[i] = process_id[i+1];
                process_id[i+1] = temp;

                // swap burst time
                // swap(burst_time[i],burst_time[i+1]);
                 temp = burst_time[i];
                burst_time[i] = burst_time[i+1];
                burst_time[i+1] = temp;

                // set flag variable to 1 => that swapping has taken place
                swapped = 1;
            }

        }
    }

    // find completion time(At what time process ended) = 0 + arrival Time of 1st process + burst time of all process that took place including current process 
    int com_time_sum = 0 + arrival_time[0];
    for(int i = 0 ; i < total_process ; i++)
    {
        // cal completion time
        completion_time[i] = com_time_sum + burst_time[i];
        com_time_sum = com_time_sum + burst_time[i];

        // cal turn around time
        turnaround_time[i] = completion_time[i] - arrival_time[i];

        // cal waiting time
        waiting_time[i] = turnaround_time[i] - burst_time[i];
    }

    // print all process info
    printf("Pid     Arr_time      Bur_time      Comp_time       Turnaround_time     Waiting_time\n");

    for(int i = 0 ; i < total_process ; i++)
    {
        printf("%d          %d             %d              %d                 %d                  %d\n",process_id[i],arrival_time[i],burst_time[i],completion_time[i],turnaround_time[i],waiting_time[i]);
    }

    // print average waiting time and average turn around time
    float avg_wt = 0 ,avg_tat = 0;
    for(int i = 0 ; i < total_process ; i++)
    {
        avg_wt += waiting_time[i];
        avg_tat += turnaround_time[i];
    }
    printf("Average Waiting Time = %f\nAverage Turnaround Time = %f",avg_wt/total_process,avg_tat/total_process);
    return 0;
}