#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void printWordCount(const char *filename, int ignoreNewLine) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int wordCount = 0;
    char prevChar = ' ';
    char currChar;

    while ((currChar = fgetc(file)) != EOF) {
        if (ignoreNewLine && (currChar == '\n' || currChar == '\r')) {
            prevChar = ' ';
            continue;
        }

        if (currChar == ' ' || currChar == '\n' || currChar == '\t') {
            if (prevChar != ' ' && prevChar != '\n' && prevChar != '\t') {
                wordCount++;
            }
        }

        prevChar = currChar;
    }

    fclose(file);

    printf("%d\n", wordCount);
}

void compareWordCounts(const char *filename1, const char *filename2, int ignoreNewLine) {
    int wordCount1 = 0;
    int wordCount2 = 0;

    FILE *file1 = fopen(filename1, "r");
    FILE *file2 = fopen(filename2, "r");

    if (file1 == NULL || file2 == NULL) {
        perror("Error opening files");
        return;
    }

    char prevChar1 = ' ';
    char prevChar2 = ' ';
    char currChar1;
    char currChar2;

    while ((currChar1 = fgetc(file1)) != EOF && (currChar2 = fgetc(file2)) != EOF) {
        if (ignoreNewLine && (currChar1 == '\n' || currChar2 == '\n')) {
            prevChar1 = ' ';
            prevChar2 = ' ';
            continue;
        }

        if (currChar1 == ' ' || currChar1 == '\n' || currChar1 == '\t') {
            if (prevChar1 != ' ' && prevChar1 != '\n' && prevChar1 != '\t') {
                wordCount1++;
            }
        }

        if (currChar2 == ' ' || currChar2 == '\n' || currChar2 == '\t') {
            if (prevChar2 != ' ' && prevChar2 != '\n' && prevChar2 != '\t') {
                wordCount2++;
            }
        }

        prevChar1 = currChar1;
        prevChar2 = currChar2;
    }

    fclose(file1);
    fclose(file2);

    printf("Word count for %s: %d\n", filename1, wordCount1);
    printf("Word count for %s: %d\n", filename2, wordCount2);

    if (wordCount1 > wordCount2) {
        printf("wordcount difference: %d\n", wordCount1 - wordCount2);
    } else if (wordCount1 < wordCount2) {
        printf("wordcount difference: %d\n", wordCount2 - wordCount1);
    } else {
        printf("0\n");
    }
}

int main(int argc, char *argv[]) {
    int ignoreNewLine = 0;
    int diffMode = 0;

    int opt;
    while ((opt = getopt(argc, argv, "nd")) != -1) {
        switch (opt) {
            case 'n':
                ignoreNewLine = 1;
                break;
            case 'd':
                diffMode = 1;
                break;
            default:
                fprintf(stderr, "Usage: word [-n | -d] [file_name]\n");
                exit(EXIT_FAILURE);
        }
    }

    if (diffMode) {
        if (argc - optind != 2) {
            fprintf(stderr, "Usage: word -d file1 file2\n");
            exit(EXIT_FAILURE);
        }

        const char *filename1 = argv[optind];
        const char *filename2 = argv[optind + 1];

        compareWordCounts(filename1, filename2, ignoreNewLine);
    } else {
        if (argc - optind != 1) {
            fprintf(stderr, "Usage: word [-n] file_name\n");
            exit(EXIT_FAILURE);
        }

        const char *filename = argv[optind];

        printWordCount(filename, ignoreNewLine);
    }

    return EXIT_SUCCESS;
}
