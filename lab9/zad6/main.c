/*
Zadanie 6. (5 pkt.)
Napisz program, który będzie symulatorem sygnalizacji świetlnej na skrzyżowaniu czterech ulic.
Symulator powinien składać się z:
    - czterech procesów, które będą symulowały pas ruchu,
    - procesu, który będzie nadzorował pracę skrzyżowania.

Proces nadzorujący powinien utworzyć cztery procesy potomne, które będą symulowały sygnalizację świetlną. (0,5 pkt.)
Każdy z tych czterech procesów potomnych powinien utworzyć po dwa wątki. (0,5 pkt.)
    - wątek obsługujący zmiany świateł (w odpowiednich odstępach czasu),
    - wątek symulujący ruch pojazdów na pasie ruchu.

Proces nadzorujący powinien, co jakiś czas, wysyłać sygnał SIGUSR1 do "losowo" wybranego procesu.
Po odebraniu komunikatu SIGUSR1 proces symulujący pas ruchu powinien zapisać odległość pojazdu z początkową wartością 50,
która zostanie zapisana w tablicy, w miejscu o wartości 0. Drugi wątek powinien, co jakiś czas, zmniejszać o 1 niezerowe wartości,
przy czym jeżeli istnieje jakaś wartość w tablicy, która jest mniejsza lub równa 20 to wszystkie wartości tablicy powinny być
zmniejszane tylko wtedy, gdy pierwszy wątek ma "zapalone" zielone światło. Element tablicy powinien być zmniejszany dopóki nie będzie
równy 0 (zadbaj o komunikację miedzy procesami i wątkami). (2 pkt.)
Symulator powinien zakończyć działanie kiedy dojdzie do wypadku.
Do wypadku może dojść, jeżeli któryś z pasów ruchu przyjął sygnał SIGUSR1 w momencie, kiedy wątek sterujący zawiera element o wartości
50 (0,5 pkt.) lub kiedy jakiś pionowy i poziomy pas ruchu zawiera pojazd o wartości mniejszej lub równej 10 w tym samym czasie
(1,5 pkt.) (wykorzystaj odpowiednie komunikatu procesów pasa ruchu i jego wątków z procesem nadzorującym, oraz musisz wyróżnić
dwa procesy pasa ruchu jako poziome oraz dwa procesy pasa ruchu pionowe).
*/

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
int spots[SIZE];
bool is_green_light = false;
bool is_vertical = false;

void* handle_signalization(void *arg) {
    while(true){
        // change lights (random or vertical/horizontal sync?)
    }
    return NULL;
}

void* handle_traffic(void *arg) {
    // crash if 2 vertical/horizontal lines have a car <= 10
    while(true){
        int min = INT_MAX;
        for(int i = 0; i < SIZE; i++){
            if(spots[i] < min){
                min = spots[i];
            }
        }

        if(min > 20 || is_green_light)
        for(int i = 0; i < SIZE; i++){
            if(spots[i] > 0){
                spots[i]--;
            }
        }
    }
    return NULL;
}

void add_car_to_lane(){
    for(int i = 0; i < SIZE; i++){
        if(spots[i] == 0){
            spots[i] = SIZE;
            return;
        } else if(spots[i] == SIZE){
            printf("Crash at spot 50.\n");
            kill(getppid(), SIGINT);
        }
    }
    printf("No free spots in this lane.\n");
}

void print_lane(){
    for(int i = 0; i < SIZE; i++){
        printf("%d ", spots[i]);
    }
    printf("\n");
}

void process_lane(bool orientation){
    is_vertical = orientation;
    pthread_t threadId1, threadId2;
    pthread_create(&threadId1, NULL, handle_signalization, NULL);
    pthread_create(&threadId2, NULL, handle_traffic, NULL);

    signal(SIGUSR1, add_car_to_lane);
    signal(SIGUSR2, print_lane);

    pthread_join(threadId1, NULL);
    pthread_join(threadId2, NULL);

    exit(0);
}

int main(){
    srand(time(NULL));

    int lanes[LANES];

    for (int i = 0; i < LANES; i++){
        int lane = fork();
        if (lane == 0){
            process_lane(i & 1);
        }
        lanes[i] = lane;
    }

    while(true){
        int id = lanes[rand() % LANES];
        kill(id, SIGUSR1);
        
        for(int i = 0; i < LANES; i++){
            printf("[1]");
            kill(lanes[i], SIGUSR2);
        }

        sleep(1);
    }

    return 0;
}