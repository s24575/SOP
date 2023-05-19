#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

sem_t my_sem;

#define MINIUM_SLEEP_TIME 5
#define SLEEP_RANGE 5
#define PRINT_TIME 3

void *my_thread(void *arg){
    int id = *((int*)arg);
    while(1){
        sleep((rand() % SLEEP_RANGE) + MINIUM_SLEEP_TIME);
        printf("Process %d wants to print something\n", id);
        sem_wait(&my_sem);
        for(int i = 0; i < PRINT_TIME; i++){
            printf("Printing: %d...\n", id);
            sleep(1);
        }
        sem_post(&my_sem);
    }
    return NULL;
}

int main(){
    srand(time(NULL));

    FILE* input = fopen("worker_count.txt", "r");
    int count;
    fscanf(input, "%d", &count);

    pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * count);

    sem_init(&my_sem, 0, 1);

    printf("Workers: %d\n", count);

    for(int i = 0; i < count; i++){
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&threads[i], NULL, my_thread, (void*)arg);
    }

    for(int i = 0; i < count; i++){
        pthread_join(threads[i], NULL);
    }    

    fclose(input);

    return 0;
}