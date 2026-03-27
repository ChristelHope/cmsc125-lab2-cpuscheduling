#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "scheduler.h"
#include "metrics.h"
#include "gantt.h"

#define MAX_PROCESSES 100

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        printf("Usage: %s <workload_file> <algorithm> [quantum]\n", argv[0]);
        return 1;
    }

    Process processes[MAX_PROCESSES];

    char *workload = argv[1];
    char *algorithm = argv[2];

    int n = load_processes(workload, processes, MAX_PROCESSES);

    if (n < 0)
    {
        printf("Error: failed to load processes.\n");
        return 1;
    }

    if (n == 0)
    {
        printf("No processes found.\n");
        return 1;
    }

    if (strcmp(algorithm, "fcfs") == 0)
    {

        reset_processes(processes, n);
        schedule_fcfs(processes, n);
    }
    else if (strcmp(algorithm, "sjf") == 0)
    {

        reset_processes(processes, n);
        schedule_sjf(processes, n);
    }
    else if (strcmp(algorithm, "stcf") == 0)
    {

        reset_processes(processes, n);
        schedule_stcf(processes, n);
    }
    else if (strcmp(algorithm, "rr") == 0)
    {

        if (argc < 4)
        {
            printf("Round Robin requires a quantum.\n");
            return 1;
        }

        int quantum = atoi(argv[3]);
        reset_processes(processes, n);
        schedule_rr(processes, n, quantum);
    }
    else if (strcmp(algorithm, "mlfq") == 0)
    {

        reset_processes(processes, n);
        schedule_mlfq(processes, n);
    }
    else if (strcmp(algorithm, "compare") == 0)
    {
        printf("=== COMPARISON MODE ===\n\n");

// helper macro for safe average printing
#define PRINT_AVG(label)                                    \
    if (n > 0)                                              \
    {                                                       \
        printf(label " -> Avg WT:%d Avg TT:%d Avg RT:%d\n", \
               total_wt / n, total_tt / n, total_rt / n);   \
    }                                                       \
    else                                                    \
    {                                                       \
        printf(label " -> Avg WT:0 Avg TT:0 Avg RT:0\n");   \
    }

        int total_wt, total_tt, total_rt;

        // FCFS
        reset_processes(processes, n);
        schedule_fcfs(processes, n);
        calculate_metrics(processes, n);

        total_wt = total_tt = total_rt = 0;
        for (int i = 0; i < n; i++)
        {
            total_wt += processes[i].waiting_time;
            total_tt += processes[i].turnaround_time;
            total_rt += processes[i].response_time;
        }
        PRINT_AVG("FCFS ");

        // SJF
        reset_processes(processes, n);
        schedule_sjf(processes, n);
        calculate_metrics(processes, n);

        total_wt = total_tt = total_rt = 0;
        for (int i = 0; i < n; i++)
        {
            total_wt += processes[i].waiting_time;
            total_tt += processes[i].turnaround_time;
            total_rt += processes[i].response_time;
        }
        PRINT_AVG("SJF  ");

        // STCF
        reset_processes(processes, n);
        schedule_stcf(processes, n);
        calculate_metrics(processes, n);

        total_wt = total_tt = total_rt = 0;
        for (int i = 0; i < n; i++)
        {
            total_wt += processes[i].waiting_time;
            total_tt += processes[i].turnaround_time;
            total_rt += processes[i].response_time;
        }
        PRINT_AVG("STCF ");

        // RR (q=30)
        reset_processes(processes, n);
        schedule_rr(processes, n, 30);
        calculate_metrics(processes, n);

        total_wt = total_tt = total_rt = 0;
        for (int i = 0; i < n; i++)
        {
            total_wt += processes[i].waiting_time;
            total_tt += processes[i].turnaround_time;
            total_rt += processes[i].response_time;
        }
        PRINT_AVG("RR   ");

        // MLFQ
        reset_processes(processes, n);
        schedule_mlfq(processes, n);
        calculate_metrics(processes, n);

        total_wt = total_tt = total_rt = 0;
        for (int i = 0; i < n; i++)
        {
            total_wt += processes[i].waiting_time;
            total_tt += processes[i].turnaround_time;
            total_rt += processes[i].response_time;
        }
        PRINT_AVG("MLFQ ");

        return 0;
    }
    else
    {

        printf("Unknown algorithm.\n");
        return 1;
    }

    print_gantt_chart(processes, n);

    calculate_metrics(processes, n);

    for (int i = 0; i < n; i++)
    {

        printf("%s Start:%d Finish:%d WT:%d TT:%d RT:%d\n",
               processes[i].pid,
               processes[i].start_time,
               processes[i].finish_time,
               processes[i].waiting_time,
               processes[i].turnaround_time,
               processes[i].response_time);
    }

    return 0;
}