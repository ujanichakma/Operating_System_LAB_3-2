#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int a = 10, b = 5;
    pid_t pid;

    printf("Parent Process (PID: %d)\n", getpid());

    for (int i = 0; i < 3; i++) {
        pid = fork();
        if (pid == 0) {
            // Child process
            printf("  Child %d (PID: %d, Parent PID: %d): ", i+1, getpid(), getppid());
            if (i == 0)
                printf("Addition: %d + %d = %d\n", a, b, a + b);
            else if (i == 1)
                printf("Subtraction: %d - %d = %d\n", a, b, a - b);
            else if (i == 2)
                printf("Multiplication: %d * %d = %d\n", a, b, a * b);
            return 0; // End child process
        }
    }

    // Parent waits for all 3 children
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("Parent Process (PID: %d) finished.\n", getpid());
    return 0;
}

