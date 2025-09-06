#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        // Parent process
        printf("Parent Process (PID: %d) exiting...\n", getpid());
        sleep(1); // Delay to allow child to become orphan
    } else if (pid == 0) {
        // Child process
        sleep(2); // Ensure parent has exited
        printf("Orphan Child (PID: %d, New Parent PID: %d)\n", getpid(), getppid());
    } else {
        printf("Fork failed.\n");
    }

    return 0;
}

