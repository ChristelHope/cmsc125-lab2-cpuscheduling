#include "sjf.h"
#include "scheduler.h"

extern int timeline[];
extern int timeline_length;

int schedule_sjf(Process *processes, int n)
{

  int completed = 0;
  int current_time = 0;
  int visited[MAX_PROCESSES] = {0};

  while (completed < n)
  {

    int shortest = -1;
    int min_burst = 999999;

    for (int i = 0; i < n; i++)
    {

      if (processes[i].arrival_time <= current_time &&
          visited[i] == 0 &&
          (processes[i].burst_time < min_burst ||
           (processes[i].burst_time == min_burst &&
            shortest != -1 &&
            processes[i].arrival_time < processes[shortest].arrival_time)))
      {

        min_burst = processes[i].burst_time;
        shortest = i;
      }
    }

    if (shortest == -1)
    {
      current_time++;
      continue;
    }

    int run_time = processes[shortest].burst_time;

    // record timeline
    for (int t = 0; t < run_time; t++)
    {
      if (timeline_length < MAX_TIMELINE)
        timeline[timeline_length++] = shortest;
    }

    execute_process(&processes[shortest], &current_time, run_time);

    visited[shortest] = 1;
    completed++;
  }

  return 0;
}