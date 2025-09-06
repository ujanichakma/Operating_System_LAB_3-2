#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        // Parent process: sleep but does not wait
        printf("Parent (PID: %d) sleeping... (child will become zombie)\n", getpid());
        sleep(10);
    } else if (pid == 0) {
        // Child process exits immediately
        printf("Child (PID: %d) exiting...\n", getpid());
        exit(0);
    } else {
        printf("Fork failed.\n");
    }

    return 0;
}

