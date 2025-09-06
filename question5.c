#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <number_of_children> <child_name_1> <child_name_2> ...\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (argc != n + 2) {
        printf("Error: Expected %d child names, but got %d.\n", n, argc - 2);
        return 1;
    }

    printf("Main process started: parent_process (PID: %d)\n", getpid());

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            printf("  --> %s created (PID: %d, Parent PID: %d)\n", argv[i + 2], getpid(), getppid());
            return 0;  // Child exits to prevent creating grandchildren
        }
    }

    // Parent waits for all children to finish
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("parent_process (PID: %d) finished.\n", getpid());
    return 0;
}

