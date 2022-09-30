#include<stdio.h>
#include<math.h>
#include <string.h>

int main()
{
    double n;
    int i;
    double esponente;
    printf("Inserisci il numero con la virgola: ");
    scanf("%lf", &n);

    esponente = *memcpy(&esponente, &n+1, 11);

    printf("Esponente = %lf\n", esponente);

    return 0;
}