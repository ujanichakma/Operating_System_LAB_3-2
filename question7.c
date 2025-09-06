#include <stdio.h>
#include <unistd.h>

int global_var = 10;

int main() {
    int local_var = 20;

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        global_var += 5;
        local_var += 5;
        printf("Child Process:\n  Global = %d\n  Local = %d\n", global_var, local_var);
    } else {
        // Parent process
        sleep(1); // ensure child runs first
        printf("Parent Process:\n  Global = %d\n  Local = %d\n", global_var, local_var);
    }

    return 0;
}

