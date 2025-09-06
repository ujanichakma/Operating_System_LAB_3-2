#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;
int resource = 0;

void* process(void* arg) {
    for (int i = 0; i < 5; i++) {
        sem_wait(&sem); // acquire
        resource++;
        printf("Thread %ld incremented resource: %d\n", (long)pthread_self(), resource);
        sem_post(&sem); // release
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    sem_init(&sem, 0, 1); // binary semaphore (acts like mutex)

    pthread_create(&t1, NULL, process, NULL);
    pthread_create(&t2, NULL, process, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem);
    return 0;
}

