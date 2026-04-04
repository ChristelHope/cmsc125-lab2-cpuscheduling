CC = gcc																
CFLAGS = -Wall -Wextra -std=c99 -g -Iinclude										
SRC = src/main.c src/parser.c src/scheduler.c src/metrics.c src/gantt.c src/fcfs.c src/sjf.c src/stcf.c src/rr.c src/mlfq.c
OUT = cpu_scheduling

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) 									

clean:
	rm -f $(OUT) 													