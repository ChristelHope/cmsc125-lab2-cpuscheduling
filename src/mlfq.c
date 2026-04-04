#include "mlfq.h"
#include "scheduler.h"
#include "gantt_context.h"

int schedule_mlfq(Process *processes, int n, GanttContext *ctx)
{
  int current_time = 0;
  int completed = 0;

  // struct instead of raw arrays
  MLFQScheduler sched;

  for (int i = 0; i < MLFQ_LEVELS; i++)
  {
    sched.levels[i].front = 0;
    sched.levels[i].rear = 0;
  }

  sched.levels[0].quantum = 10;
  sched.levels[1].quantum = 20;
  sched.levels[2].quantum = 0; // FCFS

  int added[MAX_PROCESSES] = {0};
  int BOOST_INTERVAL = 100;

  while (completed < n)
  {
    // priority boost
    if (current_time > 0 && current_time % BOOST_INTERVAL == 0)
    {
      for (int i = 0; i < MLFQ_LEVELS; i++)
      {
        sched.levels[i].front = 0;
        sched.levels[i].rear = 0;
      }

      for (int i = 0; i < n; i++)
      {
        if (processes[i].remaining_time > 0)
        {
          if (sched.levels[0].rear < MAX_PROCESSES)
            sched.levels[0].queue[sched.levels[0].rear++] = i;
        }
      }
    }

    // add arrivals → Q0
    for (int i = 0; i < n; i++)
    {
      if (!added[i] && processes[i].arrival_time <= current_time)
      {
        if (sched.levels[0].rear < MAX_PROCESSES)
          sched.levels[0].queue[sched.levels[0].rear++] = i;
        added[i] = 1;
      }
    }

    int i = -1;
    int level = -1;

    // pick highest priority
    if (sched.levels[0].front < sched.levels[0].rear)
    {
      i = sched.levels[0].queue[sched.levels[0].front++];
      level = 0;
    }
    else if (sched.levels[1].front < sched.levels[1].rear)
    {
      i = sched.levels[1].queue[sched.levels[1].front++];
      level = 1;
    }
    else if (sched.levels[2].front < sched.levels[2].rear)
    {
      i = sched.levels[2].queue[sched.levels[2].front++];
      level = 2;
    }
    else
    {
      current_time++;
      continue;
    }

    int quantum;
    if (level == 0)
      quantum = sched.levels[0].quantum;
    else if (level == 1)
      quantum = sched.levels[1].quantum;
    else
      quantum = processes[i].remaining_time; // FCFS

    int run_time =
        processes[i].remaining_time < quantum
            ? processes[i].remaining_time
            : quantum;

    // record timeline
    for (int t = 0; t < run_time; t++)
    {
      if (ctx->length < MAX_TIMELINE)
        ctx->timeline[ctx->length++] = i;
    }

    execute_process(&processes[i], &current_time, run_time);

    // demotion
    if (processes[i].remaining_time > 0)
    {
      if (level == 0)
      {
        if (sched.levels[1].rear < MAX_PROCESSES)
          sched.levels[1].queue[sched.levels[1].rear++] = i;
      }
      else if (level == 1)
      {
        if (sched.levels[2].rear < MAX_PROCESSES)
          sched.levels[2].queue[sched.levels[2].rear++] = i;
      }
      else
      {
        if (sched.levels[2].rear < MAX_PROCESSES)
          sched.levels[2].queue[sched.levels[2].rear++] = i;
      }
    }
    else
    {
      completed++;
    }
  }

  return 0;
}