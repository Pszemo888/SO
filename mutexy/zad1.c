#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 100

int counter = 0;
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_function(void *arg) {
    int iter = *((int *)arg);
    for (int i = 0; i < iter; ++i) {
        pthread_mutex_lock(&mymutex); 
        counter++;
        pthread_mutex_unlock(&mymutex); 
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number of threads> <iterations>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int num_threads = atoi(argv[1]);
    int iter = atoi(argv[2]);

    if (num_threads <= 0 || num_threads > MAX_THREADS || iter <= 0) {
        fprintf(stderr, "Invalid input parameters.\n");
        return EXIT_FAILURE;
    }

    pthread_t threads[num_threads];
    int thread_args[num_threads];

    for (int i = 0; i < num_threads; ++i) {
        thread_args[i] = iter;
        if (pthread_create(&threads[i], NULL, thread_function, (void *)&thread_args[i]) != 0) {
            fprintf(stderr, "Error creating thread %d.\n", i);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < num_threads; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Error joining thread %d.\n", i);
            return EXIT_FAILURE;
        }
    }

    printf("Final value of counter: %d\n", counter);

    return EXIT_SUCCESS;
}
