#include<stdio.h>
#include<stdlib.h>

//sembra funzioni tutto

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
        for(j=1;j<=(base-1)/(altezza-1)*(i);j++)
        {
            printf("*");
        }
        printf("\n");
    }

}