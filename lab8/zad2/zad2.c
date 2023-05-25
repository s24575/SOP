#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, m;
    printf("input n: ");
    scanf("%d", &n);
    printf("input m: ");
    scanf("%d", &m);

    int* a = (int*)malloc(n * sizeof(int));
    int* b = (int*)malloc(m * sizeof(int));
    
    for(int i = 0; i < n; i++){
        int* x = &a[i];
        printf("1: input an integer: ");
        scanf("%d", x);
    }

    for(int i = 0; i < m; i++){
        int* x = &b[i];
        printf("2: input an integer: ");
        scanf("%d", x);
    }

    for(int i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");

    for(int i = 0; i < m; i++){
        printf("%d ", b[i]);
    }
    printf("\n");

    for(int i = 0; i < n; i++){
        for(int j = i; j < m; j++){
            if(a[i] == b[j]){
                printf("a[%d]: %d, b[%d]: %d are the same.\n", i, a[i], j, b[j]);
            }
        }
    }

    return 0;
}