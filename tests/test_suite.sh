#!/bin/bash

echo "Running CMSC 125 Lab 2 Test Suite"
echo "----------------------------------"

echo "Test 1: FCFS"
./cpu_scheduling.exe tests/workload1.txt fcfs

echo ""
echo "Test 2: SJF"
./cpu_scheduling.exe tests/workload1.txt sjf

echo ""
echo "Test 3: STCF"
./cpu_scheduling.exe tests/workload1.txt stcf

echo ""
echo "Test 4: Round Robin (q=2)"
./cpu_scheduling.exe tests/workload1.txt rr 30

echo ""
echo "Test 5: MLFQ"
./cpu_scheduling.exe tests/workload1.txt mlfq

echo ""
echo "All tests executed."

