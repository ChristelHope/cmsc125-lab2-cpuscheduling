#include <stdio.h>
#include "scheduler.h"

int timeline[1000];
int timeline_length = 0;

int schedule_fcfs(Process *processes, int n) {

    // represents CPU clock time
    int current_time = 0;

    for (int i = 0; i < n; i++) {

        // if CPU is idle, jump to the process arrival time
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }

        // records when the process starts
        processes[i].start_time = current_time;

        // execute process
        current_time += processes[i].burst_time;

        // record completion
        processes[i].finish_time = current_time;

        // update remaining time
        processes[i].remaining_time = 0;
    }

    return 0;
}// Processes are executed in the order they arrive, once one starts running,
// it runs until completion

int schedule_sjf(Process *processes, int n) {

    int completed = 0;
    int current_time = 0;
    int visited[100] = {0};

    while (completed < n) {

        int shortest = -1;
        int min_burst = 999999;

        for (int i = 0; i < n; i++) {

            if (processes[i].arrival_time <= current_time &&
                visited[i] == 0 &&
                (processes[i].burst_time < min_burst ||
                (processes[i].burst_time == min_burst &&
                shortest != -1 &&
                processes[i].arrival_time < processes[shortest].arrival_time))) {

                min_burst = processes[i].burst_time;
                shortest = i;
            }
        }

        if (shortest == -1) {
            current_time++;
            continue;
        }

        processes[shortest].start_time = current_time;

        current_time += processes[shortest].burst_time;

        processes[shortest].finish_time = current_time;

        processes[shortest].remaining_time = 0;

        visited[shortest] = 1;

        completed++;
    }

    return 0;
} //checks whicb already arrived, chooses one w/smallest burst time,
// runs until it finishes

int schedule_rr(Process *processes, int n, int quantum) {

    int current_time = 0;
    int completed = 0;

    while (completed < n) {

        int executed = 0;

        for (int i = 0; i < n; i++) {

            if (processes[i].remaining_time > 0 &&
                processes[i].arrival_time <= current_time) {

                if (processes[i].start_time == -1)
                    processes[i].start_time = current_time;

                int run_time =
                    processes[i].remaining_time < quantum
                    ? processes[i].remaining_time
                    : quantum;

                current_time += run_time;

                processes[i].remaining_time -= run_time;

                if (processes[i].remaining_time == 0) {
                    processes[i].finish_time = current_time;
                    completed++;
                }

                executed = 1;
            }
        }

        if (!executed)
            current_time++;
    }

    return 0;
} //gives each porcess a small CPU time slice, moves to the next one, 
//repeats until all finish

int schedule_stcf(Process *processes, int n) {

    int current_time = 0;
    int completed = 0;

    while (completed < n) {

        int shortest = -1;
        int min_remaining = 999999;

        for (int i = 0; i < n; i++) {

            if (processes[i].arrival_time <= current_time &&
                processes[i].remaining_time > 0 &&
                processes[i].remaining_time < min_remaining) {

                min_remaining = processes[i].remaining_time;
                shortest = i;
            }
        }

        if (shortest == -1) {
            current_time++;
            continue;
        }

        if (processes[shortest].start_time == -1)
            processes[shortest].start_time = current_time;

        timeline[timeline_length++] = shortest;

        processes[shortest].remaining_time--;

        current_time++;

        if (processes[shortest].remaining_time == 0) {

            processes[shortest].finish_time = current_time;
            completed++;
        }
    }

    return 0;
} 

//always checks which process has the shortest remaining time,
// runs it for 1 time unit, then checks again, repeats until all finish
// (if shorter job arrives, cpu switches to it immediately)

void reset_processes(Process *processes, int n) {

    timeline_length = 0;

    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].start_time = -1;
        processes[i].finish_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].response_time = 0;
        processes[i].timeline_length = 0;
    }
}
