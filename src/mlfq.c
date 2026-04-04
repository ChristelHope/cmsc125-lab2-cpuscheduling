#include "mlfq.h"
#include "scheduler.h"
#include "gantt_context.h"

int schedule_mlfq(Process *processes, int n, GanttContext *ctx)
{
  int current_time = 0;
  int completed = 0;

  MLFQScheduler sched;

  // initialize queues
  for (int i = 0; i < MLFQ_LEVELS; i++)
  {
    sched.levels[i].front = 0;
    sched.levels[i].rear = 0;
  }

  sched.levels[0].quantum = 10;
  sched.levels[1].quantum = 20;
  sched.levels[2].quantum = 0; // FCFS

  int allotment[MLFQ_LEVELS] = {50, 100, 1000000};

  int added[MAX_PROCESSES] = {0};
  int BOOST_INTERVAL = 100;

  while (completed < n)
  {
    // priority boost
    if (current_time > 0 && current_time % BOOST_INTERVAL == 0)
    {
      while (sched.levels[1].front < sched.levels[1].rear)
      {
        int pid = sched.levels[1].queue[sched.levels[1].front++];
        sched.levels[0].queue[sched.levels[0].rear++] = pid;
        processes[pid].time_in_queue = 0;
      }

      while (sched.levels[2].front < sched.levels[2].rear)
      {
        int pid = sched.levels[2].queue[sched.levels[2].front++];
        sched.levels[0].queue[sched.levels[0].rear++] = pid;
        processes[pid].time_in_queue = 0;
      }

      sched.levels[1].front = sched.levels[1].rear = 0;
      sched.levels[2].front = sched.levels[2].rear = 0;
    }

    // add arrivals -> Q0
    for (int i = 0; i < n; i++)
    {
      if (!added[i] && processes[i].arrival_time <= current_time)
      {
        sched.levels[0].queue[sched.levels[0].rear++] = i;
        added[i] = 1;
      }
    }

    int i = -1;
    int level = -1;

    // pick next process
    for (int l = 0; l < MLFQ_LEVELS; l++)
    {
      if (sched.levels[l].front < sched.levels[l].rear)
      {
        i = sched.levels[l].queue[sched.levels[l].front++];
        level = l;
        break;
      }
    }

    if (i == -1)
    {
      current_time++;
      continue;
    }

    int quantum = (level == 2)
                      ? processes[i].remaining_time
                      : sched.levels[level].quantum;

    int run_time = (processes[i].remaining_time < quantum)
                       ? processes[i].remaining_time
                       : quantum;

    // record timeline
    for (int t = 0; t < run_time; t++)
    {
      if (ctx->length < ctx->capacity)
        ctx->timeline[ctx->length++] = i;
    }

    execute_process(&processes[i], &current_time, run_time);
    processes[i].time_in_queue += run_time;

    // allotment tracking
    processes[i].time_in_queue += run_time;

    if (processes[i].remaining_time > 0)
    {
      // check allotment BEFORE demoting
      if (processes[i].time_in_queue >= allotment[level])
      {
        processes[i].time_in_queue = 0; // reset on demotion

        if (level < MLFQ_LEVELS - 1)
        {
          sched.levels[level + 1].queue[sched.levels[level + 1].rear++] = i;
        }
        else
        {
          // already lowest -> stay
          sched.levels[level].queue[sched.levels[level].rear++] = i;
        }
      }
      else
      {
        // still within allotment -> stay in same queue
        sched.levels[level].queue[sched.levels[level].rear++] = i;
      }
    }
    else
    {
      completed++;
    }
  }

  return 0;
}