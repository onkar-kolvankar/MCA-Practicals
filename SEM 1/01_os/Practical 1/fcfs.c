#include<stdio.h>
int main()
{
    int total_process;
    printf("Enter no of process :");
    scanf("%d",&total_process);

    int process_id[total_process] , arrival_time[total_process] , burst_time[total_process],completion_time[total_process],turnaround_time[total_process],waiting_time[total_process];


    for(int i = 0 ; i < total_process ; i++)
    {
        printf("Enter Process No :");
        scanf("%d",&process_id[i]);

        printf("Enter Arrival time:");
        scanf("%d",&arrival_time[i]);

        printf("Enter Burst time :");
        scanf("%d",&burst_time[i]);
    }

    // code to sort arrays Arrival time and accordingly change positions of process  id and burst time
    int swapped = 1 ,temp;
    while (swapped)
    {
        swapped = 0 ;
        for(int i = 0 ; i < total_process  -1 ; i ++)
        {
            if(arrival_time[i] > arrival_time[i+1])
            {
                // 23 4 -> so swap their arri_time and note their index to swap respective process no and burst time
                
                // Swap arival time
                temp  = arrival_time[i];
                arrival_time[i] = arrival_time[i+1];
                arrival_time[i+1] = temp;

                // swap process no
                temp  = process_id[i];
                process_id[i] = process_id[i+1];
                process_id[i+1] = temp;

                // swap burst time
                temp  = burst_time[i];
                burst_time[i] = burst_time[i+1];
                burst_time[i+1] = temp;

                swapped = 1;
            }
        }
    }

    // Now cal completion time , turn around time and waiting time
    
    // Completion time = Sum of all prev Burst time + Current Burst time
    // Turn around time = Completion time - arrival time -> how much time process is in the system
    // Waiting time = Turnaround time - burst time
    int bt_sum = 0;
    for(int i = 0 ; i < total_process ; i++)
    {
        // burst time
        completion_time[i] = bt_sum + burst_time[i];
        bt_sum = bt_sum + burst_time[i];

        // Turn around time
        turnaround_time[i] = completion_time[i] - arrival_time[i];

        // Waiting time
        waiting_time[i] = turnaround_time[i] - burst_time[i];
    }

     // print all process info
    printf("Pid     Arr_time      Bur_time      Comp_time       Turnaround_time     Waiting_time\n");

    for(int i = 0 ; i < total_process ; i++)
    {
        printf("%d          %d             %d              %d                 %d                  %d\n",process_id[i],arrival_time[i],burst_time[i],completion_time[i],turnaround_time[i],waiting_time[i]);
    }
    return 0;
}