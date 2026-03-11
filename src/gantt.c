#include <stdio.h>
#include "process.h"
#include "gantt.h"

void print_gantt_chart(Process *processes, int n) {
    
    printf("\nGantt Chart:\n");

    for (int i = 0; i < n - 1; i++) { // sort by start time
        for (int j = i + 1; j < n; j++) {

            if (processes[j].start_time < processes[i].start_time) {

                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("| %s ", processes[i].pid);
    }

    printf("|\n");

    for (int i = 0; i < n; i++) {
        printf("%d   ", processes[i].start_time);
    }

    printf("%d\n\n", processes[n-1].finish_time);
}