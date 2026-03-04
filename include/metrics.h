#ifndef METRICS_H
#define METRICS_H

#include "process.h"

void calculate_metrics(Process *processes, int n);

#endif

// this file declares the function prototype for calculating metrics
// related to the scheduling simulation, such as waiting time,
// turnaround time, and response time for each process.
//
// the function takes an array of Process structures and the number
// of processes as arguments.
//
// the calculate_metrics function will be implemented in metrics.c
// and will compute the performance metrics for each process after
// the scheduling simulation finishes.
//
// these metrics allow us to evaluate the effectiveness of the
// scheduling algorithms used in the simulator.