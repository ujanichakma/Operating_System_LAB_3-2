#include <stdio.h>
#include <sys/ipc.h>
#include<sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

union semun { int val; };
void wait_sem(int semid) { struct sembuf sb = {0, -1, 0}; semop(semid, &sb, 1); }
void signal_sem(int semid) { struct sembuf sb = {0, 1, 0}; semop(semid, &sb, 1); }

int main() {
    int shmid = shmget(1234, sizeof(int), IPC_CREAT | 0666);
    int *counter = (int *)shmat(shmid, NULL, 0);
    *counter = 0;

    int semid = semget(5678, 1, IPC_CREAT | 0666);
    union semun u;
    u.val = 1;
    semctl(semid, 0, SETVAL, u);

    pid_t pid = fork();

    for (int i = 0; i < 100000; i++) {
        wait_sem(semid);
        (*counter)++;
        signal_sem(semid);
    }

    if (pid == 0) {
        shmdt(counter);
        return 0;
    } else {
        wait(NULL);
        printf("Final counter: %d\n", *counter);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);
    }

    return 0;
}

