#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

int main(){
    char s[100];
    printf("Enter name and surname, ex. [John Doe]");
    fgets (s, 100, stdin);
    s[strcspn(s, "\r\n")] = 0;

    for(int i = 0; i < strlen(s); i++){
        // printf("%d ", (int)s[i]);
        if(s[i] != ' ' && !isalpha(s[i])){
            perror("Input contains non letter characters\n");
        }
    }

    FILE* file = fopen("baza.txt", "r");

    char* line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1) {
        line[strcspn(line, "\r\n")] = 0;
        if(!strcmp(s, line)){
            printf("Found!\n");
        }
    }

    return 0;
}