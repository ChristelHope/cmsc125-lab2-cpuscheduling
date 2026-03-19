#include <stdio.h>
#include "scheduler.h"

int timeline[1000];
int timeline_length = 0;

void execute_process(Process *p, int *current_time, int run_time) {

    if (p->start_time == -1)
        p->start_time = *current_time;

    *current_time += run_time;
    p->remaining_time -= run_time;

    if (p->remaining_time == 0) {
        p->finish_time = *current_time;
    }
}

int schedule_fcfs(Process *processes, int n) {

    // represents CPU clock time
    int current_time = 0;

    for (int i = 0; i < n; i++) {

        // if CPU is idle, jump to the process arrival time
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }

       int run_time = processes[i].burst_time;
        // record timeline
        for (int t = 0; t < run_time; t++) {
            timeline[timeline_length++] = i;
        }
        // execute using helper
        execute_process(&processes[i], &current_time, run_time);
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
        int run_time = processes[shortest].burst_time;

        // record timeline
        for (int t = 0; t < run_time; t++) {
            timeline[timeline_length++] = shortest;
        }
        execute_process(&processes[shortest], &current_time, run_time);

        visited[shortest] = 1;
        completed++;
    }

    return 0;
} //checks whicb already arrived, chooses one w/smallest burst time,
// runs until it finishes

int schedule_rr(Process *processes, int n, int quantum) {

    int current_time = 0;
    int completed = 0;

    int queue[100];
    int front = 0, rear = 0;

    int added[100] = {0};

    while (completed < n) {

        // add newly arrived processes
        for (int j = 0; j < n; j++) {
            if (!added[j] && processes[j].arrival_time <= current_time) {
                queue[rear++] = j;
                added[j] = 1;
            }
        }

        if (front == rear) {
            current_time++;
            continue;
        }

        int i = queue[front++];

        if (processes[i].remaining_time > 0) {

            int run_time =
                processes[i].remaining_time < quantum
                ? processes[i].remaining_time
                : quantum;

            // record timeline
            for (int t = 0; t < run_time; t++) {
                timeline[timeline_length++] = i;
            }

            execute_process(&processes[i], &current_time, run_time);

            if (processes[i].remaining_time > 0) {
                queue[rear++] = i; // put back in queue
            } else {
                processes[i].finish_time = current_time;
                completed++;
            }
        }
    }

    return 0;
}
//always checks which process has the shortest remaining time,
// runs it for 1 time unit, then checks again, repeats until all finish
// (if shorter job arrives, cpu switches to it immediately)

int schedule_stcf(Process *processes, int n) {

    int current_time = 0;
    int completed = 0;

    while (completed < n) {

        int shortest = -1;
        int min_remaining = 999999;

        // find process with shortest remaining time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time &&
                processes[i].remaining_time > 0 &&
                processes[i].remaining_time < min_remaining) {

                min_remaining = processes[i].remaining_time;
                shortest = i;
            }
        }

        // if no process is ready, CPU is idle
        if (shortest == -1) {
            current_time++;
            continue;
        }

        // record execution (1 time unit only!)
        timeline[timeline_length++] = shortest;

        // execute for 1 unit (preemptive!)
        execute_process(&processes[shortest], &current_time, 1);

        // if finished
        if (processes[shortest].remaining_time == 0) {
            completed++;
        }
    }

    return 0;
}

int schedule_mlfq(Process *processes, int n) {

    int current_time = 0;
    int completed = 0;

    int q0[100], q1[100], q2[100];
    int f0=0,r0=0, f1=0,r1=0, f2=0,r2=0;

    int added[100] = {0};

    int BOOST_INTERVAL = 100;

    while (completed < n) {

        // 🔹 PRIORITY BOOST
        if (current_time > 0 && current_time % BOOST_INTERVAL == 0) {
            f0 = r0 = f1 = r1 = f2 = r2 = 0;

            for (int i = 0; i < n; i++) {
                if (processes[i].remaining_time > 0) {
                    q0[r0++] = i;
                }
            }
        }

        // 🔹 ADD ARRIVALS → Q0
        for (int i = 0; i < n; i++) {
            if (!added[i] && processes[i].arrival_time <= current_time) {
                q0[r0++] = i;
                added[i] = 1;
            }
        }

        int i = -1;
        int level = -1;

        // 🔹 PICK HIGHEST PRIORITY
        if (f0 < r0) {
            i = q0[f0++];
            level = 0;
        } else if (f1 < r1) {
            i = q1[f1++];
            level = 1;
        } else if (f2 < r2) {
            i = q2[f2++];
            level = 2;
        } else {
            current_time++;
            continue;
        }

        int quantum;
        if (level == 0) quantum = 10;
        else if (level == 1) quantum = 20;
        else quantum = processes[i].remaining_time; // FCFS

        int run_time =
            processes[i].remaining_time < quantum
            ? processes[i].remaining_time
            : quantum;

        // 🔹 RECORD TIMELINE
        for (int t = 0; t < run_time; t++) {
            timeline[timeline_length++] = i;
        }

        execute_process(&processes[i], &current_time, run_time);

        // 🔹 IF NOT FINISHED → DEMOTE
        if (processes[i].remaining_time > 0) {
            if (level == 0) q1[r1++] = i;
            else if (level == 1) q2[r2++] = i;
            else q2[r2++] = i;
        } else {
            completed++;
        }
    }

    return 0;
}


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
