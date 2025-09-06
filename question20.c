#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int average, minimum, maximum;
int *numbers;
int count;

void* calc_average(void* arg) {
    int sum = 0;
    for (int i = 0; i < count; i++) sum += numbers[i];
    average = sum / count;
    return NULL;
}

void* calc_minimum(void* arg) {
    minimum = numbers[0];
    for (int i = 1; i < count; i++)
        if (numbers[i] < minimum)
            minimum = numbers[i];
    return NULL;
}

void* calc_maximum(void* arg) {
    maximum = numbers[0];
    for (int i = 1; i < count; i++)
        if (numbers[i] > maximum)
            maximum = numbers[i];
    return NULL;
}

int main(int argc, char *argv[]) {
    count = argc - 1;
    numbers = malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++) numbers[i] = atoi(argv[i+1]);

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, calc_average, NULL);
    pthread_create(&t2, NULL, calc_minimum, NULL);
    pthread_create(&t3, NULL, calc_maximum, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("Average = %d\nMinimum = %d\nMaximum = %d\n", average, minimum, maximum);
    free(numbers);
    return 0;
}

