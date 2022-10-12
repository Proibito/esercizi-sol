#include<stdio.h>
#include<stdlib.h>

//Nota:   se il numero di asterischi da stampare non sarebbe intero, verranno stampati gli asterischi approssimati per difetto

int main()
{
    char stringa[100];
    unsigned base, altezza;
    int i, j;
    printf("Inserisci il valore della base: ");
    fgets(stringa, sizeof(stringa), stdin);
    base = strtol(stringa, NULL, 10);
    printf("Inserisci il valore dell'altezza: ");
    fgets(stringa, sizeof(stringa), stdin);
    altezza = strtol(stringa, NULL, 10);

    for(i=0;i<altezza;i++)
    {
        printf("*");
        for(j=1;j<=(base-1)*(i)/(altezza-1);j++)
        {
            printf("*");
        }
        /*if((float)(base-1)*(i)/(altezza-1)-j>0.5)     ho tentato di migliorare l'approssimazione ma non ci sono riuscito
        {
            printf("*");
        }*/
        printf("\n");
    }

}