#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

struct ThreadArgs {
    int start;
    int end;
    int *result;
} typedef ThreadArgs;

void *sumThread(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    int sum = 0;
    for (int i = args->start; i <= args->end; ++i) {
        sum += i;
    }
    *(args->result) = sum;
    pthread_exit(NULL);
}

void *productThread(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    int product = 1;
    for (int i = args->start; i <= args->end; ++i) {
        product *= i;
    }
    *(args->result) = product;
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadArgs thread_args[NUM_THREADS];
    int results[NUM_THREADS];

    int num_start = 1;
    int num_end = 10;

    int num_range = (num_end - num_start + 1) / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_args[i].start = num_start + i * num_range;
        thread_args[i].end = thread_args[i].start + num_range - 1;
        thread_args[i].result = &results[i];

        if (pthread_create(&threads[i], NULL, i == 0 ? sumThread : productThread, &thread_args[i]) != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("Sum: %d\n", results[0]);
    printf("Product: %d\n", results[1]);

    return 0;
}