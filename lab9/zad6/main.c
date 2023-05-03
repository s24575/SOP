#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <pthread.h>
#include <limits.h>

#define LANES 4
#define SIZE 50

#define SIGNALIZATION_DELAY 10000
#define TRAFFIC_DELAY 5000
#define MAIN_PROCESS_DELAY 10000

int spots[SIZE];
bool is_green_light = false;
bool accident = false;
int lane_id;

void* handle_signalization(void *arg) {
    printf("Created lane %d signalization thread.\n", lane_id);
    while(!accident){
        usleep(SIGNALIZATION_DELAY);
        is_green_light = !is_green_light;
    }
    return NULL;
}

void* handle_traffic(void *arg) {
    printf("Created lane %d traffic thread.\n", lane_id);
    while(!accident){
        int min = INT_MAX;
        for(int i = 0; i < SIZE; i++){
            if(spots[i] && spots[i] < min){
                min = spots[i];
            }
        }

        if(min > 20 || is_green_light){
            for(int i = 0; i < SIZE; i++){
                if(spots[i] > 0){
                    spots[i]--;
                }
            }
        }

        if(min <= 10){
            kill(getppid(), (lane_id & 1) ? SIGUSR1 : SIGUSR2);
        }

        usleep(TRAFFIC_DELAY);
    }
    return NULL;
}

void add_car_to_lane(){
    for(int i = 0; i < SIZE; i++){
        if(spots[i] == 0){
            spots[i] = SIZE;
            break;
        } else if(spots[i] == SIZE){
            printf("Crash at lane %d: spot %d.\n", lane_id, SIZE);
            accident = true;
            break;
        }
    }
}

void print_lane(){
    printf("[%d] %s: ", lane_id, (is_green_light) ? "green" : "red");
    for(int i = 0; i < SIZE; i++){
        printf("%d ", spots[i]);
    }
    printf("\n");
}

void process_lane(int process_id){
    printf("Created lane %d.\n", process_id);

    lane_id = process_id;
    is_green_light = lane_id & 1;

    signal(SIGUSR1, add_car_to_lane);
    signal(SIGUSR2, print_lane);

    pthread_t threadId1, threadId2;
    pthread_create(&threadId1, NULL, handle_signalization, NULL);
    pthread_create(&threadId2, NULL, handle_traffic, NULL);

    while(!accident){
        pause();
    }
}

void cleanup(){
    printf("Cleaning up...\n");
    kill(0, SIGTERM);
}

void handle_SIGINT(){
    exit(0);
}

bool is_vertical_in_range = false;
bool is_horizontal_in_range = false;

void handle_SIGUSR1(){
    is_vertical_in_range = true;
}

void handle_SIGUSR2(){
    is_horizontal_in_range = true;
}

int main(){
    srand(time(NULL));

    atexit(cleanup);
    signal(SIGINT, handle_SIGINT);

    int lanes[LANES];
    for (int i = 0; i < LANES; i++){
        int pid = fork();
        if(pid < 0){
            printf("Error: creating a lane unsuccessful.\n");
            return 1;
        }
        else if (pid == 0){
            process_lane(i);
            exit(0);
        }
        
        lanes[i] = pid;
        usleep(5000);
    }

    printf("Generated processes.\n");

    signal(SIGUSR1, handle_SIGUSR1);
    signal(SIGUSR2, handle_SIGUSR2);


    while(true){
        int x = rand() % LANES;
        kill(lanes[x], SIGUSR1);
        
        printf("========================================================================================================\n");
        printf("Adding a car to lane %d\n", x);
        printf("========================================================================================================\n");
        for(int i = 0; i < LANES; i++){
            kill(lanes[i], SIGUSR2);
        }

        if(is_horizontal_in_range && is_vertical_in_range){
            printf("Crash between different lanes.\n");
            return 0;
        }

        is_vertical_in_range = false;
        is_horizontal_in_range = false;

        usleep(MAIN_PROCESS_DELAY);
    }

    return 0;
}