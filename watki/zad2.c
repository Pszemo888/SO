#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define NUM_THREADS 10

void *thread_function(void *arg) {
    int *iterations = (int *)arg;
    int num_iterations = rand() % 10001;
    
    for (int i = 0; i < num_iterations; ++i) {
        printf("Wątek %ld iteracja %d\n", pthread_self(), i);
    }
    
    *iterations = num_iterations;

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int iterations[NUM_THREADS];
    int total_iterations = 0;
    
    srand(time(NULL));

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, thread_function, &iterations[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        void *retval;
        pthread_join(threads[i], &retval);
        total_iterations += iterations[i];
    }
    
    printf("Łączna liczba iteracji: %d\n", total_iterations);
    
    return 0;
}

