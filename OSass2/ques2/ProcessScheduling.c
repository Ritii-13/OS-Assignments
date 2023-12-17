#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <time.h>

int set_cpu_affinity(pid_t pid, int cpu_id) {
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpu_id, &mask);

    if (sched_setaffinity(pid, sizeof(mask), &mask) == -1) {
        perror("sched_setaffinity");
        return -1;
    }

    return 0;
}

unsigned long long int calculate_elapsed_time(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
}

int main() {
    pid_t pid1, pid2, pid3;
    struct timespec start_time, end_time;
    unsigned long long int elapsed_time1 = 0, elapsed_time2 = 0, elapsed_time3 = 0;

    // Get the start time
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    // Create Process 1 on CPU core 0
    pid1 = fork();
    if (pid1 == 0) {
        // Child process 1
        if (nice(0) == -1) {
            perror("nice");
            exit(EXIT_FAILURE);
        }
        set_cpu_affinity(getpid(), 0); // Set CPU affinity for process 1
        execl("./counting_program_1", "./counting_program_1", "SCHED_OTHER", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    } else if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Create Process 3 on CPU core 1
    pid3 = fork();
    if (pid3 == 0) {
        // Child process 3
        set_cpu_affinity(getpid(), 1); // Set CPU affinity for process 3
        execl("./counting_program_3", "./counting_program_3", "SCHED_FIFO", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    } else if (pid3 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Create Process 2 on CPU core 2
    pid2 = fork();
    if (pid2 == 0) {
        // Child process 2
        set_cpu_affinity(getpid(), 2); // Set CPU affinity for process 2
        execl("./counting_program_2", "./counting_program_2", "SCHED_RR", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    } else if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Wait for all child processes to finish and calculate elapsed times
    waitpid(pid1, NULL, 0);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    elapsed_time1 = calculate_elapsed_time(start_time, end_time);

    waitpid(pid2, NULL, 0);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    elapsed_time2 = calculate_elapsed_time(start_time, end_time);

    waitpid(pid3, NULL, 0);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    elapsed_time3 = calculate_elapsed_time(start_time, end_time);

    // Print the total time taken by each scheduling policy
    printf("Total time for process 1: %llu ms\n", elapsed_time1);
    printf("Total time for process 2: %llu ms\n", elapsed_time2);
    printf("Total time for process 3: %llu ms\n", elapsed_time3);

    // Open a file for writing
    FILE *file = fopen("process_times.txt", "w");
    if (file == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    // Write elapsed times to the file
    fprintf(file, "Total time for process 1: %llu ms\n", elapsed_time1);
    fprintf(file, "Total time for process 2: %llu ms\n", elapsed_time2);
    fprintf(file, "Total time for process 3: %llu ms\n", elapsed_time3);

    // Close the file
    fclose(file);

    return 0;
}
