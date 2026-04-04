#include "stcf.h"
#include "scheduler.h"
#include "gantt_context.h"

extern int timeline[];
extern int timeline_length;

int schedule_stcf(Process *processes, int n, GanttContext *ctx)
{

  int current_time = 0;
  int completed = 0;

  while (completed < n)
  {

    int shortest = -1;
    int min_remaining = 999999;

    // find process with shortest remaining time
    for (int i = 0; i < n; i++)
    {
      if (processes[i].arrival_time <= current_time &&
          processes[i].remaining_time > 0 &&
          processes[i].remaining_time < min_remaining)
      {

        min_remaining = processes[i].remaining_time;
        shortest = i;
      }
    }

    // if no process is ready, CPU is idle
    if (shortest == -1)
    {
      current_time++;
      continue;
    }

    // record execution (1 time unit only!)
    if (ctx->length < MAX_TIMELINE)
      ctx->timeline[ctx->length++] = shortest;

    // execute for 1 unit (preemptive!)
    execute_process(&processes[shortest], &current_time, 1);

    // if finished
    if (processes[shortest].remaining_time == 0)
    {
      completed++;
    }
  }

  return 0;
}