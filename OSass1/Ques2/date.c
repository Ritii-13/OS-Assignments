#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>

void displayTime(const char *filename, const char *timeString) {
    struct stat fileStat;

    if (stat(filename, &fileStat) != 0) {
        perror("Error getting file information");
        return;
    }

    time_t modifiedTime = fileStat.st_mtime;

    if (strcmp(timeString, "yesterday") == 0) {
        modifiedTime -= 24 * 60 * 60; // Subtract 24 hours (in seconds)
    } else {
        struct tm timeInfo;
        if (strptime(timeString, "%Y-%m-%d %H:%M:%S", &timeInfo) == NULL) {
            perror("Error parsing time string");
            return;
        }
        modifiedTime = mktime(&timeInfo);
    }

    char timeBuffer[50];
    strftime(timeBuffer, sizeof(timeBuffer), "%a %b %d %I : %M : %S %p IST %Y", localtime(&modifiedTime));
    printf("Previous date of modified time of %s: %s\n", filename, timeBuffer);
}

void displayyesterdaytime(const char *filename) {
    struct stat fileStat;

    if (stat(filename, &fileStat) != 0) {
        perror("Error getting file information");
        return;
    }

    time_t modifiedTime = fileStat.st_mtime - 24 * 60 * 60;

    char timeBuffer[50];
    strftime(timeBuffer, sizeof(timeBuffer), "%a %b %d %I : %M : %S %p IST %Y", localtime(&modifiedTime));
    printf("Previous date of modified time of %s: %s\n", filename, timeBuffer);
}

void displayRFC5322Time(const char *filename) {
    struct stat fileStat;

    if (stat(filename, &fileStat) != 0) {
        perror("Error getting file information");
        return;
    }

    time_t modifiedTime = fileStat.st_mtime;

    struct tm *timeInfo = localtime(&modifiedTime);

    char timeBuffer[50];
    strftime(timeBuffer, sizeof(timeBuffer), "%a, %d %b %Y %H:%M:%S %z", timeInfo);
    printf("Last modified time of %s (RFC 5322 format): %s\n", filename, timeBuffer);
}

int main(int argc, char *argv[]) {
    int displayTimeString = 0;
    int displayRFC5322 = 0;
    int displayyesterday = 0;
    char *timeString = NULL;

    int opt;
    while ((opt = getopt(argc, argv, "dR")) != -1) {
        switch (opt) {
            case 'd':
                if (optind < argc) {
                    timeString = argv[optind++];
                    displayTimeString = 1;
                } else {
                    fprintf(stderr, "Usage: date [-d 'time_string' | -R] [file_name]\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'R':
                displayRFC5322 = 1;
                break;
            default:
                fprintf(stderr, "Usage: date [-d 'time_string' | -R] [file_name]\n");
                exit(EXIT_FAILURE);
        }
    }

    if (argc - optind != 1) {
        fprintf(stderr, "Usage: date [-d 'time_string' | -R] file_name\n");
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[optind];

    if (displayTimeString || displayRFC5322) {
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) {
            if (displayTimeString) {
                if (argc - optind != 2) {
                    fprintf(stderr, "Usage: date -d 'time_string' file_name\n");
                    exit(EXIT_FAILURE);
                }
                const char *timeString = argv[optind + 1];
                displayTime(filename, timeString);
            } else if (displayRFC5322) {
                displayRFC5322Time(filename);
            }
            else if (displayyesterday) {
                displayyesterdaytime(filename);
            }

            // Replace the child process with "ls -l"
            execlp("ls", "ls", "-l", NULL);

            perror("execlp"); // If execlp fails
            exit(EXIT_FAILURE);
        } else {
            int status;
            wait(&status); // Wait for the child process to finish
            if (WIFEXITED(status)) {
                printf("Child process exited with status %d\n", WEXITSTATUS(status));
            }
        }
    } else {
        struct stat fileStat;
        if (stat(filename, &fileStat) != 0) {
            perror("Error getting file information");
            exit(EXIT_FAILURE);
        }

        char timeBuffer[50];
        strftime(timeBuffer, sizeof(timeBuffer), "%a %b %d %I:%M:%S %p IST %Y", localtime(&fileStat.st_mtime));
        printf("Last modified time of %s: %s\n", filename, timeBuffer);
    }

    return EXIT_SUCCESS;
}
