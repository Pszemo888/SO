#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void *printString(void *ptr);

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int main() {
    pthread_t thread1, thread2;
    int iret1;

    iret1 = pthread_create(&thread1, NULL, printString, "HELLO WORLD ");
    if(iret1) {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        exit(EXIT_FAILURE);
    }

    iret1 = pthread_create(&thread2, NULL, printString, "ala ma kota ");
    if(iret1) {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        exit(EXIT_FAILURE);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    exit(0);
}
void screenPrinter(char c) {
    pthread_mutex_lock(&mutex1);  
    printf("%c\n", c);
    usleep(250*1000); 
    pthread_mutex_unlock(&mutex1);  
}

void *printString(void *ptr) {
    char *message;
    message = (char *) ptr;
    int len = strlen(message);
    int i = 0;

    // Drukowanie wiadomości znak po znaku
    for (i = 0; i < len; i++) {
        screenPrinter(message[i]);
    }

    return NULL;
}
