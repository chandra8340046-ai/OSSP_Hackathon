
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int value = 100;
    pid_t pid;

    // Display the project title
    printf("\n");
    printf("========================================\n");
    printf("  COPY-ON-WRITE MEMORY DEMONSTRATOR\n");
    printf("========================================\n\n");

    printf("Initial value before fork() = %d\n", value);
    printf("Creating child process...\n\n");

    // Create a child process
    pid = fork();

    if (pid < 0) {
        perror("Error creating child process");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        // Child process
        printf("--- CHILD PROCESS ---\n");
        printf("Process ID: %ld\n", (long)getpid());
        printf("Value before modification: %d\n", value);

        // Modify the child's private value
        value = 200;

        printf("Value after modification:  %d\n", value);
        printf("Child process completed.\n\n");

        _exit(EXIT_SUCCESS);
    } else {
        // Parent process
        int status;

        // Wait for child to finish
        if (waitpid(pid, &status, 0) == -1) {
            perror("Error waiting for child");
            return EXIT_FAILURE;
        }

        printf("--- PARENT PROCESS ---\n");
        printf("Process ID: %ld\n", (long)getpid());
        printf("Value after child modification: %d\n", value);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            printf("\n--- RESULT ---\n");
            printf("Parent value remains: %d\n", value);
            printf("Child changed its value to: 200\n");
            printf("Parent and child values are isolated.\n");
            printf("Copy-on-Write demonstration completed!\n");
        } else {
            printf("Child process did not complete successfully.\n");
            return EXIT_FAILURE;
        }
    }

    printf("\n========================================\n");
    return EXIT_SUCCESS;
}
