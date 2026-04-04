#include "rr.h"
#include "scheduler.h"
#include "gantt_context.h"

extern int timeline[];
extern int timeline_length;

#define NEXT(x) (((x) + 1) % MAX_PROCESSES)

int schedule_rr(Process *processes, int n, int quantum, GanttContext *ctx)
{

  int current_time = 0;
  int completed = 0;

  int queue[MAX_PROCESSES];
  int front = 0, rear = 0;

  int added[MAX_PROCESSES] = {0};

// circular queue helper
#define NEXT(x) (((x) + 1) % MAX_PROCESSES)

  while (completed < n)
  {

    // add newly arrived processes
    for (int j = 0; j < n; j++)
    {
      if (!added[j] && processes[j].arrival_time <= current_time)
      {
        if (NEXT(rear) != front)
        {
          queue[rear] = j;
          rear = NEXT(rear);
        }
        added[j] = 1;
      }
    }

    if (front == rear)
    {
      current_time++;
      continue;
    }

    int i = queue[front];
    front = NEXT(front);

    if (processes[i].remaining_time > 0)
    {

      int run_time =
          processes[i].remaining_time < quantum
              ? processes[i].remaining_time
              : quantum;

      // record timeline + simulate per time unit
      for (int t = 0; t < run_time; t++)
      {
        if (ctx->length < MAX_TIMELINE)
          ctx->timeline[ctx->length++] = i;

        current_time++;

        // check arrivals DURING execution
        for (int j = 0; j < n; j++)
        {
          if (!added[j] && processes[j].arrival_time <= current_time)
          {
            if (NEXT(rear) != front)
            {
              queue[rear] = j;
              rear = NEXT(rear);
            }
            added[j] = 1;
          }
        }
      }

      if (processes[i].start_time == -1)
        processes[i].start_time = current_time - run_time;

      processes[i].remaining_time -= run_time;

      if (processes[i].remaining_time > 0)
      {
        // put back in queue (fair rotation)
        if (NEXT(rear) != front)
        {
          queue[rear] = i;
          rear = NEXT(rear);
        }
      }
      else
      {
        processes[i].finish_time = current_time;
        completed++;
      }
    }
  }

  return 0;
}