#ifndef GANTT_H
#define GANTT_H

#include "process.h"

void print_gantt_chart(Process *processes, int n);

#endif

// this file declares the function responsible for generating
// and displaying the gantt chart of the scheduling simulation.
//
// the gantt chart visually represents how processes are executed
// on the CPU over time.
//
// the function will use the scheduling information stored in the
// Process structures (such as start time and finish time) to
// construct a timeline of execution.
//
// the implementation of this function will be written in gantt.c.