// Compile with: gcc client.c -o client
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

    connect(sockfd, (struct sockaddr*)&serv, sizeof(serv));
    write(sockfd, "Hi Server!", 10);
    char buffer[100];
    read(sockfd, buffer, sizeof(buffer));
    printf("Received: %s\n", buffer);
    close(sockfd);
    return 0;
}

