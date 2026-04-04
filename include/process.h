#ifndef PROCESS_H
#define PROCESS_H
#define MAX_PROCESSES 100

typedef struct
{
    char pid[16];

    int arrival_time;
    int burst_time;
    int remaining_time;

    int start_time;
    int finish_time;

    int waiting_time;
    int turnaround_time;
    int response_time;

    int priority;
    int time_in_queue;

} Process;

#endif

// this file defines the Process structure, which represents each
// process in the scheduling simulation.
//
// it includes fields for:
// - process id
// - arrival time
// - burst time
// - remaining execution time
// - start and finish times
// - scheduling metrics (waiting time, turnaround time, response time)
//
// additional fields like priority and time_in_queue are useful
// for algorithms such as multi-level feedback queue (MLFQ).
//
// this structure will be used throughout the program to store
// and update process information during simulation.