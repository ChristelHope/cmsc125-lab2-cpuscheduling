#include <stdio.h>
#include "process.h"
#include "gantt.h"

void print_gantt_chart(Process *processes, int n) {

    printf("\nGantt Chart:\n");

    /* create a temporary copy so we don't modify the original array */
    Process temp[100];

    for (int i = 0; i < n; i++) {
        temp[i] = processes[i];
    }

    /* sort the copy by start_time */
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {

            if (temp[j].start_time < temp[i].start_time) {

                Process swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
        }
    }

    /* print process blocks */
    for (int i = 0; i < n; i++) {
        printf("| %s ", temp[i].pid);
    }

    printf("|\n");

    /* print start times */
    for (int i = 0; i < n; i++) {
        printf("%-5d", temp[i].start_time);
    }

    printf("%d\n\n", temp[n-1].finish_time);
}