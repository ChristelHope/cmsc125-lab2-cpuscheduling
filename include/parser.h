#ifndef PARSER_H
#define PARSER_H

#include "process.h"

// reads process data from a workload file and stores it
// in the given Process array. Returns the number of
// processes successfully loaded.

int load_processes(const char *filename, Process processes[], int max_processes);

#endif

// This file declares the function used to read workload files for the CPU scheduling simulator.
// Each workload file contains process information such as PID, arrival time, and burst time.
// The load_processes function parses the file and stores the data into an array of Process structures so it can be used by the scheduling algorithms.
