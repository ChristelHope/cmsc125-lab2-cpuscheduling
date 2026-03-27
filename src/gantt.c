#include <stdio.h>
#include "process.h"
#include "gantt.h"

extern int timeline[1000];
extern int timeline_length;

void print_gantt_chart(Process *processes, int n)
{

    printf("\nGantt Chart:\n");

    if (timeline_length == 0)
    {
        printf("No timeline data.\n");
        return;
    }

    // print process blocks (compressed)
    printf("|");

    int prev = -1;

    for (int i = 0; i < timeline_length && i < 1000; i++)
    {

        if (timeline[i] < 0 || timeline[i] >= n)
            continue;

        if (timeline[i] != prev)
        {
            printf(" %s |", processes[timeline[i]].pid);
            prev = timeline[i];
        }
    }

    printf("\n");

    // print time markers
    int last = -1;

    for (int i = 0; i < timeline_length && i < 1000; i++)
    {

        if (timeline[i] < 0 || timeline[i] >= n)
            continue;

        if (timeline[i] != last)
        {
            if (last == -1)
                printf("0");
            else
                printf("%4d", i);

            last = timeline[i];
        }
    }

    printf("%4d\n\n", (timeline_length < 1000 ? timeline_length : 1000));
}