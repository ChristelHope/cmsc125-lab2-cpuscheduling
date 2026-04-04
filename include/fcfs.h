#ifndef FCFS_H
#define FCFS_H

#include "process.h"
#include "gantt_context.h"

int schedule_fcfs(Process *processes, int n, GanttContext *ctx);

#endif