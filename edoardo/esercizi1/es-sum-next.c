#include <stdio.h>
#include <stdlib.h>

// ok funziona

int main()
{

    int v2[10] = {0};
    int v1[10] = {0};

    for (int i = 0; i < 10; i++)
    {
        char carattere[10];
        fgets(carattere, sizeof(v1), stdin);
        v1[i] = strtol(carattere, NULL, 10);
    }

    for (int i = 0; i < 10; i++)
    {
        for (int k = i; k < 10; k++)
        {
            v2[i] += v1[k];
            printf("v1: %d - k: %d - v2: %d\n", v1[k], k, v2[i]);
        }
    }

    for (int i = 0; i < 10; i++)
    {
        printf("v2 %d \n", v2[i]);
    }

    return 0;
}