#include <stdio.h>

int main(){
    int input;
    scanf("%d", &input);

    int sum;
    int counter = 1;
    while(1){
        sum += counter;
        if(sum > input){
            break;
        }
        counter++;
    }

    printf("%d\n", counter - 1);

    return 0;
}