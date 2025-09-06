#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

void* thread_function(void* arg) {
    printf("Thread started (TID: %ld)\n", pthread_self());
    
    // A. Call fork() inside a thread
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child Process (PID: %d). Only this thread is duplicated.\n", getpid());
        // B. Call exec inside thread
        execlp("ls", "ls", "-l", NULL);
        perror("exec failed");
        exit(1);
    } else {
        wait(NULL);
    }

    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_function, NULL);
    pthread_create(&t2, NULL, thread_function, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Main process finished.\n");
    return 0;
}

