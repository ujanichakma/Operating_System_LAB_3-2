#include <stdio.h>
#include <sys/shm.h>
#include<sys/wait.h>
#include <unistd.h>

int main() {
    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    int *counter = (int *)shmat(shmid, NULL, 0);
    *counter = 0;

    pid_t pid = fork();

    if (pid == 0) {
        // Child
        for (int i = 0; i < 100000; i++) (*counter)++;
        printf("Child done.\n");
    } else {
        // Parent
        for (int i = 0; i < 100000; i++) (*counter)++;
        wait(NULL);
        printf("Final value (expected 200000): %d\n", *counter);
        shmdt(counter);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}

