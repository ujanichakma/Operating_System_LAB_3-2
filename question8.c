#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    char msg[] = "Hello from parent!";
    char buffer[100];

    pipe(fd);
    pid_t pid = fork();

    if (pid == 0) {
        // Child reads from pipe
        close(fd[1]); // close write end
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
    } else {
        // Parent writes to pipe
        close(fd[0]); // close read end
        write(fd[1], msg, strlen(msg)+1);
    }

    return 0;
}

