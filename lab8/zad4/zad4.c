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

    int n = strlen(word1);
    int m = strlen(word2);

    if(m > n)
        return 1;

    int j = 0;
    for(int i = 0; i < n; i++){
        if(word1[i] == word2[j]){
            j++;
        } else{
            j = 0;
        }

        if(j == m){
            printf("%s is a subsequence of %s.\n", word2, word1);
            return 0;
        }
    }
    
    printf("%s is not a subsequence of %s.\n", word2, word1);

    return 0;
}