#ifndef SCHEDULER_H
#define SCHEDULER_H
#define MAX_PROCESSES 100
#define MAX_TIMELINE 1000

#include "process.h"
#include "fcfs.h"
#include "sjf.h"
#include "stcf.h"
#include "rr.h"
#include "mlfq.h"

void execute_process(Process *p, int *current_time, int run_time);

int schedule_fcfs(Process *processes, int n);
int schedule_sjf(Process *processes, int n);
int schedule_stcf(Process *processes, int n);
int schedule_rr(Process *processes, int n, int quantum);
int schedule_mlfq(Process *processes, int n);

void reset_processes(Process *processes, int n);

#endif

// this file declares the function prototypes for the scheduling
// algorithms used in the CPU scheduling simulator.
//
// each function simulates a scheduling algorithm using an array
// of Process structures.
//
// the algorithms implemented include:
// - First Come First Serve (FCFS)
// - Shortest Job First (SJF)
// - Shortest Time to Completion First (STCF)
// - Round Robin (RR)
// - Multi-Level Feedback Queue (MLFQ)
//
// the implementations of these algorithms will be placed in
// the corresponding source files.