#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

void print_child_info(){
    while(true){
        printf("Child: %d, Parent: %d\n", getpid(), getppid());
        sleep(1);
    }

    exit(0);
}

int main(){
    srand(time(NULL));

    int child1_pid = fork();
    if(child1_pid == 0){
        print_child_info();
    }
    printf("Created child 1%d\n", child1_pid);

    int child2_pid = fork();
    if(child2_pid == 0){
        print_child_info();
    }
    printf("Created child 2%d\n", child2_pid);

    bool is_child1_killed = false;
    bool is_child2_killed = false;

    while(!is_child1_killed || !is_child2_killed){
        int x = (rand() % 50) + 1;
        printf("Number: %d\n", x);

        if(!is_child1_killed && x < 10){
            printf("kill child 1\n");
            kill(child1_pid, SIGINT);
            is_child1_killed = true;
        }
        if(!is_child2_killed && x > 40){
            printf("kill child 2\n");
            kill(child2_pid, SIGINT);
            is_child2_killed = true;
        }

        sleep(1);
    }

    printf("Parent: %d\n", getpid());

    return 0;
}