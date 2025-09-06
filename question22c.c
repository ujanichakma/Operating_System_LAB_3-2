#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv = {0};
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));
    listen(sockfd, 5);
    printf("Multi-process server running...\n");

    while (1) {
        int clientfd = accept(sockfd, NULL, NULL);
        if (fork() == 0) {
            char buffer[100];
            read(clientfd, buffer, sizeof(buffer));
            printf("Child handling: %s\n", buffer);
            write(clientfd, "Child process response", 23);
            close(clientfd);
            exit(0);
        }
        close(clientfd); // Parent closes client socket
    }

    return 0;
}

