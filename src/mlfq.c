#include "mlfq.h"
#include "scheduler.h"

extern int timeline[];
extern int timeline_length;

int schedule_mlfq(Process *processes, int n)
{

  int current_time = 0;
  int completed = 0;

  int q0[MAX_PROCESSES], q1[MAX_PROCESSES], q2[MAX_PROCESSES];
  int f0 = 0, r0 = 0, f1 = 0, r1 = 0, f2 = 0, r2 = 0;

  int added[MAX_PROCESSES] = {0};

  int BOOST_INTERVAL = 100;

  while (completed < n)
  {

    // priority boost
    if (current_time > 0 && current_time % BOOST_INTERVAL == 0)
    {
      f0 = r0 = f1 = r1 = f2 = r2 = 0;

      for (int i = 0; i < n; i++)
      {
        if (processes[i].remaining_time > 0)
        {
          if (r0 < MAX_PROCESSES)
            q0[r0++] = i;
        }
      }
    }

    // ADD ARRIVALS → Q0
    for (int i = 0; i < n; i++)
    {
      if (!added[i] && processes[i].arrival_time <= current_time)
      {
        if (r0 < MAX_PROCESSES)
          q0[r0++] = i;
        added[i] = 1;
      }
    }

    int i = -1;
    int level = -1;

    // pick highest priority
    if (f0 < r0)
    {
      i = q0[f0++];
      level = 0;
    }
    else if (f1 < r1)
    {
      i = q1[f1++];
      level = 1;
    }
    else if (f2 < r2)
    {
      i = q2[f2++];
      level = 2;
    }
    else
    {
      current_time++;
      continue;
    }

    int quantum;
    if (level == 0)
      quantum = 10;
    else if (level == 1)
      quantum = 20;
    else
      quantum = processes[i].remaining_time; // FCFS

    int run_time =
        processes[i].remaining_time < quantum
            ? processes[i].remaining_time
            : quantum;

    // record timeline
    for (int t = 0; t < run_time; t++)
    {
      if (timeline_length < MAX_TIMELINE)
        timeline[timeline_length++] = i;
    }

    execute_process(&processes[i], &current_time, run_time);

    // IF NOT FINISHED → DEMOTE
    if (processes[i].remaining_time > 0)
    {
      if (level == 0)
      {
        if (r1 < MAX_PROCESSES)
          q1[r1++] = i;
      }
      else if (level == 1)
      {
        if (r2 < MAX_PROCESSES)
          q2[r2++] = i;
      }
      else
      {
        if (r2 < MAX_PROCESSES)
          q2[r2++] = i;
      }
    }
    else
    {
      completed++;
    }
  }

  return 0;
}