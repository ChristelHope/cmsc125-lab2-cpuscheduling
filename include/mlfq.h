#ifndef MLFQ_H
#define MLFQ_H

#include "process.h"
#include "gantt_context.h"

#define MLFQ_LEVELS 3

typedef struct
{
  int queue[100]; // can keep static for now
  int front;
  int rear;
  int quantum;
} MLFQQueue;

typedef struct
{
  MLFQQueue levels[MLFQ_LEVELS];
} MLFQScheduler;

int schedule_mlfq(Process *processes, int n, GanttContext *ctx);

#endif