#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

sem_t my_sem;

#define PRODUCERS 5
#define CONSUMERS 5
#define SIZE 5

#define PRODUCE_TIME 5
#define CONSUME_TIME 5

void *produce(void *arg){
    int id = *((int*)arg);
    while(1){
        sleep(rand() % PRODUCE_TIME);
        int total;
        sem_getvalue(&my_sem, &total);
        while(total >= SIZE){
            usleep(10);
            sem_getvalue(&my_sem, &total);
        }
        sem_post(&my_sem);
        printf("Producent: %d produced.\n", id);
        printf("Size: %d\n", total);
    }
    return NULL;
}

void *consume(void *arg){
    int id = *((int*)arg);
    while(1){
        sleep(rand() % CONSUME_TIME);
        sem_wait(&my_sem);
        printf("Consumer: %d consumed.\n", id);
    }
    return NULL;
}

int main(){
    srand(time(NULL));

    int producers = 5;
    int consumers = 5;
    int size = 5;
    
    pthread_t* producerThreads = (pthread_t*)malloc(sizeof(pthread_t) * producers);
    pthread_t* consumerThreads = (pthread_t*)malloc(sizeof(pthread_t) * consumers);

    sem_init(&my_sem, 0, 0);

    printf("Producers: %d\n", producers);
    printf("Consumers: %d\n", consumers);
    printf("Buffor size: %d\n", size);

    for(int i = 0; i < producers; i++){
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&producerThreads[i], NULL, produce, (void*)arg);
    }

    for(int i = 0; i < consumers; i++){
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&consumerThreads[i], NULL, consume, (void*)arg);
    }

    for(int i = 0; i < producers; i++){
        pthread_join(producerThreads[i], NULL);
    }

    for(int i = 0; i < producers; i++){
        pthread_join(consumerThreads[i], NULL);
    }

    return 0;
}