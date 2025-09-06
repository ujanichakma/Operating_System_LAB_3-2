#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    int shmid = shmget(1234, sizeof(int), IPC_CREAT | 0666);
    int *counter = (int *)shmat(shmid, NULL, 0);
    *counter = 0;

    for (int i = 0; i < 100000; i++) (*counter)++;
    printf("Writer done.\n");
    shmdt(counter);
    return 0;
}

