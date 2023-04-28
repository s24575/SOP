#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>

int main(){
    srand(time(NULL));

    int id = fork();
    if(id == 0){
        int x;
        do{
            x = (rand() % 50) + 1;
            printf("Child: %d, Parent: %d, Number: %d\n", getpid(), getppid(), x);
        } while(x % 5 != 0);
        printf("Number is divisible by 5.\n");
    } else {
        wait(NULL);
        printf("Parent: %d\n", getpid());
    }

    return 0;
}