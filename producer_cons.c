#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t empty, full, mutex;
int buffer[5] = {-1, -1, -1, -1, -1}; 
int in = 0, out = 0;

void* producer(void* arg) {
    sem_wait(&empty); 
    sem_wait(&mutex);

    buffer[in] = rand() % 100; 
    printf("Produced: %d | Buffer: ", buffer[in]);
    in = (in + 1) % 5;

    for(int i = 0; i < 5; i++)
        printf("%d ", buffer[i]);
    printf("\n");

    sem_post(&mutex); 
    sem_post(&full);
    return NULL;
}

void* consumer(void* arg) {
    int val;
    do {
        sem_wait(&full);
        sem_wait(&mutex); 

        printf("Consumed: %d | Buffer: ", buffer[out]);
        buffer[out] = -1; em
        out = (out + 1) % 5;

        for(int i = 0; i < 5; i++)
            printf("%d ", buffer[i]);
        printf("\n");

        sem_post(&mutex);
        sem_post(&empty); 
        sem_getvalue(&empty, &val);
    } while(val != 5); 
    return NULL;
}

int main() {
    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t producers[8], consumer_thread;

    for(int i = 0; i < 8; i++) 
        pthread_create(&producers[i], NULL, producer, NULL);
    
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    for(int i = 0; i < 8; i++) 
        pthread_join(producers[i], NULL);
    
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    
    return 0;
}
