#include <stdio.h>

// Scrivere un programma che stampi a video un triangolo rettangolo di ’*’ la cui base e altezza siano lette
// da tastiera. Esempio, se vengono inseriti 10 (base) e 4 (altezza), viene stampato quanto segue

int main()
{
    printf("base \n");
    int base = 2;
    // scanf("%d", &base);

    printf("altezza: \n");
    int altezza = 4;
    int baseAlContrario = base + 1;
    // scanf("%d", &altezza);
    int giro = 0;
    int span = (base % altezza);
    for (altezza; altezza != 0; altezza--)
    { 
        printf("\n");
    }
}