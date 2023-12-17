#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

void create_directory(const char *dir_name, int remove_existing, int verbose) {
    struct stat st;
    int dir_exists = stat(dir_name, &st) == 0;

    if (dir_exists && remove_existing) {
        if (verbose) {
            printf("Removing existing directory '%s'\n", dir_name);
        }
        if (rmdir(dir_name) != 0) {
            perror("Error removing directory");
            exit(1);
        }
        dir_exists = 0;
    }

    if (dir_exists) {
        fprintf(stderr, "Directory '%s' already exists.\n", dir_name);
        exit(1);
    }

    if (verbose) {
        printf("Creating directory '%s'\n", dir_name);
    }
    if (mkdir(dir_name, 0755) != 0) {
        perror("Error creating directory");
        exit(1);
    }

    if (verbose) {
        printf("Changing directory to '%s'\n", dir_name);
    }
    if (chdir(dir_name) != 0) {
        perror("Error changing directory");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    int remove_existing = 0;
    int verbose = 0;
    char *dir_name = NULL;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            remove_existing = 1;
        } else if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        } else {
            dir_name = argv[i];
        }
    }

    if (dir_name == NULL) {
        fprintf(stderr, "Error: Directory name not provided.\n");
        return 1;
    }

    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Fork error");
        return 1;
    } else if (child_pid == 0) { // Child process
        create_directory(dir_name, remove_existing, verbose);
        exit(0);  // Child process should exit after completing its task
    } else { // Parent process
        wait(NULL);
        if (verbose) {
            printf("Parent process done.\n");
        }
    }

    return 0;
}
