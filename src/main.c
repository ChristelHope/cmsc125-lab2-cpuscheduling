#include <stdio.h>
#include "parser.h"
#include "scheduler.h"
#include "metrics.h"

#define MAX_PROCESSES 100

int main() {

    Process processes[MAX_PROCESSES];

    int n = load_processes("tests/workload1.txt", processes, MAX_PROCESSES);

    schedule_fcfs(processes, n);

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
