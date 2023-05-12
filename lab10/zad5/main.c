#include "stdio.h"

int main(){
    FILE* input = fopen("znaki.txt", "r");
    char s[30];
    size_t len = 0;
    while (getline(&s, &len, input) != -1) {
        s[strcspn(s, "\r\n")] = 0;
        
    }
}