#include "metrics.h"

// Calculates scheduling metrics for each process including turnaround time, waiting time, and response time.

void calculate_metrics(Process *processes, int n) {

    if (n <= 0) return; // safety guard

    for (int i = 0; i < n; i++) {

        // validate finish_time
        if (processes[i].finish_time >= processes[i].arrival_time) {
            processes[i].turnaround_time =
                processes[i].finish_time - processes[i].arrival_time;
        } else {
            processes[i].turnaround_time = 0;
        }

        // waiting time (never negative)
        processes[i].waiting_time =
            processes[i].turnaround_time - processes[i].burst_time;

        if (processes[i].waiting_time < 0)
            processes[i].waiting_time = 0;

        // response time (only if started)
        if (processes[i].start_time >= processes[i].arrival_time) {
            processes[i].response_time =
                processes[i].start_time - processes[i].arrival_time;
        } else {
            processes[i].response_time = 0;
        }
    }
}
