#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int num_start = 1;
    int num_end = 5;
    int num_range = num_end - num_start + 1;

    int sum = 0;
    int product = 1;

    pid_t child_pid = fork();

    if (child_pid == -1) {
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (child_pid == 0) { // Child process
        for (int i = num_start; i <= num_end; ++i) {
            sum += i;
        }
        printf("Child process: Sum = %d\n", sum);
    } else { // Parent process
        for (int i = num_start; i <= num_end; ++i) {
            product *= i;
        }
        printf("Parent process: Product = %d\n", product);

        // Wait for the child process to finish
        wait(NULL);
    }

    return 0;
}