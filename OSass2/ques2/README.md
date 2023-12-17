# Linux Scheduling Policy Benchmarking

## Program Logic

The objective of this project is to benchmark Linux scheduling policies by comparing how different policies affect the execution times of three processes. Each process counts from 1 to 2^32, and the parent process records the execution times.

### Process Logic

1. **Process 1 (SCHED_OTHER)**
   - This process is created using the `fork()` system call.
   - It sets its scheduling policy to SCHED_OTHER with standard priority (nice: 0) using `nice(0)`.
   - It records the start time and executes `counting_program_1` using `execl()`.
   - The parent process waits for it to complete, records the end time, and calculates the elapsed time.
   - The total time for process 1 is recorded and written to `process_times.txt`.

2. **Process 2 (SCHED_RR)**
   - Similar to Process 1, but it executes `counting_program_2`.

3. **Process 3 (SCHED_FIFO)**
   - Similar to Process 1, but it executes `counting_program_3`.

### Measurement Logic

- Execution times are measured using `clock_gettime(CLOCK_MONOTONIC)` to ensure precise timing.
- Elapsed time for each process is calculated as the difference between the start and end times, and it is recorded.
- Results are written to a text file named `process_times.txt` which is later used to plot histograms to effectively display the measured times for each process.

## Outcomes of Tests/Measurements

- Each process counts from 1 to 2^32, and the time taken for this operation is recorded.
- The execution times for each process are recorded and written to  text file.
- To visualize the results, histograms are generated using Python, showing how different scheduling policies affect completion times.
- The histograms demonstrate the impact of different scheduling policies, allowing for a clear comparison.
- The general order observed is **SCHED_FIFO >> SCHED_OTHER >> SCHED_RR**

In summary, this benchmarking project provides insights into the behavior of Linux scheduling policies on process execution times. It allows us to visualize how scheduling policies prioritize processes in a real-world scenario, facilitating informed decisions on process scheduling strategies.
