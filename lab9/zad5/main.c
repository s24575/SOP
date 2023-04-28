#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

void *myThread(void *arg) {
    int x;
    do{
        x = (rand() % 50) + 1;
        printf("Thread: %ld, Number: %d\n", pthread_self(), x);
    } while(x % 5 != 0);
    printf("Number is divisible by 5.\n");

    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_t threadId;
    pthread_create(&threadId, NULL, myThread, NULL);
    pthread_join(threadId, NULL);
    return 0;
}