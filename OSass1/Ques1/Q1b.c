#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    pid_t pid;
    int status;

    pid = vfork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("\nFactorial of 4: %d\n", factorial(4));
        
        exit(0); // Child process exits
    } else {
        // Parent process
        wait(&status); // Wait for child process to complete

        printf("\nFibonacci Series up to 16:\n");
        for (int i = 0; i <= 16; ++i) {
            printf("%d ", fibonacci(i));
        }
        printf("\n");

    }

    return 0;
}
