# CMSC 125 Lab 2

## CPU Scheduling – Design Notes

**Members**

* Ong, Christel Hope
* Yap, Mae Maricar

---

# I. Problem Analysis

The objective of this laboratory activity is to implement a **CPU Scheduling in C** that models how operating systems determine which process should execute on the CPU.

The simulator will read a workload of processes defined by:

* **PID** – Process identifier
* **Arrival Time** – Time when a process enters the ready queue
* **Burst Time** – Total CPU time required

Using this workload, the simulator will execute multiple scheduling algorithms and measure their performance.

The simulator must support the following capabilities:

* Implementation of classic scheduling algorithms
* Discrete-time simulation of process execution
* Calculation of scheduling metrics
* ASCII Gantt chart generation
* Comparative analysis between scheduling algorithms

### Main Challenges

Some challenges expected during implementation include:

* Correct implementation of **preemption** for STCF and Round Robin
* Handling **process arrivals while another process is running**
* Designing a **Multi-Level Feedback Queue (MLFQ)** scheduler without relying on burst time
* Preventing **starvation while maintaining responsiveness**

---

# II. Features

The simulator will support the following functionalities.

---

## Scheduling Algorithms

The simulator will implement the following scheduling policies:

### FCFS (First Come First Serve)

* Non-preemptive scheduling
* Processes are executed in order of arrival
* Once a process starts execution, it runs until completion

### SJF (Shortest Job First)

* Non-preemptive scheduling
* Selects the process with the **shortest burst time** among ready processes
* Optimizes average turnaround time in non-preemptive scenarios

### STCF (Shortest Time to Completion First)

* Preemptive version of SJF
* Always runs the process with the **shortest remaining execution time**
* Preempts the current process if a newly arriving process has a shorter remaining time

### Round Robin (RR)

* Preemptive scheduling
* Each process receives a **fixed time quantum**
* After the quantum expires, the process moves to the end of the ready queue
* Quantum is configurable (default example: 30)

### Multi-Level Feedback Queue (MLFQ)

* Multiple priority queues
* Processes move between queues depending on CPU usage behavior
* Implements **priority boosting** to avoid starvation
* Scheduling decisions **must not use burst time**

---

## Workload Input

The simulator will support two types of input.

### Input File

Example format:

```
# PID ArrivalTime BurstTime
A 0 240
B 10 100
C 20 150
```

Lines beginning with `#` are treated as comments.

### Command-Line Arguments

Example usage:

```
./schedsim --algorithm=FCFS --processes="A:0:240,B:10:100"
```

This allows workloads to be passed directly through the terminal.

---

## Output

The simulator will generate the following outputs.

### 1. ASCII Gantt Chart

Displays process execution timeline.

Example:

```
Gantt Chart
[A][A][A][B][B][C]
Time: 0 10 20 30 40
```

---

### 2. Per-Process Metrics

For each process, the simulator will compute:

| Metric               | Description                           |
| -------------------- | ------------------------------------- |
| Finish Time (FT)     | Time when process completes           |
| Turnaround Time (TT) | FT − Arrival Time                     |
| Waiting Time (WT)    | Time spent waiting in the ready queue |
| Response Time (RT)   | Time from arrival to first execution  |

---

### 3. Average Metrics

The simulator will compute average values for:

* Average Turnaround Time
* Average Waiting Time
* Average Response Time

---

### 4. Comparison Mode

A comparison mode will allow all algorithms to run on the same workload and produce a table such as:

| Algorithm | Avg Turnaround | Avg Waiting | Avg Response |
| --------- | -------------- | ----------- | ------------ |
| FCFS      | ...            | ...         | ...          |
| SJF       | ...            | ...         | ...          |
| STCF      | ...            | ...         | ...          |
| RR        | ...            | ...         | ...          |
| MLFQ      | ...            | ...         | ...          |

---

# III. Solution Architecture

The simulator will be organized into multiple components to separate responsibilities.

---

## Process Data Structure

Each process will store information required for scheduling and metric computation.

Example structure:

```
Process
- pid
- arrival_time
- burst_time
- remaining_time
- start_time
- finish_time
- waiting_time
- turnaround_time
- response_time
- priority_queue (for MLFQ)
```

---

## Scheduler State

The scheduler will maintain global simulation data.

Example structure:

```
SchedulerState
- process_list
- ready_queue
- current_time
- current_process
- gantt_chart_data
```

This state will be updated continuously during the simulation.

---

## Scheduling Algorithms

Each scheduling policy will be implemented as a **separate function**.

Example:

```
schedule_fcfs()
schedule_sjf()
schedule_stcf()
schedule_rr()
schedule_mlfq()
```

This modular design allows easier testing and expansion.

---

## Simulation Engine

The simulator will run using **discrete time steps**.

At each time unit, the following steps will occur:

1. Check for new process arrivals
2. Add arriving processes to the ready queue
3. Update the currently running process
4. Handle process completion or quantum expiration
5. Select the next process according to the scheduling algorithm
6. Record the execution state for the Gantt chart

This loop continues until **all processes finish execution**.

---

# IV. MLFQ Design

The Multi-Level Feedback Queue scheduler will consist of multiple priority levels.

Example configuration:

| Queue                 | Quantum | Allotment |
| --------------------- | ------- | --------- |
| Q0 (Highest Priority) | 10      | 50        |
| Q1                    | 30      | 150       |
| Q2 (Lowest Priority)  | FCFS    | Unlimited |

### Behavior

* New processes enter **Q0**
* If a process consumes its allotment, it is **demoted to the next queue**
* Lower queues receive longer execution time
* A **priority boost** occurs after a fixed period to prevent starvation
* All processes are moved back to **Q0 during a boost**

Importantly, the MLFQ scheduler **must not use burst time to make scheduling decisions**. Instead, it observes process behavior during execution.

---

# V. Error Handling

The simulator will include error checking for invalid inputs and runtime issues.

Examples include:

* Invalid workload format
* Missing process fields
* Negative arrival or burst times
* Empty workload file
* Invalid command-line parameters

Errors will display descriptive messages and terminate the program with a non-zero exit code.

---

# VI. Estimated Implementation Timeline

## Week 1

* Write and submit design documentation
* Initialize repository structure
* Implement workload parser
* Implement FCFS algorithm

## Week 2

* Implement SJF
* Implement STCF
* Implement Round Robin
* Implement Gantt chart rendering
* Create initial automated test script

## Week 3

* Design MLFQ parameters
* Implement MLFQ scheduler
* Implement priority boost mechanism
* Test mixed workloads
* Implement comparison mode

## Week 4

* Refactor and clean code
* Test edge cases
* Check for memory leaks
* Finalize documentation
* Prepare for defense

---
