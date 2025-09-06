// Compile with: gcc server_single.c -o server_single
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv = {0};
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));
    listen(sockfd, 5);
    printf("Single-threaded server running...\n");

    while (1) {
        int clientfd = accept(sockfd, NULL, NULL);
        char buffer[100];
        read(clientfd, buffer, sizeof(buffer));
        printf("Client said: %s\n", buffer);
        write(clientfd, "Hello from server", 18);
        close(clientfd);
    }

    return 0;
}

