#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void calculate_factorial(int number) {
    FILE *fp = fopen("factorial_result.txt", "w");
    if (fp == NULL) {
        perror("Failed to open factorial result file");
        exit(EXIT_FAILURE);
    }
    unsigned long long factorial = 1;
    for(int i = 1; i <= number; ++i) {
        factorial *= i;
    }
    fprintf(fp, "Factorial of %d = %llu\n", number, factorial);
    fclose(fp);
}

void list_processes() {
    FILE *fp = fopen("process_list.txt", "w");
    if (fp == NULL) {
        perror("Failed to open process list file");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "List of processes\n");
    system("ps -ef > process_list.txt");
    fclose(fp);
}

void calculate_average(int *numbers, int count) {
    FILE *fp = fopen("average_result.txt", "w");
    if (fp == NULL) {
        perror("Failed to open average result file");
        exit(EXIT_FAILURE);
    }
    int sum = 0;
    for(int i = 0; i < count; ++i) {
        sum += numbers[i];
    }
    double average = (double)sum / count;
    fprintf(fp, "Average = %f\n", average);
    fclose(fp);
}


void readFile(int* fact, int** num, int* count) {
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Unable to open the file.");
        exit(1);
    }

    // Read factorial
    fscanf(file, "%d", fact);

    
    *num = (int*)malloc(100 * sizeof(int));
    if (*num == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        exit(2);
    }

    // Read numbers
    while (!feof(file)) {
        fscanf(file, "%d", &((*num)[*count]));
        *count += 1;
    }

    fclose(file);
}

int main() {
    pid_t pids[3];
    int status;


    // Read input from file
    int factorialNumber;
    int count = 0;
    int *numbers = NULL;
    readFile(&factorialNumber, &numbers, &count);

    // 1.Calculate factorial
    if ((pids[0] = fork()) == 0) {
        calculate_factorial(factorialNumber);
        exit(EXIT_SUCCESS);
    } else if (pids[0] < 0) {
        perror("fork factorial failed");
        exit(EXIT_FAILURE);
    }

    // 2.List processes
    if ((pids[1] = fork()) == 0) {
        list_processes();
        exit(EXIT_SUCCESS);
    } else if (pids[1] < 0) {
        perror("fork process list failed");
        exit(EXIT_FAILURE);
    }

    // 3.Calculate average
    if ((pids[2] = fork()) == 0) {
        calculate_average(numbers, count);
        exit(EXIT_SUCCESS);
    } else if (pids[2] < 0) {
        perror("fork average failed");
        exit(EXIT_FAILURE);
    }

    // Wait for all child processes to finish
    for (int i = 0; i < 3; ++i) {
        waitpid(pids[i], &status, 0);
    }

    // Example of consolidating output: Print a message to indicate completion
    printf("All tasks completed. Results are in their respective files.\n");

    return 0;
}
