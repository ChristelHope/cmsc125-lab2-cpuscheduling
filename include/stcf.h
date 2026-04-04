#ifndef STCF_H
#define STCF_H

#include "process.h"
#include "gantt_context.h"

int schedule_stcf(Process *processes, int n, GanttContext *ctx);

#endif