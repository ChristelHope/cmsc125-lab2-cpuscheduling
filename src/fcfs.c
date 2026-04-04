#include "fcfs.h"
#include "scheduler.h"

extern int timeline[];
extern int timeline_length;

int schedule_fcfs(Process *processes, int n)
{
  // represents CPU clock time
  int current_time = 0;

  for (int i = 0; i < n; i++)
  {
    if (current_time < processes[i].arrival_time)
    {
      current_time = processes[i].arrival_time;
    }

    int run_time = processes[i].burst_time;

    for (int t = 0; t < run_time; t++)
    {
      if (timeline_length < MAX_TIMELINE)
        timeline[timeline_length++] = i;
    }

    execute_process(&processes[i], &current_time, run_time);
  }
  return 0;
}