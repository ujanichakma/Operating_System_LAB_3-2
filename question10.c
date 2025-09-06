#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main() {
    mkfifo("myfifo", 0666);
    pid_t pid = fork();

    if (pid == 0) {
        // Child reads from named pipe
        char buffer[100];
        int fd = open("myfifo", O_RDONLY);
        read(fd, buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd);
    } else {
        // Parent writes to named pipe
        int fd = open("myfifo", O_WRONLY);
        char msg[] = "Hello from parent to child!";
        write(fd, msg, strlen(msg)+1);
        close(fd);
    }

    return 0;
}

