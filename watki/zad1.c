#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;
volatile int flag = 0;

void *thread1(void *arg) {
    while (1) {
        while (flag != 0); 
        printf("Counter value: %d\n", counter);
        flag = 1; 
        usleep(500000); 
    }
    return NULL;
}

void *thread2(void *arg) {
    while (1) {
        while (flag != 1); 
        counter++; 
        flag = 0; 
        usleep(500000); 
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    
    void *retval;
    pthread_join(t1, &retval);
    pthread_join(t2, &retval);

    return 0;
}
