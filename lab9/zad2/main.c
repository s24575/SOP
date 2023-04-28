#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signum){
    printf("\nI'm immortal: %d\n", getpid());
}

void sighup_handler(int signum){
    signal(SIGINT, SIG_IGN);
}

int main(){
    signal(SIGINT, sigint_handler);
    signal(SIGHUP, sighup_handler);
    while(1){
        printf("Inside main function\n");
        sleep(1);
    }

    return 0;
}