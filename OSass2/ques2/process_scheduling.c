#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <time.h>

int main() {
    pid_t pid1, pid2, pid3;
    struct timespec start_time, process_start, process_end;
    unsigned long long int elapsed_time1 = 0, elapsed_time2 = 0, elapsed_time3 = 0;

    // Get the start time
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    // Create Process 3
    pid3 = fork();
    if (pid3 == 0) {
        // Child process 3
        clock_gettime(CLOCK_MONOTONIC, &process_start); // Record start time for process 3
        execl("./counting_program_3", "./counting_program_3", "SCHED_FIFO", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    } else if (pid3 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    waitpid(pid3, NULL, 0);
    clock_gettime(CLOCK_MONOTONIC, &process_end); // Record end time for process 3
    elapsed_time3 = (process_end.tv_sec - process_start.tv_sec) * 1000 +
                   (process_end.tv_nsec - process_start.tv_nsec) / 1000000;


    // Create Process 1
    pid1 = fork();
    if (pid1 == 0) {
        // Child process 1
        if (nice(0) == -1) {
            perror("nice");
            exit(EXIT_FAILURE);
        }
        clock_gettime(CLOCK_MONOTONIC, &process_start); // Record start time for process 1
        execl("./counting_program_1", "./counting_program_1", "SCHED_OTHER", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    } else if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    waitpid(pid1, NULL, 0);
    clock_gettime(CLOCK_MONOTONIC, &process_end); // Record end time for process 1
    elapsed_time1 = (process_end.tv_sec - process_start.tv_sec) * 1000 +
                   (process_end.tv_nsec - process_start.tv_nsec) / 1000000;

    // Create Process 2
    pid2 = fork();
    if (pid2 == 0) {
        // Child process 2
        clock_gettime(CLOCK_MONOTONIC, &process_start); // Record start time for process 2
        execl("./counting_program_2", "./counting_program_2", "SCHED_RR", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    } else if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    waitpid(pid2, NULL, 0);
    clock_gettime(CLOCK_MONOTONIC, &process_end); // Record end time for process 2
    elapsed_time2 = (process_end.tv_sec - process_start.tv_sec) * 1000 +
                   (process_end.tv_nsec - process_start.tv_nsec) / 1000000;

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
