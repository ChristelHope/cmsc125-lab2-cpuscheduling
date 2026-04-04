#include <stdio.h>
#include "scheduler.h"

#define MAX_PROCESSES 100

void execute_process(Process *p, int *current_time, int run_time)
{

    if (p->start_time == -1)
        p->start_time = *current_time;

    *current_time += run_time;
    p->remaining_time -= run_time;

    if (p->remaining_time == 0)
    {
        p->finish_time = *current_time;
    }
}

void reset_processes(Process *processes, int n)
{

    for (int i = 0; i < n; i++)
    {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].start_time = -1;
        processes[i].finish_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].response_time = 0;
    }
}