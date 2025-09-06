#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<stdlib.h>
#include <unistd.h>

void* handle_client(void* arg) {
    int clientfd = *(int*)arg;
    char buffer[100];
    read(clientfd, buffer, sizeof(buffer));
    printf("Thread handling: %s\n", buffer);
    write(clientfd, "Threaded response", 18);
    close(clientfd);
    return NULL;
}

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv = {0};
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));
    listen(sockfd, 5);
    printf("Multi-threaded server running...\n");

    while (1) {
        int *clientfd = malloc(sizeof(int));
        *clientfd = accept(sockfd, NULL, NULL);
        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, clientfd);
        pthread_detach(tid);
    }

    return 0;
}

