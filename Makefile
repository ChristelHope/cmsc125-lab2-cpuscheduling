CC = gcc																
CFLAGS = -Wall -Wextra -std=c99 -Iinclude										
SRC = src/main.c src/parser.c src/scheduler.c src/metrics.c src/gantt.c 
OUT = cpu_scheduling

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) 									

clean:
	rm -f $(OUT) 													