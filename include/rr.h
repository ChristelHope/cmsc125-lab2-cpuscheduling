#ifndef RR_H
#define RR_H

#include "process.h"
#include "gantt_context.h"

int schedule_rr(Process *processes, int n, int quantum, GanttContext *ctx);

#endif