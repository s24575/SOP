#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char word1[100];
    printf("Enter word 1.\n");
    scanf("%s", word1);

    char word2[100];
    printf("Enter word 2.\n");
    scanf("%s", word2);

    int result = strcmp(word1, word2);

    if(result != 0){
        printf("%s is lexicographically smaller\n", (result < 0) ? word1 : word2);
    } else{
        printf("Both words are the same.\n");
    }

    if(strlen(word1) != strlen(word2)){
        printf("%s is longer\n", (strlen(word1) > strlen(word2) ? word1 : word2));
    } else{
        printf("Both words have the same length\n");
    }
}