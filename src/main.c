#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "scheduler.h"
#include "metrics.h"
#include "gantt.h"
#include "gantt_context.h"

#define MAX_PROCESSES 100

int main(int argc, char *argv[])
{
    Process processes[MAX_PROCESSES];

    char *workload = NULL;
    char *algorithm = NULL;
    int quantum = -1;

    // parse flags first
    for (int i = 1; i < argc; i++)
    {
        if (strncmp(argv[i], "--input=", 8) == 0)
        {
            workload = argv[i] + 8;
        }
        else if (strncmp(argv[i], "--algorithm=", 12) == 0)
        {
            algorithm = argv[i] + 12;
        }
        else if (strncmp(argv[i], "--quantum=", 10) == 0)
        {
            char *end;
            long q = strtol(argv[i] + 10, &end, 10);

            if (*end != '\0' || q <= 0)
            {
                printf("Invalid quantum value.\n");
                return 1;
            }

            quantum = (int)q;
        }
    }

    // validate required flags
    if (workload == NULL || algorithm == NULL)
    {
        printf("Usage: %s --input=<file> --algorithm=<algo> [--quantum=N]\n", argv[0]);
        return 1;
    }

    // now load processes (correct order)
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

    // input validation
    for (int i = 0; i < n; i++)
    {
        if (processes[i].arrival_time < 0)
        {
            printf("Error: Process %s has negative arrival time.\n", processes[i].pid);
            return 1;
        }

        if (processes[i].burst_time <= 0)
        {
            printf("Error: Process %s has invalid burst time.\n", processes[i].pid);
            return 1;
        }
    }

    // gantt context
    GanttContext ctx;
    ctx.capacity = 1000;
    ctx.length = 0;
    ctx.timeline = malloc(sizeof(int) * ctx.capacity);

    if (ctx.timeline == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // algorithm dispatch
    if (strcmp(algorithm, "fcfs") == 0)
    {
        reset_processes(processes, n);
        schedule_fcfs(processes, n, &ctx);
    }
    else if (strcmp(algorithm, "sjf") == 0)
    {
        reset_processes(processes, n);
        schedule_sjf(processes, n, &ctx);
    }
    else if (strcmp(algorithm, "stcf") == 0)
    {
        reset_processes(processes, n);
        schedule_stcf(processes, n, &ctx);
    }
    else if (strcmp(algorithm, "rr") == 0)
    {
        if (quantum <= 0)
        {
            printf("Round Robin requires a valid --quantum=N.\n");
            free(ctx.timeline);
            return 1;
        }

        reset_processes(processes, n);
        schedule_rr(processes, n, quantum, &ctx);
    }
    else if (strcmp(algorithm, "mlfq") == 0)
    {
        reset_processes(processes, n);
        schedule_mlfq(processes, n, &ctx);
    }
    else if (strcmp(algorithm, "compare") == 0)
    {
        printf("=== COMPARISON MODE ===\n\n");

#define PRINT_AVG(label)                                    \
    if (n > 0)                                              \
    {                                                       \
        printf(label " -> Avg WT:%d Avg TT:%d Avg RT:%d\n", \
               total_wt / n, total_tt / n, total_rt / n);   \
    }

        int total_wt, total_tt, total_rt;

        // FCFS
        reset_processes(processes, n);
        schedule_fcfs(processes, n, &ctx);
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
        schedule_sjf(processes, n, &ctx);
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
        schedule_stcf(processes, n, &ctx);
        calculate_metrics(processes, n);

        total_wt = total_tt = total_rt = 0;
        for (int i = 0; i < n; i++)
        {
            total_wt += processes[i].waiting_time;
            total_tt += processes[i].turnaround_time;
            total_rt += processes[i].response_time;
        }
        PRINT_AVG("STCF ");

        // RR
        reset_processes(processes, n);
        schedule_rr(processes, n, 30, &ctx);
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
        schedule_mlfq(processes, n, &ctx);
        calculate_metrics(processes, n);

        total_wt = total_tt = total_rt = 0;
        for (int i = 0; i < n; i++)
        {
            total_wt += processes[i].waiting_time;
            total_tt += processes[i].turnaround_time;
            total_rt += processes[i].response_time;
        }
        PRINT_AVG("MLFQ ");

        free(ctx.timeline);
        return 0;
    }
    else
    {
        printf("Unknown algorithm.\n");
        free(ctx.timeline);
        return 1;
    }

    print_gantt_chart(&ctx, processes, n);
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

    free(ctx.timeline);
    return 0;
}