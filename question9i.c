#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {
    mkfifo("mypipe", 0666);
    int fd = open("mypipe", O_WRONLY);
    char msg[] = "Hello from writer!";
    write(fd, msg, strlen(msg)+1);
    close(fd);
    return 0;
}

