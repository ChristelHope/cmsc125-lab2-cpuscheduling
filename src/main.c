#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "scheduler.h"
#include "metrics.h"
#include "gantt.h"

#define MAX_PROCESSES 100

int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("Usage: %s <workload_file> <algorithm> [quantum]\n", argv[0]);
        return 1;
    }

    Process processes[MAX_PROCESSES];

    char *workload = argv[1];
    char *algorithm = argv[2];

    int n = load_processes(workload, processes, MAX_PROCESSES);

    if (strcmp(algorithm, "fcfs") == 0) {

        reset_processes(processes, n);
        schedule_fcfs(processes, n);

    } else if (strcmp(algorithm, "sjf") == 0) {

        reset_processes(processes, n);
        schedule_sjf(processes, n);

    } else if (strcmp(algorithm, "stcf") == 0) {

        reset_processes(processes, n);
        schedule_stcf(processes, n);

    } else if (strcmp(algorithm, "rr") == 0) {

        if (argc < 4) {
            printf("Round Robin requires a quantum.\n");
            return 1;
        }

        int quantum = atoi(argv[3]);
        reset_processes(processes, n);
        schedule_rr(processes, n, quantum);

    } else {

        printf("Unknown algorithm.\n");
        return 1;
    }

    print_gantt_chart(processes, n);

    calculate_metrics(processes, n);

    for (int i = 0; i < n; i++) {

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