# MLFQ Design Justification

This project implements a Multi-Level Feedback Queue (MLFQ) scheduler with three priority levels. The design choices are based on balancing responsiveness for short jobs and fairness for long-running processes.

## Number of Queues

The scheduler uses **3 queues**:

- **Q0 (highest priority)**
- **Q1 (medium priority)**
- **Q2 (lowest priority)**

This structure is sufficient to:
- Quickly respond to short or interactive jobs (Q0)
- Gradually demote longer jobs (Q1 → Q2)
- Avoid unnecessary complexity from too many queues

Three levels provide a clear distinction between short, medium, and long processes without overcomplicating scheduling logic.

---

## Time Quantums

Each queue uses a different time quantum:

- **Q0: 10**
- **Q1: 20**
- **Q2: FCFS (no fixed quantum)**

### Rationale:
- A **small quantum (10)** in Q0 allows fast context switching, improving responsiveness.
- A **larger quantum (20)** in Q1 reduces overhead while still allowing preemption.
- Q2 runs in **FCFS mode**, minimizing context switching for long-running processes.

This progression ensures:
- Short jobs finish early
- Longer jobs are handled efficiently with fewer interruptions

---

## Allotment Policy

Each queue has a time allotment:

- **Q0: 50**
- **Q1: 100**
- **Q2: unlimited**

A process is only demoted when its accumulated `time_in_queue` reaches the allotment.

### Rationale:
- Prevents premature demotion after a single quantum
- Allows processes to fully utilize a queue before being downgraded
- Better reflects actual CPU usage rather than just number of time slices

---

## Priority Boost

A **priority boost occurs every 100 time units**, moving all processes back to Q0.

### Rationale:
- Prevents starvation of low-priority processes
- Ensures fairness over time
- Allows long processes to regain higher priority periodically

Without boosting, processes in lower queues may never get CPU time if higher-priority queues remain busy.

---

## Overall Behavior

This MLFQ design achieves:

- **Responsiveness** → short jobs handled quickly in Q0
- **Fairness** → long jobs are not starved (via boosting)
- **Efficiency** → reduced context switching in lower queues
- **Adaptability** → processes dynamically change priority based on CPU usage

---

## Summary

The chosen parameters (3 queues, quantums 10/20, boost at 100, and allotments 50/100) provide a balanced scheduling strategy that follows standard MLFQ principles while remaining simple and efficient to implement.