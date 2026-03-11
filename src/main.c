#include <stdio.h>
#include "parser.h"
#include "scheduler.h"
#include "metrics.h"
#include "gantt.h"

#define MAX_PROCESSES 100

int main() {

    // creates storage for process data
    Process processes[MAX_PROCESSES];

    // load process from one file then returns number of processes
    int n = load_processes("tests/workload1.txt", processes, MAX_PROCESSES);

    // runs algo scheduling; edit line below to test different algos
      //schedule_fcfs(processes, n);
    schedule_sjf(processes, n);
    //schedule_stcf(processes, n);
    //schedule_rr(processes, n, 2);             //quantum of 2 time units

    print_gantt_chart(processes, n);

    // computes the waiting, turnaround and return time
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

