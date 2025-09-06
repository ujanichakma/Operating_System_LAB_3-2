#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    printf("Main process started: parent_process (PID: %d)\n", getpid());

    for (int i = 1; i <= 3; i++) {
        pid = fork();

        if (pid == 0) {
            // Child process
            if (i == 1) {
                printf("  --> child_1 created (PID: %d, Parent PID: %d)\n", getpid(), getppid());
            } else if (i == 2) {
                printf("  --> child_2 created (PID: %d, Parent PID: %d)\n", getpid(), getppid());
            } else if (i == 3) {
                printf("  --> child_3 created (PID: %d, Parent PID: %d)\n", getpid(), getppid());
            }
            return 0;  // Exit child so no grandchildren are created
        }
    }

    // Parent waits for all child processes
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("parent_process (PID: %d) finished.\n", getpid());
    return 0;
}

