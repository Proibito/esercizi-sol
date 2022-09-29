#include<stdio.h>
#include<string.h>
#define NUMERI 10

int main()
{
    char stringa[100];
    int vettore[NUMERI];
    int i;
    //scanf("%d %d %d %d %d %d %d %d %d %d", &v[0], &v[1], &v[0], ...);
    for(i=0;i<NUMERI;i++)
    {
        fgets(&stringa, sizeof(stringa), stdin);
        vettore[i] = strtol(stringa, NULL, 10);
    }

//    VETTORE RICEVUTO   //

    int somma=0;
    int vettore_2[NUMERI];
    for(i=NUMERI-1;i!=0;i++)
    {
        vettore_2[i]=somma+vettore[i];
        somma = somma + vettore[i];
    }

}