#include <stdio.h>
#include "scheduler.h"

// Implements First Come First Serve (FCFS) scheduling.
// Processes are executed in the order they arrive.
// Once a process starts running, it runs until completion.

int schedule_fcfs(Process *processes, int n) {

    int current_time = 0;

    for (int i = 0; i < n; i++) {

        // if CPU is idle, jump to the process arrival time
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }

        // first time the process gets CPU
        processes[i].start_time = current_time;

        // execute process
        current_time += processes[i].burst_time;

        // record completion
        processes[i].finish_time = current_time;

        // update remaining time
        processes[i].remaining_time = 0;
    }

    return 0;
}
