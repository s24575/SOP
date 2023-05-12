#include "stdio.h"
#include "stdlib.h"

int main()
{
    int x;
    printf("Input size: ");
    scanf("%d", &x);
    int* arr = (int*)malloc(x * sizeof(int));
    for (int i = 0; i < x; i++)
    {
        printf("Input a number: ");
        scanf("%d", &arr[i]);
    }

    FILE* dodatnie = fopen("dodatnie.txt", "w");
    FILE* ujemne = fopen("ujemne.txt", "w");

    for (int i = 0; i < x; i++)
    {
        if(arr[i] > 0){
            fprintf(dodatnie, "%d\n", arr[i]);
        }
        else if(arr[i] < 0){
            fprintf(ujemne, "%d\n", arr[i]);
        }
        else {
            perror("0 is illegal.");
        }
    }

    return 0;
}