#include <stdio.h>
#include "parser.h"

#define MAX_PROCESSES 100

int main() {

    Process processes[MAX_PROCESSES];

    int n = load_processes("tests/workload1.txt", processes, MAX_PROCESSES);

    printf("Loaded %d processes\n", n);

    for (int i = 0; i < n; i++) {
        printf("%s %d %d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time);
    }

    return 0;
}
