# OS Assignments

## Overview
This repository contains assignments completed throughout the Operating System (OS) course. Each assignment addresses different aspects of OS concepts, including process management, memory management, file systems, device management, and concurrent programming using pthreads and dispatch semaphores.

## Assignment 1: Process Management and System Calls

### Part 1: Fork and Vfork System Calls
- Description: The C code demonstrates the usage of `vfork()` system call to create child processes and illustrates the parent-child relationship and execution order.
- Part 2: Process Creation and Factorial Computation
- Description: The C code calculates factorial and Fibonacci series using `vfork()` system call for process creation and synchronization.

### Part 2: Custom System Call Module
- Description: This assignment involves creating a custom system call module for the Linux kernel to count the number of running processes.
- Features: The module logs the count of running processes and provides a Makefile for easy compilation, loading, unloading, and kernel log viewing.

## Assignment 2: Linux Scheduling Policy Benchmarking

### Overview
- Description: This project benchmarks Linux scheduling policies by comparing execution times of processes under different policies.
- Processes: Three processes count from 1 to 2^32 under different scheduling policies: SCHED_OTHER, SCHED_RR, and SCHED_FIFO.
- Measurement: Execution times are measured using precise timing methods, and histograms are generated to visualize policy effects.

## Assignment 3: Memory Management System

### Overview
- Description: This assignment involves designing and implementing a memory management system using C.
- Features: The system manages memory allocation, deallocation, and fragmentation to optimize memory usage.

## Assignment 4: Concurrent Programming with pthreads and Semaphores

### Overview
- Description: This assignment explores concurrent programming using pthreads and dispatch semaphores in C.
- Examples: 
  - Dining Philosophers: Demonstrates mutex locks to avoid deadlock in a dining philosophers scenario.
  - Amusement Park Simulation: Simulates passenger-car synchronization using dispatch semaphores.
  - Bridge Crossing Problem: Uses semaphores to coordinate car crossings on a bridge.

## How to Use
1. Navigate to each assignment folder.
2. Follow the instructions in the respective README files to compile and run the code.
3. Review the code and experiment with different parameters to explore OS concepts further.
