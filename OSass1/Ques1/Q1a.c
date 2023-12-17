#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int status;

    printf("A) Parent (P) is having ID %d\n", getpid());

    pid = vfork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("C) Child is having ID %d\n", getpid());

        printf("D) My Parent ID is %d\n", getppid());

        exit(0); // Child process exits
    } else {
        // Parent process
        wait(&status); // Wait for child process to complete
        printf("B) ID of P's Child is %d\n", pid);

        }
        printf("\n");

    return 0;
}
