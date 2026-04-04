#include <stdio.h>
#include "process.h"
#include "gantt.h"
#include "gantt_context.h"

void print_gantt_chart(GanttContext *ctx, Process *processes, int n)
{
    printf("\nGantt Chart:\n");

    if (ctx->length == 0)
    {
        printf("No timeline data.\n");
        return;
    }

    // print process blocks (compressed)
    printf("|");

    int prev = -1;

    for (int i = 0; i < ctx->length; i++)
    {
        if (ctx->timeline[i] < 0 || ctx->timeline[i] >= n)
            continue;

        if (ctx->timeline[i] != prev)
        {
            printf(" %s |", processes[ctx->timeline[i]].pid);
            prev = ctx->timeline[i];
        }
    }

    printf("\n");

    // print time markers
    int last = -1;

    for (int i = 0; i < ctx->length; i++)
    {
        if (ctx->timeline[i] < 0 || ctx->timeline[i] >= n)
            continue;

        if (ctx->timeline[i] != last)
        {
            if (last == -1)   
                printf("0");
            else
                printf("%4d", i);

            last = ctx->timeline[i];
        }
    }

    printf("%4d\n\n", ctx->length);
}