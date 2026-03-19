#include <stdio.h>
#include "process.h"
#include "gantt.h"

extern int timeline[1000];
extern int timeline_length;

void print_gantt_chart(Process *processes, int n) {

    (void)n; // suppress unused parameter warning

    printf("\nGantt Chart:\n");

    if (timeline_length == 0) {
        printf("No timeline data.\n");
        return;
    }

    // print process blocks (compressed)
    printf("|");
    for (int i = 0; i < timeline_length; i++) {
        if (i == 0 || timeline[i] != timeline[i - 1]) {
            printf(" %s |", processes[timeline[i]].pid);
        }
    }

    printf("\n");

    // print time markers
    printf("0");

    for (int i = 1; i < timeline_length; i++) {
        if (timeline[i] != timeline[i - 1]) {
            printf("%5d", i);
        }
    }

    printf("%5d\n\n", timeline_length);
}