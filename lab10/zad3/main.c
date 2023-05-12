#include "stdio.h"
#include "string.h"

int main(){
    char s1[100];
    char s2[100];

    printf("Enter first string: ");
    scanf("%s", s1);
    printf("Enter second string: ");
    scanf("%s", s2);

    int result = strcmp(s1, s2);

    if(strlen(s1) == strlen(s2)){
        perror("Both strings have the same length.");
    }
    if(result < 0){
        printf("[%s] is lexicographically smaller.\n", s1);
    }

    else if(result > 0){
        printf("[%s] is lexicographically smaller.\n", s2);
    }

    return 0;
}