#include "fcfs.h"
#include "scheduler.h"
#include "gantt_context.h"
#include <stdio.h>

int schedule_fcfs(Process *processes, int n, GanttContext *ctx)
{
  int current_time = 0;

  // declare once for entire function
  int warned = 0;

  // sort by arrival time
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      if (processes[j].arrival_time < processes[i].arrival_time)
      {
        Process temp = processes[i];
        processes[i] = processes[j];
        processes[j] = temp;
      }
    }
  }

  // FCFS execution
  for (int i = 0; i < n; i++)
  {
    if (current_time < processes[i].arrival_time)
    {
      current_time = processes[i].arrival_time;
    }

    int run_time = processes[i].burst_time;

    for (int t = 0; t < run_time; t++)
    {
      if (ctx->length < ctx->capacity)
      {
        ctx->timeline[ctx->length++] = i;
      }
      else if (!warned)
      {
        fprintf(stderr, "Warning: timeline truncated (capacity reached).\n");
        warned = 1;
      }
    }

    execute_process(&processes[i], &current_time, run_time);
  }

  return 0;
}