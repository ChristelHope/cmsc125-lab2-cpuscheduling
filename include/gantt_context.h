#ifndef GANTT_CONTEXT_H
#define GANTT_CONTEXT_H

typedef struct
{
  int *timeline;
  int length;
  int capacity;
} GanttContext;

#endif