// C program for implementation of RR scheduling
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int burst_time[], int process_id[], int i)
{
    int t;
    t = burst_time[i + 1];
    burst_time[i + 1] = burst_time[i];
    burst_time[i] = t;

    t = process_id[i + 1];
    process_id[i + 1] = process_id[i];
    process_id[i] = t;
}

void sort(int process_id[100], int burst_time[100], int n, int x)
{
    int i, j, t;

    for (j = 0; j < n; j++)
    {
        for (i = 0; i < n - 1; i++)
        {
            if (x == 1)
            {
                if (burst_time[i + 1] < burst_time[i])
                {
                    swap(burst_time, process_id, i);
                }
            }
            else
            {
                if (process_id[i + 1] < process_id[i])
                {
                    swap(burst_time, process_id, i);
                }
            }
        }
    }
}

int quantum_time(int i, int n, int qt[4])
{
    int quantum, x;

    if (i < n / 4)
    {
        quantum = qt[0];
        x = 0;
    }
    else if (i < 2 * (n / 4))
    {
        quantum = qt[1];
        x = 1;
    }
    else if (i < 3 * (n / 4))
    {
        quantum = qt[2];
        x = 2;
    }
    else
    {
        quantum = qt[3];
        x = 3;
    }

    return quantum;
}

void findWaitingTime(int process_id[100], int n,
                     int bt[100], int wt[100])
{
    int i;

    for (i = 0; i < n; i++)
    {
        wt[i] = 0;
    }

    int x1[10], x2[10], x3[10], x4[10], sum = 0, cnt = 0, qt[4];
    for (i = 0; i < n / 4; i++)
    {
        x1[i] = process_id[i];
        sum += bt[i];
    }
    qt[0] = sum / (n / 4);
    sum = 0;

    for (i = 0; i < n / 4; i++)
    {
        x2[i] = process_id[i + n / 4];
        sum += bt[i + n / 4];
    }
    qt[1] = sum / (n / 4);
    sum = 0;
    for (i = 0; i < n / 4; i++)
    {
        x3[i] = process_id[i + 2 * (n / 4)];
        sum += bt[i + 2 * (n / 4)];
    }
    qt[2] = sum / (n / 4);
    sum = 0;
    int j = 0;
    for (i = 3 * (n / 4); i < n; i++)
    {
        x4[j] = process_id[i];
        sum += bt[i];
        j++;
    }

    qt[3] = sum / (n - (3 * (n / 4)));

    int rem_bt[n];

    for (i = 0; i < n; i++)
    {
        rem_bt[i] = bt[i];
    }

    int t = 0; // Current time
    printf("\nTime: %d", t);

    // Keep traversing process_id in round robin manner
    // until all of them are not done.
    int quantum;
    printf("\n");
    while (1)
    {
        bool done = true;
        int x = 0;

        // Traverse all process_id one by one repeatedly
        for (i = 0; i < n; i++)
        {
            ;
            quantum = quantum_time(i, n, qt);

            if (rem_bt[i] > 0)
            {
                done = false; // There is a pending process

                if (rem_bt[i] < 0.1 * bt[i])
                {

                    t = t + rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }

                if (rem_bt[i] > quantum)
                {
                    t += quantum;
                    printf("t-2: %d \n", t);

                    rem_bt[i] -= quantum;
                }

                else
                {
                    t = t + rem_bt[i];
                    wt[i] = t - bt[i];

                    //For next process if it satisfies next for loop
                    if (i != n - 1 && rem_bt[i + 1] > quantum_time(i + 1, n, qt))
                    {
                        wt[i + 1] += rem_bt[i];
                    }

                    rem_bt[i] = 0;
                }
                printf("Run Process: %d, TQ: %d, BT Remaining: %d, Waiting_Time: %d \n", process_id[i], quantum, rem_bt[i], wt[i]);
                printf("Time: %d\n", t);
            }
        }

        // If all processes are done
        if (done == true)
            break;
    }
}

// Function to calculate turn around time
void findTurnAroundTime(int process_id[], int n,
                        int bt[], int wt[], int tat[])
{
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    int i;

    for (i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

// Function to calculate average time
void findavgTime(int process_id[], int n, int bt[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0, i;

    // Function to find waiting time of all processes
    findWaitingTime(process_id, n, bt, wt);

    // Function to find turn around time for all processes
    findTurnAroundTime(process_id, n, bt, wt, tat);

    // Sort and Display process_id along with all details
    sort(process_id, bt, n, 0);

    //  printf("\nProcesses  Burst_time  Waiting_time  Turn_around_time\n");

    // Calculate total waiting time and total turn
    // around time
    for (i = 0; i < n; i++)
    {
        printf("wt[i]: %d\n", wt[i]);
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        // printf("    %d \t\t %d \t   %d \t\t %d \n",process_id[i],bt[i],wt[i],tat[i]);
    }

    printf("\nAverage waiting time = %f", (float)total_wt / (float)n);
    printf("\nAverage turn around time = %f", (float)total_tat / (float)n);
}

// Driver code
int main()
{
    int j;
    for (j = 0; j < 15; j++)
    {
        int n = 10, i;
        //printf("Enter number of processes: ");
        //scanf("%d",&n);

        int process_id[n];

        // Burst time of all processes
        int burst_time[n];
        printf("Enter burst time of process");

        for (i = 0; i < n; i++)
        {
            process_id[i] = i + 1;
            scanf("%d", &burst_time[i]);
        }

        sort(process_id, burst_time, n, 1);

        findavgTime(process_id, n, burst_time);
    }

    return 0;
}
