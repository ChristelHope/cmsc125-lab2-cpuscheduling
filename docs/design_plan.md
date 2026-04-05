# CPU Scheduling Simulator Design Plan

## Overview

The system is a CPU scheduling simulator written in C. It reads a workload file containing processes and simulates how different scheduling algorithms execute them over time.

The goal is to analyze scheduling performance using metrics such as waiting time, turnaround time, and response time.

---

## Components

The system is divided into the following modules:

- **parser.c** – reads and validates workload input
- **scheduler.c / algorithm files** – executes scheduling algorithms
- **metrics.c** – computes performance metrics
- **gantt.c** – prints execution timeline
- **main.c** – handles input and program flow

---

## Data Structures

### Process

Each process contains:

- pid
- arrival_time
- burst_time
- remaining_time
- start_time
- finish_time
- waiting_time
- turnaround_time
- response_time
- time_in_queue (for MLFQ)

---

## Scheduling Algorithms

The simulator supports:

- FCFS
- SJF
- STCF
- Round Robin
- MLFQ

Each algorithm is implemented as a separate function.

---

## Execution Flow

1. Load processes from input file
2. Validate input
3. Select scheduling algorithm
4. Simulate execution over time
5. Record timeline for Gantt chart
6. Compute metrics
7. Display results

---

## Design Goals

- Modular structure (separate files per component)
- Clear separation of concerns
- Support both preemptive and non-preemptive scheduling
- Accurate simulation of CPU behavior