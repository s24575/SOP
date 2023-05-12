#include "stdio.h"
#include "limits.h"

int main()
{
    FILE *file = fopen("liczby.txt", "r");
    int x, min = INT_MAX, max = INT_MIN;
    
    while (!feof(file))
    {
        fscanf(file, "%d", &x);
        printf("%d\n", x);
        if (x < min)
            min = x;
        else if (x > max)
            max = x;
    }

    printf("min: %d, max: %d\n", min, max);

    return 0;
}