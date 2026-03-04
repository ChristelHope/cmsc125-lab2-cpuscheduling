#include "metrics.h"

// Calculates scheduling metrics for each process including turnaround time, waiting time, and response time.

void calculate_metrics(Process *processes, int n) {

    for (int i = 0; i < n; i++) {

        // Turnaround Time = Finish Time - Arrival Time
        processes[i].turnaround_time =
            processes[i].finish_time - processes[i].arrival_time;

        // Waiting Time = Turnaround Time - Burst Time
        processes[i].waiting_time =
            processes[i].turnaround_time - processes[i].burst_time;

        // Response Time = Start Time - Arrival Time
        processes[i].response_time =
            processes[i].start_time - processes[i].arrival_time;
    }
}
