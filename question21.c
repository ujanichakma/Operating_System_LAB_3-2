#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *fib_sequence;
int n;

void* generate_fibonacci(void* arg) {
    if (n > 0) fib_sequence[0] = 0;
    if (n > 1) fib_sequence[1] = 1;
    for (int i = 2; i < n; i++)
        fib_sequence[i] = fib_sequence[i-1] + fib_sequence[i-2];
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_terms>\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    fib_sequence = malloc(n * sizeof(int));

    pthread_t tid;
    pthread_create(&tid, NULL, generate_fibonacci, NULL);
    pthread_join(tid, NULL);

    printf("Fibonacci sequence:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", fib_sequence[i]);
    printf("\n");

    free(fib_sequence);
    return 0;
}

