#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    int shmid = shmget(1234, sizeof(int), 0666);
    int *counter = (int *)shmat(shmid, NULL, 0);

    for (int i = 0; i < 100000; i++) (*counter)++;
    printf("Final counter (expected 200000): %d\n", *counter);

    shmdt(counter);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

