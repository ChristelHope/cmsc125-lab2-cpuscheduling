#ifndef SJF_H
#define SJF_H

#include "process.h"
#include "gantt_context.h"

int schedule_sjf(Process *processes, int n, GanttContext *ctx);

#endif