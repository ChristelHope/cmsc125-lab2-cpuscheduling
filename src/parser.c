#include <stdio.h>
#include <string.h>
#include "process.h"
#include "parser.h"

int load_processes(const char *filename, Process processes[], int max_processes) {

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: Could not open workload file.\n");
        return -1;
    }

    // how many processes were loaded
    int count = 0;

    while (count < max_processes) {

        // buffer to hold one line from the file
        char line[128];

        // reads one line from the file
        if (fgets(line, sizeof(line), file) == NULL)
            break;

        // skip comments
        if (line[0] == '#')
            continue;

        // creates a temporary process object
        Process p;

        if (sscanf(line, "%s %d %d",
                   p.pid,
                   &p.arrival_time,
                   &p.burst_time) == 3) {

            p.remaining_time = p.burst_time;
            p.start_time = -1;
            p.finish_time = 0;

            p.waiting_time = 0;
            p.turnaround_time = 0;
            p.response_time = 0;

            // for MLFQ scheduling
            p.priority = 0;
            p.time_in_queue = 0;

            processes[count] = p;
            count++;
        }
    }

    fclose(file);

    return count;
}
