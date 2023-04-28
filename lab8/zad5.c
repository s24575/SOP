#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b){
    return (*(int*)b - *(int*)a);
}

float* k_max_elements(float* arr, int size, int k){
    qsort(arr, size, sizeof(float), compare);

    float* max_elem = (float*)malloc(sizeof(float) * k);
    float* max_curr = max_elem;
    for(float* curr = arr; curr < arr + k; curr++){
        *max_curr = *curr;
        max_curr++;
    }

    return max_elem;
}

int main(){
    float arr[] = {23, 15, 34, 27, 231, 20, 88};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    float* max_elem = k_max_elements(arr, size, k);

    for(int i = 0; i < k; i++){
        printf("%f ", max_elem[i]);
    }
    printf("\n");

    return 0;
}